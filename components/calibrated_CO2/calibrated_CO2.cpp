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
        update();
    }

    void CALIBRATEDCO2::update()
    {
        publish_state(_outDoorCO2);
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
            Serial.println(htmlContent);
            int startIdx = htmlContent.indexOf(searchForStart);
            if (startIdx != -1) {
                String temp = htmlContent.substring(startIdx + searchForStart.length(), htmlContent.length() - 1);
                String value = temp.substring(0, temp.indexOf(","));
                return value.toFloat();
            } else {
                return 420;
            }
        }
    }

} // namespace empty_sensor
} // namespace esphome