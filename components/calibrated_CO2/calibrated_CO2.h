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
        void dump_config() override;

    private:
        float getCalibrationValue();
        _outDoorCO2 = 0;

    protected:
        sensor::Sensor* sensor_ { nullptr };
    };

} // namespace empty_sensor
} // namespace esphome