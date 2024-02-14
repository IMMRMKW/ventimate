#include "empty_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace empty_sensor {

    static const char* TAG = "calibrated_CO2";

    void CALIBRATEDCO2::setup()
    {
    }

    void CALIBRATEDCO2::loop()
    {
        this->update();
    }

    void CALIBRATEDCO2::update()
    {
        this->publish_state(4);
    }

    void CALIBRATEDCO2::dump_config()
    {
        ESP_LOGCONFIG(TAG, "Empty custom sensor");
    }

} // namespace empty_sensor
} // namespace esphome