
/**
 * USB Power Delivery integration in ESPHome
 *
 * Authors: groothuisss & IMMRMKW
 */

#include "fusb302.h"
#define PIN_LED 27
namespace esphome {
namespace fusb302 {

    static const char* TAG = "fusb302.component";

    class PD_UFP_c PD_UFP;

    void FUSB302::setup()
    {
        Wire.begin();

        auto maxPowerSettingPDProtocol = PD_POWER_OPTION_MAX_5V;
        switch (maximum_supply_voltage_) {
        case PD5V:
            maxPowerSettingPDProtocol = PD_POWER_OPTION_MAX_5V;
            break;
        case PD9V:
            maxPowerSettingPDProtocol = PD_POWER_OPTION_MAX_9V;
            break;
        case PD12V:
            maxPowerSettingPDProtocol = PD_POWER_OPTION_MAX_12V;
            break;
        case PD15V:
            maxPowerSettingPDProtocol = PD_POWER_OPTION_MAX_15V;
            break;
        case PD20V:
            maxPowerSettingPDProtocol = PD_POWER_OPTION_MAX_20V;
            break;
        }

        PD_UFP.set_fusb302_int_pin(this->interrupt_pin_->get_pin());

        PD_UFP.init(maxPowerSettingPDProtocol);

        unsigned long timer = millis();
        while (!PD_UFP.is_PPS_ready() && millis() - timer < TIME_OUT) {
            PD_UFP.run();
        }

        timer = millis();
        while (!PD_UFP.is_power_ready() && millis() - timer < TIME_OUT) {
            PD_UFP.run();
        }
        if (!PD_UFP.is_PPS_ready() && !PD_UFP.is_power_ready()) {
            ESP_LOGD(TAG, "ERROR: Neither PPS_ready or power_ready returned True.");
        }
    }

    void FUSB302::update()
    {
        PD_UFP.run();
    }

    void FUSB302::dump_config()
    {
        ESP_LOGCONFIG(TAG, "FUSB302:");

        switch (maximum_supply_voltage_) {
        case PD5V:
            ESP_LOGCONFIG(TAG, "  Maximum supply voltage: 5V");
            break;
        case PD9V:
            ESP_LOGCONFIG(TAG, "  Maximum supply voltage: 9V");
            break;
        case PD12V:
            ESP_LOGCONFIG(TAG, "  Maximum supply voltage: 12V");
            break;
        case PD15V:
            ESP_LOGCONFIG(TAG, "  Maximum supply voltage: 15V");
            break;
        case PD20V:
            ESP_LOGCONFIG(TAG, "  Maximum supply voltage: 20V");
            break;
        }

        LOG_PIN("  Interrupt pin: ", this->interrupt_pin_);
    }

} // namespace fusb302
} // namespace esphome