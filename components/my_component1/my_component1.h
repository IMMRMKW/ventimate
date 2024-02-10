
/**
 * USB Power Delivery integration in ESPHome
 *
 * Authors: groothuisss & IMMRMKW
 */

#pragma once

#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/log.h"
#include <Arduino.h>

// #include "Arduino_GFX_Library.h"
#include "esphome/components/display/display.h"
#include "esphome/components/spi/spi.h"
#include "esphome/components/ssd1331_spi/ssd1331_spi.h"

namespace esphome {
namespace my_component1 {

    class MyComponent : public ssd1331_spi::SPISSD1331 {
    public:
        void setup() override;
        void printComma(int16_t x, int16_t y);
        // esphome::api::LambdaAction my_variable_setter;
        // float iaq_accuracy = 0.0;

    protected:
    };

} // namespace fusb302
} // namespace esphome
