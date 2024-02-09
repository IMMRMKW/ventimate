#include "my_component1.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"

namespace esphome {
namespace my_component1 {
    static const char* const TAG = "my_component1";

    void MyComponent::setup()
    {
        ESP_LOGCONFIG(TAG, "Setting up SPI SSD1331...");
        this->spi_setup();
        this->dc_pin_->setup(); // OUTPUT
        if (this->cs_)
            this->cs_->setup(); // OUTPUT

        this->init_reset_();
        delay(500); // NOLINT
        SSD1331::setup();
    }