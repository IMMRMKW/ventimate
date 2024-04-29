#include "aqi.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"

namespace esphome {
namespace aqi {

    void aqi::setup()
    {
    }
    void aqi::loop()
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

    void aqi::update()
    {
        if (sensor_co2_index_) {
            if (sensor_co2_) {
                sensor_co2_index_->state = find_level(sensor_co2_.get_state(), co2_levels_);
            }
        }

        if (sensor_pm_index_) {
            if (sensor_pm_1_0_ || sensor_pm_2_5_ || sensor_pm_10_) {
                uint8_t index = 0;
                if (sensor_pm_1_0_) {
                    uint8_t temp = find_level((uint16_t)sensor_pm_1_0_->get_state(), pm_1_0_levels_);
                    index = (temp > index) ? temp : index;
                }
                if (sensor_pm_2_5_) {
                    uint8_t temp = find_level((uint16_t)sensor_pm_2_5_->get_state(), pm_2_5_levels_);
                    index = (temp > index) ? temp : index;
                }
                if (sensor_pm_10_) {
                    uint8_t temp = find_level((uint16_t)sensor_pm_10_->get_state(), pm_10_levels_);
                    index = (temp > index) ? temp : index;
                }
                sensor_pm_index_->state = index;
            }
        }

        if (sensor_voc_index_) {
            if (sensor_voc_) {
                uint16_t level = (uint16_t)sensor_voc_->get_state();
                uint8_t temp = sensor_voc_index->state = find_level(level, voc_levels_);
            }
        }
    }

    /**
     * @fn uint8_t find_level(uint16_t level, std::array<uint16_t, 5> levels)
     * @brief Helper function to determine air quality level
     * @todo complete doxigen documentation
     * @todo See also determine_aqi documentation
     */

    uint8_t aqi::find_level(uint16_t level, std::array<uint16_t, 5> levels)
    {
        for (uint8_t i = 0; i < levels.size(); i++) {
            if ((levels[i] - level) > 0) {
                return i;
            }
        }
        return levels.size();
    }