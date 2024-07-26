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

    /**
     * @fn void update()
     * @brief Updates fan power based on whether the manual/auto setting.
     * @todo error_Int is based on index, but can simply be I_[index]*diff_time, where I_contains the time constant to reach 100% power
     * @todo remove prints
     * @todo more appropriate name for max_power_
     * @todo add more complete explanation in brief
     */

    void AIRPURIFIER::update()
    {
        Serial.println("Airpurifier update");
        uint32_t cur_time = millis();
        uint8_t power_setpoint = 0;

        if (!manual_) {
            // Simple controller that determines the required fan power if the airpurifier is on automatic mode.
            int8_t index = calculate_aqi();
            Serial.println(index);
            if (index > 0) {
                // convert milliseconds to seconds
                float diff_time = float(cur_time - prev_time_) / 1000.0;

                error_Int_ = I_[index] * diff_time + error_Int_;

                error_Int_ = (error_Int_ > max_power_) ? max_power_ : error_Int_;

                float temp = error_Int_ + P_[index];

                power_setpoint = (temp > max_power_) ? max_power_ : temp;
            }
            // reset integrator if air quality index is 0
            if (index == 0) {
                error_Int_ = 0;
                power_setpoint = (P_[index] > max_power_) ? max_power_ : P_[index];
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

    /**
     * @fn uint8_t calculate_aqi()
     * @brief Calculates air quality index based on sensor readouts and previously determined thresholds for each sensor.
     * @todo Decide if an external aqi is made which serves both the display and the purifier
     * @todo Create @brief description
     */

    uint8_t AIRPURIFIER::calculate_aqi()
    {
        uint8_t index = 0;
        if (sensor_co2_index_) {
            uint8_t index_co2 = (uint8_t)sensor_co2_index_->get_state();
            index = (index_co2 > index) ? index_co2 : index;
        }

        if (sensor_pm_index_) {
            uint8_t index_pm = (uint8_t)sensor_pm_index_->get_state();
            index = (index_pm > index) ? index_pm : index;
        }

        if (sensor_voc_index_) {
            uint8_t index_voc = (uint8_t)sensor_voc_index_->get_state();
            index = (index_voc > index) ? index_voc : index;
        }
        return index;
    }

    /**
     * @fn void dump_config()
     * @brief
     * @todo implement as 0 in header file, override in derived classes
     */

    void AIRPURIFIER::dump_config()
    {
        Serial.println("Number changed");
    }

    /**
     * @fn uint8_t find_level(uint16_t level, std::array<uint16_t, 5> levels)
     * @brief Helper function to determine air quality level
     * @todo complete doxigen documentation
     * @todo See also determine_aqi documentation
     */

    uint8_t AIRPURIFIER::find_level(uint16_t level, std::array<uint16_t, 5> levels)
    {
        for (uint8_t i = 0; i < levels.size(); i++) {
            if ((levels[i] - level) > 0) {
                return i;
            }
        }
        return levels.size();
    }

    /**
     * @fn void set_power(uint8_t power)
     * @brief Sets fan power
     * @todo remove from here, implement as zero in header file
     */

    void AIRPURIFIER::set_power(uint8_t power)
    {
    }

    /**
     * @fn void set_integral_gain(std::array<float, 5> constants)
     * @brief Sets time constant
     * @todo name can be changed once controller is changed to have a time constant instead of a strict dt*error*gain
     */

    void AIRPURIFIER::set_integral_gain(std::array<float, 6> constants)
    {
        for (uint8_t i = 0; i < constants.size(); i++) {
            I_[i] = 100 / constants[i];
        }
    }
}
}
