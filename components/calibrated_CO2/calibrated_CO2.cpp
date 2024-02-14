#include "calibrated_CO2.h"
#include "esphome/core/log.h"

namespace esphome {
namespace calibrated_CO2 {

    static const char* TAG = "calibrated_CO2";

    void CALIBRATEDCO2::setup()
    {
    }

    void CALIBRATEDCO2::loop()
    {
        update();
    }

    void CALIBRATEDCO2::update()
    {
        publish_state(4);
    }

    void CALIBRATEDCO2::dump_config()
    {
        ESP_LOGCONFIG(TAG, "Empty custom sensor");
    }

} // namespace empty_sensor
} // namespace esphome