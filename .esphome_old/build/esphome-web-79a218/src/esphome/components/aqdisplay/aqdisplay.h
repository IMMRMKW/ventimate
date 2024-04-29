#ifndef AQDISPLAY_H
#define AQDISPLAY_H

#include <Arduino.h>
#undef WHITE
#undef BLACK
#include <Arduino_GFX_Library.h>
#undef WHITE
#undef BLACK
// Black and White are already defined in the Esphome core, so redefine:
#define GFX_BLACK RGB565_BLACK
#define GFX_WHITE RGB565_WHITE
#include "array"
#include "cmath"
#include "esphome/components/homeassistant/time/homeassistant_time.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/wifi/wifi_component.h"
#include "esphome/core/gpio.h"

#include "FreeSansBold10pt7b.h"
#include "FreeSansBold9pt7b.h"
#include "bitmaps.h"

#define BIG_FONT FreeSansBold9pt7b
#define MAX_LEVEL 5
#define LEVEL0 0x04A8
#define LEVEL1 0x8E27
#define LEVEL2 0xFF66
#define LEVEL3 0xFD88
#define LEVEL4 0xF4A3
#define LEVEL5 0xF800

#define RH_WIDTH 11
#define RH_HEIGHT 14

#define SEG_WIDTH 12
#define SEG_HEIGHT 8
#define PLOT_WIDTH 76
#define PLOT_HEIGHT 28
#define PLOT_X 19
#define PLOT_Y 36

namespace esphome {
namespace aqdisplay {

    /**
     * @enum status
     * @brief An enum for the state machine of the aqdisplay. It discriminates between a welcome state at startup, and a working state where measurement data is updated and presented continously
     */
    enum status {
        welcome = 0,
        working
    };

    /**
     * @enum connectivity
     * @brief An enum for the state machine of connectivity. It discriminates between none, wifi, and bluetooth
     */
    enum connectivity {
        none = 0,
        wifi,
        Bluetooth
    };

    static const char* const TAG = "aqdisplay";

    /**
     * @class Aqdisplay
     * @brief A class for visualizing air quality parameters on a SSD1331 oled screen
     * Create new font: https://rop.nl/truetype2gfx/
     * @todo document all one-liner functions (set/get) and class variables
     */

    class AQDISPLAY : public PollingComponent {
    public:
        void setup() override;
        void loop() override {};
        void update() override;
        void printTemp(int16_t x, int16_t y, float temp);
        void printComma(int16_t x, int16_t y);
        void printRH(int16_t x, int16_t y, float RH);

        void set_cs_pin(InternalGPIOPin* pin) { this->cs_pin_ = pin; }
        void set_dc_pin(InternalGPIOPin* pin) { this->dc_pin_ = pin; }
        void set_rst_pin(InternalGPIOPin* pin) { this->rst_pin_ = pin; }

        void set_clock(homeassistant::HomeassistantTime* clock) { clock_ = clock; }
        void set_network(wifi::WiFiComponent* network) { network_ = network; }

        void set_sensor_co2(sensor::Sensor* sensor) { sensor_co2_ = sensor; }
        void set_sensor_pm_1_0(sensor::Sensor* sensor) { sensor_pm_1_0_ = sensor; }
        void set_sensor_pm_2_5(sensor::Sensor* sensor) { sensor_pm_2_5_ = sensor; }
        void set_sensor_pm_10(sensor::Sensor* sensor) { sensor_pm_10_ = sensor; }
        void set_sensor_power(sensor::Sensor* sensor) { sensor_power_ = sensor; }
        void set_sensor_rh(sensor::Sensor* sensor) { sensor_rh_ = sensor; }
        void set_sensor_temp(sensor::Sensor* sensor) { sensor_temp_ = sensor; }
        void set_sensor_voc(sensor::Sensor* sensor) { sensor_voc_ = sensor; }

        void set_pm_1_0_levels(std::array<uint16_t, 5> levels) { pm_1_0_levels_ = levels; }
        void set_pm_2_5_levels(std::array<uint16_t, 5> levels) { pm_2_5_levels_ = levels; }
        void set_pm_10_levels(std::array<uint16_t, 5> levels) { pm_10_levels_ = levels; }
        void set_voc_levels(std::array<uint16_t, 5> levels) { voc_levels_ = levels; }
        void set_co2_levels(std::array<uint16_t, 5> levels) { co2_levels_ = levels; }

        void setPM(uint8_t level);
        void setCO2(uint8_t level);
        void setVOC(uint8_t level);
        void setTime(int16_t x, int16_t y, ESPTime current_time);
        void setConnectivity(uint8_t connect);
        void setFan(int16_t x, int16_t y, uint8_t level);

    private:
        InternalGPIOPin* cs_pin_ { nullptr };
        InternalGPIOPin* dc_pin_ { nullptr };
        InternalGPIOPin* rst_pin_ { nullptr };
        homeassistant::HomeassistantTime* clock_ { nullptr };
        sensor::Sensor* sensor_co2_ { nullptr };
        sensor::Sensor* sensor_pm_1_0_ { nullptr };
        sensor::Sensor* sensor_pm_2_5_ { nullptr };
        sensor::Sensor* sensor_pm_10_ { nullptr };
        sensor::Sensor* sensor_power_ { nullptr };
        sensor::Sensor* sensor_rh_ { nullptr };
        sensor::Sensor* sensor_temp_ { nullptr };
        sensor::Sensor* sensor_voc_ { nullptr };
        wifi::WiFiComponent* network_ { nullptr };

        std::array<uint16_t, 5> pm_1_0_levels_ = { 0 };
        std::array<uint16_t, 5> pm_2_5_levels_ = { 0 };
        std::array<uint16_t, 5> pm_10_levels_ = { 0 };
        std::array<uint16_t, 5> voc_levels_ = { 0 };
        std::array<uint16_t, 5> co2_levels_ = { 0 };

        uint8_t find_level(uint16_t level, std::array<uint16_t, 5> levels);

        uint16_t colors[6] = { LEVEL0, LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5 };

        Arduino_DataBus* bus;
        Arduino_GFX* gfx;

        int8_t pm_level = -1;
        int8_t CO2_level = -1;
        int8_t VOC_level = -1;
        int8_t fan_level = -1;
        float temp_level = 0;
        uint8_t rh_level = 0;
        uint8_t fan_level_ = 255;

        bool single_digits = false;
        bool connectivity_shown = false;

        int16_t get_width_difference(const char* str1, const char* str2);
        void fill_textBounds_with_black(const char* str, int16_t x, int16_t y, int16_t* x1, int16_t* y1, uint16_t* w, uint16_t* h);
        void drawGraph();
        void drawRow(uint8_t row, uint8_t new_level, int8_t prev_level);
        void drawLevel(uint8_t level, uint8_t row, bool flag);

        uint8_t state_ = welcome;
        uint8_t counter_ = 0;
        bool graph_shown_ = false;
    };
}

}

#endif