#include "calibrated_co2.h"
#include "esphome/core/log.h"

namespace esphome {
namespace calibrated_co2 {

    static const char* TAG = "calibrated_co2";

    void CalibratedCo2::setup()
    {
        //this->outdoor_co2 = get_calibration_value();
    }

    void CalibratedCo2::loop()
    {
        // update();
    }

    void CalibratedCo2::update()
    {
        float offset = 0;
        if (this->sensor_->has_state()) {
            if (!this->has_been_updated_before_) {
                this->min_co2_ = this->sensor_->get_state();
                this->has_been_updated_before_ = true;
            } else {
                if (this->sensor_->get_state() < this->min_CO2_) {
                    this->min_co2_ = this->sensor_->get_state();
                }
            }
            offset = this->min_co2_ - this->outdoor_co2_;
        }
        if (this->retrieve_co2_online_) {
            if (millis() > this->wait_) {
                if (millis() - this->previous_calibration_ > this->calibration_interval_) {
                    this->outdoor_co2_ = get_calibration_value();
                    this->previous_calibration_ = millis();
                }
            }
        }

        Serial.print("Retrieve CO2 online?:");
        Serial.println(this->retrieve_co2_online_);
        Serial.print("default CO2 outdoor:");
        Serial.println(this->default_outdoor_co2);
        this->co2_sensor_->state = this->sensor_->get_state() - offset;
        this->co2_sensor_->publish_state(this->co2_sensor_->state);
        Serial.print("min_CO2_: ");
        Serial.println(this->min_co2_);
        Serial.print("Calibrated CO2: ");
        Serial.println(this->co2_sensor_->get_state());
        Serial.print("Uncalibrated CO2: ");
        Serial.println(this->sensor_->get_state());
        publish_state(this->outdoor_co2_);
    }

    void CalibratedCo2::dump_config()
    {
        ESP_LOGCONFIG(TAG, "Empty custom sensor");
    }

    float CalibratedCo2::get_calibration_value()
    {
        HTTPClient http;
        http.begin("https://charting.numberlens.com/api/teamearth/getdailyco2?authtoken=D43026302F294A5784F7512A8969FE37"); // Replace with the actual URL
        int httpCode = http.GET();

        if (httpCode == HTTP_CODE_OK) {
            String searchForStart = "\"CurrentIndexValue\":";
            String htmlContent = http.getString();
            int startIdx = htmlContent.indexOf(searchForStart);
            if (startIdx != -1) {
                String temp = htmlContent.substring(startIdx + searchForStart.length(), htmlContent.length() - 1);
                String value = temp.substring(0, temp.indexOf(","));
                return value.toFloat();
            } else {
                return this->default_outdoor_co2;
            }
        } else {
            return this->default_outdoor_co2;
        }
    }

} // namespace empty_sensor
} // namespace esphome