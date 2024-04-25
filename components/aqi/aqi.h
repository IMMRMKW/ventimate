#ifndef AQI_H
#define AQI_H

#include "Arduino.h"
#include "array"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

namespace esphome {
namespace airpurifier {
    static const char* const TAG = "airpurifier";

    /**
     * @class AQI
     * @brief A class that implements air quality index.
     * @todo document all one-liner functions (set/get) and class variables
     */

    class AQI : public PollingComponent {
    public:
        void setup() override;
        void loop() override;
        void update() override;

        void set_sensor_co2_index(sensor::Sensor* sensor) { sensor_co2_index_ = sensor; }

        void set_sensor_pm_index(sensor::Sensor* sensor) { sensor_pm_index_ = sensor; }

        void set_sensor_voc_index(sensor::Sensor* sensor) { sensor_voc_index_ = sensor; }

        void set_sensor_voc(sensor::Sensor* sensor) { sensor_voc_ = sensor; }

        void set_sensor_pm_1_0(sensor::Sensor* sensor) { sensor_pm_1_0_ = sensor; }

        void set_sensor_pm_2_5(sensor::Sensor* sensor) { sensor_pm_2_5_ = sensor; }

        void set_sensor_pm_10(sensor::Sensor* sensor) { sensor_pm_10_ = sensor; }

        void set_sensor_co2(sensor::Sensor* sensor) { sensor_co2_ = sensor; }

        void set_pm_2_5_levels(std::array<uint16_t, 5> levels) { pm_2_5_levels_ = levels; }

        void set_pm_10_levels(std::array<uint16_t, 5> levels) { pm_10_levels_ = levels; }

        void set_voc_levels(std::array<uint16_t, 5> levels) { voc_levels_ = levels; }

        void set_co2_levels(std::array<uint16_t, 5> levels) { co2_levels_ = levels; }

        void dump_config() override;

    private:
    protected:
        sensor::Sensor* sensor_index { nullptr };
        sensor::Sensor* sensor_co2_index_ { nullptr };
        sensor::Sensor* sensor_pm_index_ { nullptr };
        sensor::Sensor* sensor_voc_index_ { nullptr };
        sensor::Sensor* sensor_co2_ { nullptr };
        sensor::Sensor* sensor_pm_1_0_ { nullptr };
        sensor::Sensor* sensor_pm_2_5_ { nullptr };
        sensor::Sensor* sensor_pm_10_ { nullptr };
        sensor::Sensor* sensor_voc_ { nullptr };

        std::array<uint16_t, 5> pm_2_5_levels_ = { 0 };
        std::array<uint16_t, 5> pm_10_levels_ = { 0 };
        std::array<uint16_t, 5> voc_levels_ = { 0 };
        std::array<uint16_t, 5> co2_levels_ = { 0 };

        uint8_t calculate_aqi();
        uint8_t find_level(uint16_t level, std::array<uint16_t, 5> levels);
        };

} // namespace aqi
} // namespace esphome

#endif