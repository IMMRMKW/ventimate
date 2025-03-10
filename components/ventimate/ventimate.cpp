#include "ventimate.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ventimate {
    static const char* const TAG = "ventimate";
    void VENTIMATE::setup()
    {
        power_en_pin_->pin_mode(gpio::FLAG_OUTPUT);
        power_en_pin_->digital_write(true);
        power_pwm_pin_->pin_mode(gpio::FLAG_OUTPUT);

        if (fan_pwm_flag_) {
            fan_pwm_pin_->pin_mode(gpio::FLAG_OUTPUT);
            ledcSetup(fan_pwm_channel_, fan_pwm_frequency_, resolution_);
            ledcAttachPin(fan_pwm_pin_->get_pin(), fan_pwm_channel_);
            ledcWrite(fan_pwm_channel_, 0);

            power_pwm_pin_->digital_write(true);
        } else {
            ledcSetup(power_pwm_channel_, power_pwm_frequency, resolution_);
            ledcAttachPin(power_pwm_pin_->get_pin(), power_pwm_channel_);
            ledcWrite(power_pwm_channel_, 0);
        }
    }

    void VENTIMATE::set_power(uint8_t power)
    {
        Serial.print("Set power: ");
        Serial.println(power);
        switch (fan_pwm_flag_) {
        case true:

            if (power == 0) {
                ledcWrite(fan_pwm_channel_, 0);
            } else {
                float min_voltage = min_duty_cycle_ * max_output_voltage_;
                uint32_t setpoint
                    = (voltage_setpoint(min_voltage, max_voltage_, power) / max_output_voltage_) * (pow(2, resolution_) - 1);
                ledcWrite(fan_pwm_channel_, setpoint);
            }
            break;
        case false:
            if (power == 0) {
                ledcWrite(power_pwm_channel_, 0);
            } else {
                uint32_t setpoint
                    = (voltage_setpoint(min_voltage_, max_voltage_, power) / max_output_voltage_) * (pow(2, resolution_) - 1);
                ledcWrite(power_pwm_channel_, setpoint);
            }
            break;
        }
    }

    float VENTIMATE::voltage_setpoint(float min_voltage, float max_voltage, uint8_t power)
    {
        Serial.print("Voltage setpoint ");
        Serial.println(min_voltage_ + ((float)power / 100) * (max_voltage_ - min_voltage_));
        return min_voltage_ + ((float)power / 100) * (max_voltage_ - min_voltage_);
    }

    void VENTIMATE::dump_config()
    {
        Serial.println("Number changed");
    }
}
}