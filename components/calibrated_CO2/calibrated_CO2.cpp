#include "calibrated_CO2.h"
#include "esphome/core/log.h"

namespace esphome {
namespace calibrated_CO2 {

    static const char* TAG = "calibrated_CO2";

    void CALIBRATEDCO2::setup()
    {
        //_outDoorCO2 = getCalibrationValue();
    }

    void CALIBRATEDCO2::loop()
    {
        // update();
    }

    void CALIBRATEDCO2::update()
    {
        float offset = 0;
        if (sensor_->has_state()) {
            if (!updated_before_) {
                min_CO2_ = sensor_->get_state();
                updated_before_ = true;
            } else {
                if (sensor_->get_state() < min_CO2_) {
                    min_CO2_ = sensor_->get_state();
                }
            }
            offset = min_CO2_ - outDoorCO2_;
        }
        if (get_co2_online_) {
            if (millis() > wait_) {
                if (millis() - previous_calibration_ > calibration_interval_) {
                    outDoorCO2_ = getCalibrationValue();
                    previous_calibration_ = millis();
                }
            }
        }

        Serial.print("CO2 online?:");
        Serial.println(get_co2_online_);
        Serial.print("default CO2 outdoor:");
        Serial.println(default_outDoor_CO2);
        co2_sensor_->state = sensor_->get_state() - offset;
        co2_sensor_->publish_state(co2_sensor_->state);
        Serial.print("min_CO2_: ");
        Serial.println(min_CO2_);
        Serial.print("Calibrated CO2: ");
        Serial.println(co2_sensor_->get_state());
        Serial.print("Uncalibrated CO2: ");
        Serial.println(sensor_->get_state());
        publish_state(outDoorCO2_);
    }

    void CALIBRATEDCO2::dump_config()
    {
        ESP_LOGCONFIG(TAG, "Empty custom sensor");
    }

    float CALIBRATEDCO2::getCalibrationValue()
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
                return default_outDoor_CO2;
            }
        } else {
            return default_outDoor_CO2;
        }
    }

} // namespace empty_sensor
} // namespace esphome