#include "aqi.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"

namespace esphome {
namespace aqi {

    void AQI::setup()
    {
    }
    void AQI::loop()
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

    void AQI::update()
    {
        if (sensor_co2_index_) {
            if (sensor_co2_) {
                sensor_co2_index_->state = find_level(sensor_co2_->get_state(), co2_levels_);
                sensor_co2_index_->publish_state(sensor_co2_index_->state);
            }
        }

        if (sensor_pm_index_) {
            if (sensor_pm_1_0_ || sensor_pm_2_5_ || sensor_pm_10_) {
                uint8_t index = 0;
                if (sensor_pm_1_0_) {
                    uint8_t temp = find_level((uint16_t)sensor_pm_1_0_->get_state(), pm_1_0_levels_);
                    index = (temp > index) ? temp : index;
                    Serial.println(index);
                }
                if (sensor_pm_2_5_) {
                    uint8_t temp = find_level((uint16_t)sensor_pm_2_5_->get_state(), pm_2_5_levels_);
                    index = (temp > index) ? temp : index;
                    Serial.println(index);
                }
                if (sensor_pm_10_) {
                    uint8_t temp = find_level((uint16_t)sensor_pm_10_->get_state(), pm_10_levels_);
                    index = (temp > index) ? temp : index;
                    Serial.println(index);
                }
                sensor_pm_index_->state = index;
                sensor_pm_index_->publish_state(sensor_pm_index_->state);
            }
        }

        if (sensor_voc_index_) {
            if (sensor_voc_) {
                sensor_voc_index_->state = find_level((uint16_t)sensor_voc_->get_state(), voc_levels_);
                sensor_voc_index_->publish_state(sensor_voc_index_->state);
            }
        }
    }

    /**
     * @fn uint8_t find_level(uint16_t level, std::array<uint16_t, 5> levels)
     * @brief Helper function to determine air quality level
     * @todo complete doxigen documentation
     * @todo See also determine_aqi documentation
     */

    uint8_t AQI::find_level(uint16_t level, std::array<uint16_t, 5> levels)
    {
        for (uint8_t i = 0; i < levels.size(); i++) {
            if ((levels[i] - level) > 0) {
                return i;
            }
        }
        return levels.size();
    }

    void AQI::dump_config()
    {
    }
}
}