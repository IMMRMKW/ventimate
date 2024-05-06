#pragma once
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include <HTTPClient.h>

#define DEFAULT_OUTDOOR_CO2 420.0
#define WAITING_TIME 120
#define CALIBRATION_INTERVAL 60

namespace esphome {
namespace calibrated_co2 {
    /**
     * @class Calibrated_CO2
     * @brief A class that implements extended calibration functionality by getting the Baseline environment
     * @todo document all one-liner functions (set/get) and class variables
     * @todo document all functions in .cpp file
     * @todo implement dump_config function
     * @todo waiting time implementation can be deleted. Was to check if powerdelivery was influenced
     * @todo check if current online database is representative for world wide CO2 levels, or more logical to use other database
     * @todo Current method of getting online data takes too much time according to ESPHome, look at if alternatives are possible. There is a HTTPRequest Class, maybe use that.
     * @todo check if calibration method is sensible, or smarter methods are available
     */

    class CalibratedCo2 : public sensor::Sensor, public PollingComponent {
    public:
        void setup() override;
        void loop() override;
        void update() override;
        void set_sensor(sensor::Sensor* sensor) { sensor_ = sensor; }
        void set_co2_sensor(sensor::Sensor* co2_sensor) { co2_sensor_ = co2_sensor; }
        void dump_config() override;
        void set_flag_retrieving_co2_online_(bool flag) { retrieve_co2_online_ = flag; }
        void set_default_outdoor_co2(float default_value) { default_outdoor_co2 = default_value; }

    private:
        float get_calibration_value();
        float default_outdoor_co2 = DEFAULT_OUTDOOR_CO2;
        float outdoor_co2_ = DEFAULT_OUTDOOR_CO2;
        float min_co2_;
        uint32_t wait_ = WAITING_TIME * 1000; // waiting time
        uint32_t calibration_interval_ = CALIBRATION_INTERVAL * 1000; // calibration interval
        uint32_t previous_calibration_ = 0; // moment of previous calibration in milliseconds
        bool retrieve_co2_online_ = false;

    protected:
        sensor::Sensor* sensor_ { nullptr };
        sensor::Sensor* co2_sensor_ { nullptr };
        bool has_been_updated_before_ = false;
    };

} // namespace calibrated_co2
} // namespace esphome