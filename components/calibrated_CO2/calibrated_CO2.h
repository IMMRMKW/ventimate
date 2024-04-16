#pragma once
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include <HTTPClient.h>

#define DEFAULT_OUTDOOR_CO2 420.0
#define WAITING_TIME 120
#define CALIBRATION_INTERVAL 60

namespace esphome {
namespace calibrated_CO2 {

    class CALIBRATEDCO2 : public sensor::Sensor, public PollingComponent {
    public:
        void setup() override;
        void loop() override;
        void update() override;
        void set_sensor(sensor::Sensor* sensor) { sensor_ = sensor; }
        void set_co2_sensor(sensor::Sensor* co2_sensor) { co2_sensor_ = co2_sensor; }
        void dump_config() override;
        void set_Getting_CO2_Online(bool flag) { get_co2_online_ = flag; }
        void set_default_outdoor_CO2(float default_value) { default_outDoor_CO2 = default_value; }

    private:
        float
        getCalibrationValue();
        float default_outDoor_CO2 = DEFAULT_OUTDOOR_CO2;
        float outDoorCO2_ = DEFAULT_OUTDOOR_CO2;
        float min_CO2_;
        uint32_t wait_ = WAITING_TIME * 1000; // waiting time
        uint32_t calibration_interval_ = CALIBRATION_INTERVAL * 1000; // calibration interval
        uint32_t previous_calibration_ = 0; // moment of previous calibration in milliseconds
        bool get_co2_online_ = false;

    protected:
        sensor::Sensor* sensor_ { nullptr };
        sensor::Sensor* co2_sensor_ { nullptr };
        bool updated_before_ = false;
    };

} // namespace empty_sensor
} // namespace esphome