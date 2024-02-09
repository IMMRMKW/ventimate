
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

// #include "ssd1331_spi.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace my_component1 {

    class MyComponent : public ssd1331_base::SPISSD1331, public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_HIGH, spi::CLOCK_PHASE_TRAILING, spi::DATA_RATE_8MHZ> {
    public:
        // esphome::api::LambdaAction my_variable_setter;
        // float iaq_accuracy = 0.0;

        void setup() override;

    protected:
    };

} // namespace fusb302
} // namespace esphome
#endif // MY_CUSTOM_COMPONENT_H