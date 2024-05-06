#ifndef AIRQUALITYDISPLAY_H
#define AIRQUALITYDISPLAY_H

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
#include "bitmaps.h"

#define MAX_LEVEL 5
#define COLOR_LEVEL0 0x04A8
#define COLOR_LEVEL1 0x8E27
#define COLOR_LEVEL2 0xFF66
#define COLOR_LEVEL3 0xFD88
#define COLOR_LEVEL4 0xF4A3
#define COLOR_LEVEL5 0xF800

#define RELATIVEHUMIDITY_WIDTH 11
#define RELATIVEHUMIDITY_HEIGHT 14

#define SEG_WIDTH 12
#define SEG_HEIGHT 8
#define PLOT_WIDTH 76
#define PLOT_HEIGHT 28
#define PLOT_X 19
#define PLOT_Y 36

namespace esphome {
namespace airqualitydisplay {

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
        bluetooth
    };

    static const char* const TAG = "airqualitydisplay";

    class AirQualityDisplay : public PollingComponent {
    public:
        void setup() override;
        void loop() override;
        void update() override;
        void print_temperature(int16_t x, int16_t y, float temperature);
        void print_comma(int16_t x, int16_t y);
        void print_humidity(int16_t x, int16_t y, float humidity);

        void set_cs_pin(InternalGPIOPin* pin) { this->cs_pin_ = pin; }
        void set_dc_pin(InternalGPIOPin* pin) { this->dc_pin_ = pin; }
        void set_rst_pin(InternalGPIOPin* pin) { this->rst_pin_ = pin; }

        void set_clock(homeassistant::HomeAssistantTime* clock) { clock_ = clock; }
        void set_network(wifi::WiFiComponent* network) { network_ = network; }

        void set_sensor_co2(sensor::Sensor* sensor) { sensor_co2_ = sensor; }
        void set_sensor_pm_1_0(sensor::Sensor* sensor) { sensor_pm_1_0_ = sensor; }
        void set_sensor_pm_2_5(sensor::Sensor* sensor) { sensor_pm_2_5_ = sensor; }
        void set_sensor_pm_10(sensor::Sensor* sensor) { sensor_pm_10_ = sensor; }
        void set_sensor_power(sensor::Sensor* sensor) { sensor_power_ = sensor; }
        void set_sensor_humidity(sensor::Sensor* sensor) { sensor_humidity_ = sensor; }
        void set_sensor_temperature(sensor::Sensor* sensor) { sensor_temperature_ = sensor; }
        void set_sensor_voc(sensor::Sensor* sensor) { sensor_voc_ = sensor; }

        void set_pm_1_0_levels(std::array<uint16_t, 5> levels) { pm_1_0_levels_ = levels; }
        void set_pm_2_5_levels(std::array<uint16_t, 5> levels) { pm_2_5_levels_ = levels; }
        void set_pm_10_levels(std::array<uint16_t, 5> levels) { pm_10_levels_ = levels; }
        void set_voc_levels(std::array<uint16_t, 5> levels) { voc_levels_ = levels; }
        void set_co2_levels(std::array<uint16_t, 5> levels) { co2_levels_ = levels; }

        void set_pm(uint8_t level);
        void set_co2(uint8_t level);
        void set_voc(uint8_t level);
        void set_time(ESPTime current_time);
        void set_connectivity(uint8_t connect);
        void set_fan(bool show, uint8_t level);

    private:
        homeassistant::HomeAssistantTime* clock_ { nullptr };
        wifi::WiFiComponent* network_ { nullptr };
        sensor::Sensor* sensor_co2_ { nullptr };
        sensor::Sensor* sensor_pm_1_0_ { nullptr };
        sensor::Sensor* sensor_pm_2_5_ { nullptr };
        sensor::Sensor* sensor_pm_10_ { nullptr };
        sensor::Sensor* sensor_power_ { nullptr };
        sensor::Sensor* sensor_humidity_ { nullptr };
        sensor::Sensor* sensor_temperature_ { nullptr };
        sensor::Sensor* sensor_voc_ { nullptr };

        std::array<uint16_t, 5> pm_1_0_levels_ = { 0 };
        std::array<uint16_t, 5> pm_2_5_levels_ = { 0 };
        std::array<uint16_t, 5> pm_10_levels_ = { 0 };
        std::array<uint16_t, 5> voc_levels_ = { 0 };
        std::array<uint16_t, 5> co2_levels_ = { 0 };

        uint8_t find_graph_level(uint16_t level, std::array<uint16_t, 5> levels);

        uint16_t colors[6] = { COLOR_LEVEL0, COLOR_LEVEL1, COLOR_LEVEL2, COLOR_LEVEL3, COLOR_LEVEL4, COLOR_LEVEL5 };

        Arduino_DataBus* bus;
        Arduino_GFX* gfx;

        int8_t pm_level_ = -1;
        int8_t co2_level_ = -1;
        int8_t voc_level_ = -1;
        int8_t fan_level_ = -1;
        float temperature_level_ = 0;
        uint8_t humidity_level_ = 0;

        bool is_showing_connectivity_ = false;

        void draw_graph();
        void draw_fan_square();
        void draw_row(uint8_t row, uint8_t new_level, int8_t prev_level);
        void draw_graph_level(uint8_t level, uint8_t row, bool flag);

        uint8_t state_ = welcome;
        uint8_t counter_ = 0;
        bool is_showing_graph_ = false;

    protected:
        InternalGPIOPin* cs_pin_ { nullptr };
        InternalGPIOPin* dc_pin_ { nullptr };
        InternalGPIOPin* rst_pin_ { nullptr };
    };
}

}

#endif