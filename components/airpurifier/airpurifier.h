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

        void set_sensor_power(sensor::Sensor* sensor) { sensor_power_ = sensor; }

        void set_sensor_co2_index(sensor::Sensor* sensor) { sensor_co2_index_ = sensor; }
        void set_sensor_pm_index(sensor::Sensor* sensor) { sensor_pm_index_ = sensor; }
        void set_sensor_voc_index(sensor::Sensor* sensor) { sensor_voc_index_ = sensor; }

        void set_max_power(int8_t max_power) { max_power_ = max_power; }

        void set_manual(bool manual) { manual_ = manual; }

        void set_purge(bool purge) { use_purge_ = purge; }

        void set_purge_duration(uint32_t purge_duration) { purge_duration_ = purge_duration * 1000; }

        void set_purge_interval(uint32_t purge_interval) { purge_interval_ = purge_interval * 1000; }

        void set_purge_power(uint8_t purge_power) { purge_power_ = purge_power; };

        void set_integral_gain(std::array<float, 6> constants);

        void set_proportional_gain(std::array<float, 6> constants) { P_ = constants; }

        void dump_config() override;

    private:
    protected:
        sensor::Sensor* sensor_co2_index_ { nullptr };
        sensor::Sensor* sensor_pm_index_ { nullptr };
        sensor::Sensor* sensor_voc_index_ { nullptr };
        sensor::Sensor* sensor_power_ { nullptr };

        bool manual_ = false;

        bool purge_ = false;
        bool use_purge_ = true;
        uint32_t purge_interval_ = 0;
        uint32_t prev_purge_ = 0;
        uint32_t purge_duration_ = 0;
        int8_t purge_power_ = 0;

        int8_t max_power_ = 100;
        std::array<float, 6> I_ = { 0.0f };
        std::array<float, 6> P_ = { 0.0f };

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