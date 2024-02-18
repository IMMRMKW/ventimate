#pragma once
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include <HTTPClient.h>

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

    private:
        float getCalibrationValue();
        float _outDoorCO2 = 400;

    protected:
        sensor::Sensor* sensor_ { nullptr };
        sensor::Sensor* co2_sensor_ { nullptr };
    };

} // namespace empty_sensor
} // namespace esphome