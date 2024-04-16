#include "airpurifier.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"

namespace esphome {
namespace airpurifier {

    void AIRPURIFIER::setup()
    {
    }
    void AIRPURIFIER::loop()
    {
    }
    void AIRPURIFIER::update()
    {
        Serial.println("Airpurifier update");
        uint32_t cur_time = millis();
        uint8_t power_setpoint = 0;

        if (!manual_) {
            // Simple controller that determines the required fan power if the airpurifier is on automatic mode.
            int8_t index = calculate_aqi();
            if (index > 0) {
                float diff_time = float(cur_time - prev_time_) / 1000.0;

                error_Int_ = I_[index] * diff_time * float(index) + error_Int_;

                error_Int_ = (error_Int_ > max_power_) ? max_power_ : error_Int_;

                float temp = error_Int_ + P_[index] * index;
                power_setpoint = (temp > max_power_) ? max_power_ : temp;
            }
            prev_time_ = cur_time;
        } else {
            // If not on automatic mode, simply use max fan power.
            power_setpoint = max_power_;
        }

        // Purging is an action to remove the current air around the sensors to get a more accurate image
        // of the air quality in the whole room.
        if (use_purge_) {
            if (!manual_ && purge_) {
                if (cur_time - prev_purge_ > purge_duration_) {
                    Serial.println(cur_time - prev_purge_);
                    purge_ = false;
                } else {
                    power_setpoint = (purge_power_ > max_power_) ? max_power_ : purge_power_;
                }
            } else if ((cur_time - prev_purge_ > purge_interval_) && power_setpoint < purge_power_ && !manual_) {
                purge_ = true;
                prev_purge_ = cur_time;
                power_setpoint = (purge_power_ > max_power_) ? max_power_ : purge_power_;
            }
        }
        set_power(power_setpoint);

        sensor_power_->state = power_setpoint;
        sensor_power_->publish_state(sensor_power_->state);
    }

    uint8_t AIRPURIFIER::calculate_aqi()
    {
        uint8_t index = 0;
        if (sensor_co2_) {
            uint16_t level = (uint16_t)sensor_co2_->get_state();
            uint8_t temp = find_level(level, co2_levels_);
            index = (temp > index) ? temp : index;
        }
        if (sensor_pm_2_5_) {
            uint16_t level = (uint16_t)sensor_pm_2_5_->get_state();
            uint8_t temp = find_level(level, pm_2_5_levels_);
            index = (temp > index) ? temp : index;
        }
        if (sensor_pm_10_) {
            uint16_t level = (uint16_t)sensor_pm_10_->get_state();
            uint8_t temp = find_level(level, pm_10_levels_);
            index = (temp > index) ? temp : index;
        }
        if (sensor_voc_) {
            uint16_t level = (uint16_t)sensor_voc_->get_state();
            uint8_t temp = find_level(level, voc_levels_);
            index = (temp > index) ? temp : index;
        }
        return index;
    }

    void AIRPURIFIER::dump_config()
    {
        Serial.println("Number changed");
    }

    uint8_t AIRPURIFIER::find_level(uint16_t level, std::array<uint16_t, 5> levels)
    {
        for (uint8_t i = 0; i < levels.size(); i++) {
            if ((levels[i] - level) > 0) {
                return i;
            }
        }
        return levels.size();
    }

    void AIRPURIFIER::set_power(uint8_t power)
    {
    }

    void AIRPURIFIER::set_integral_gain(std::array<float, 5> constants)
    {
        for (uint8_t i = 0; i < constants.size(); i++) {
            I_[i] = 100 / (i * constants[i]);
        }
    }
}
}
