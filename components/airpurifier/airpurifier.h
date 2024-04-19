#ifndef AIRPURIFIER_H
#define AIRPURIFIER_H

#include "Arduino.h"
#include "array"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

namespace esphome {
namespace airpurifier {
    static const char* const TAG = "airpurifier";

    /**
     * @class Airpurifier
     * @brief A class that implements airpufier functions.
     * @todo document all one-liner functions (set/get) and class variables
     */

    class AIRPURIFIER : public PollingComponent {
    public:
        void setup() override;
        void loop() override;
        void update() override;

        void set_sensor_voc(sensor::Sensor* sensor) { sensor_voc_ = sensor; }

        void set_sensor_pm_2_5(sensor::Sensor* sensor) { sensor_pm_2_5_ = sensor; }

        void set_sensor_pm_10(sensor::Sensor* sensor) { sensor_pm_10_ = sensor; }

        void set_sensor_co2(sensor::Sensor* sensor) { sensor_co2_ = sensor; }

        void set_sensor_power(sensor::Sensor* sensor) { sensor_power_ = sensor; }

        void set_max_power(int8_t max_power) { max_power_ = max_power; }

        void set_manual(bool manual) { manual_ = manual; }

        void set_purge(bool purge) { use_purge_ = purge; }

        void set_purge_duration(uint32_t purge_duration) { purge_duration_ = purge_duration * 1000; }

        void set_purge_interval(uint32_t purge_interval) { purge_interval_ = purge_interval * 1000; }

        void set_purge_power(uint8_t purge_power) { purge_power_ = purge_power; };

        void set_integral_gain(std::array<float, 5> constants);

        void set_proportional_gain(std::array<float, 5> constants) { P_ = constants; }

        void set_pm_2_5_levels(std::array<uint16_t, 5> levels) { pm_2_5_levels_ = levels; }

        void set_pm_10_levels(std::array<uint16_t, 5> levels) { pm_10_levels_ = levels; }

        void set_voc_levels(std::array<uint16_t, 5> levels) { voc_levels_ = levels; }

        void set_co2_levels(std::array<uint16_t, 5> levels) { co2_levels_ = levels; }

        void dump_config() override;

    private:
    protected:
        sensor::Sensor* sensor_co2_ { nullptr };
        sensor::Sensor* sensor_pm_2_5_ { nullptr };
        sensor::Sensor* sensor_pm_10_ { nullptr };
        sensor::Sensor* sensor_power_ { nullptr };
        sensor::Sensor* sensor_voc_ { nullptr };

        std::array<uint16_t, 5> pm_2_5_levels_ = { 0 };
        std::array<uint16_t, 5> pm_10_levels_ = { 0 };
        std::array<uint16_t, 5> voc_levels_ = { 0 };
        std::array<uint16_t, 5> co2_levels_ = { 0 };

        bool manual_ = false;

        bool purge_ = false;
        bool use_purge_ = true;
        uint32_t purge_interval_ = 0;
        uint32_t prev_purge_ = 0;
        uint32_t purge_duration_ = 0;
        int8_t purge_power_ = 0;

        int8_t max_power_ = 100;
        std::array<float, 5> I_ = { 0.0f };
        std::array<float, 5> P_ = { 0.0f };

        uint32_t prev_time_ = 0;
        float error_Int_ = 0;
        uint8_t calculate_aqi();
        uint8_t find_level(uint16_t level, std::array<uint16_t, 5> levels);
        virtual void set_power(uint8_t power);
        uint8_t power_ = 0;
    };

} // namespace empty_sensor
} // namespace esphome

#endif