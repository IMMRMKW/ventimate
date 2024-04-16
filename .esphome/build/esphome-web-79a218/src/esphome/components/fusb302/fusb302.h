
/**
 * USB Power Delivery integration in ESPHome
 *
 * Authors: groothuisss & IMMRMKW
 */

#pragma once

#include "PD_UFP.h"
#include "PD_UFP_Protocol.h"
#include "Wire.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/log.h"
#include <Arduino.h>

#define TIME_OUT 1000

namespace esphome {
namespace fusb302 {

    enum MaximumSupplyVoltage {
        PD5V,
        PD9V,
        PD12V,
        PD15V,
        PD20V
    };

    class FUSB302 : public PollingComponent, public i2c::I2CDevice {
    public:
        void set_maximum_supply_voltage(MaximumSupplyVoltage maximum_supply_voltage) { maximum_supply_voltage_ = maximum_supply_voltage; }
        void set_interrupt_pin(InternalGPIOPin* pin) { this->interrupt_pin_ = pin; }

        void setup() override;
        void update() override;
        void dump_config() override;

    protected:
        MaximumSupplyVoltage maximum_supply_voltage_ { PD5V };
        InternalGPIOPin* interrupt_pin_;
    };
} // namespace fusb302
} // namespace esphome