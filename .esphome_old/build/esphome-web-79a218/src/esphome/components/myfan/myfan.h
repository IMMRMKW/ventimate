#pragma once
#include "Arduino.h"
#include "airpurifier.h"
#include "esphome/components/switch/switch.h"
#include "esphome/core/component.h"
#include "esphome/core/gpio.h"

namespace esphome {
namespace myfan {

    /**
     * @class MYFAN
     * @brief A class that extends the airpurifier class. It is the physical implementation of the airpurifier so to say.
     * @todo document all one-liner functions (set/get) and class variables
     * @todo Think of new name!
     * @todo implement dump_config function
     * @todo remove all print functions
     * @todo create doxygen documentation for all class functions in .cpp file.
     */

    class MYFAN : public airpurifier::AIRPURIFIER {
    public:
        void setup() override;
        void set_power_en_pin(InternalGPIOPin* pin) { this->power_en_pin_ = pin; }
        void set_power_pwm_pin(InternalGPIOPin* pin) { this->power_pwm_pin_ = pin; }
        void set_fan_pwm_pin(InternalGPIOPin* pin) { this->fan_pwm_pin_ = pin; }
        void set_tacho_pin(InternalGPIOPin* pin) { this->tacho_pin_ = pin; }
        void set_power_pwm_channel(uint8_t channel) { power_pwm_channel_ = channel; }
        void set_fan_pwm_channel(uint8_t channel) { fan_pwm_channel_ = channel; }

        void set_fan_pwm_flag(bool flag) { fan_pwm_flag_ = flag; }
        void set_max_voltage(float setpoint) { max_voltage_ = setpoint; }
        void set_min_voltage(float setpoint) { min_voltage_ = setpoint; }

        void set_fan_pwm_frequency(uint32_t setpoint) { fan_pwm_frequency_ = setpoint; }
        void set_min_duty_cycle(float setpoint) { min_duty_cycle_ = setpoint; }

        void dump_config() override;

    private:
        void set_power(uint8_t power) override;
        float voltage_setpoint(float min_voltage, float max_voltage, uint8_t power);
        float max_voltage_ = 0;
        float min_voltage_ = 0;
        const float max_output_voltage_ = 12;
        const uint8_t resolution_ = 8;
        const uint32_t power_pwm_frequency = 50000;
        uint32_t fan_pwm_frequency_ = 0;
        float min_duty_cycle_ = 0;
        uint8_t power_pwm_channel_ = 0;
        uint8_t fan_pwm_channel_ = 0;
        bool fan_pwm_flag_ = false;

    protected:
        InternalGPIOPin* power_en_pin_ { nullptr };
        InternalGPIOPin* power_pwm_pin_ { nullptr };
        InternalGPIOPin* fan_pwm_pin_ { nullptr };
        InternalGPIOPin* tacho_pin_ { nullptr };
    };

} // namespace myfan
} // namespace esphome