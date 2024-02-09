
/**
 * USB Power Delivery integration in ESPHome
 *
 * Authors: groothuisss & IMMRMKW
 */

#ifndef MY_CUSTOM_COMPONENT_H
#define MY_CUSTOM_COMPONENT_H

#pragma once

#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/log.h"
#include <Arduino.h>

namespace esphome {
namespace my_component1 {

    class MyComponent : public Component {
    public:
        uint8_t _level = 0;
        // esphome::api::LambdaAction my_variable_setter;
        // float iaq_accuracy = 0.0;

        void
        setup() override
        {
            // my_variable_setter = esphome::api::LambdaAction(this {
            //     iaq_accuracy = value;
            // });
            // this->add_action(my_variable_setter);
            //  This will be called once to set up the component
            //  Think of it as the `setup()` call in Arduino
        }

        void loop() override
        {
            const int32_t now = millis();
            this->last_update_ = now;
            if (now - this->last_update_ > this->update_interval_) {
                ESP_LOGD("custom", "The value of sensor is: %f", _level);
            }
        }
        void set_iaq_accuracy(uint8_t level)
        {
            _level = level;
        }

        void set_update_interval(uint32_t val) { update_interval_ = val; };

    protected:
        uint32_t update_interval_ { 0 };
        uint32_t last_update_ { 0 };
    };

#endif // MY_CUSTOM_COMPONENT_H
} // namespace fusb302
} // namespace esphome