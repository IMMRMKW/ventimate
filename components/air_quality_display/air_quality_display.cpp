#include "air_quality_display.h"

namespace esphome {
namespace airqualitydisplay {

    void AirQualityDisplay::setup()
    {

        bus = new Arduino_HWSPI(dc_pin_->get_pin(), cs_pin_->get_pin() /* CS */);
        gfx = new Arduino_SSD1331(bus, rst_pin_->get_pin() /* RST */, 0 /* rotation */);
        gfx->begin();
        dc_pin_->pin_mode(gpio::FLAG_OUTPUT);
        gfx->fillScreen(GFX_BLACK);
        // gfx->draw16bitRGBBitmap(0, 0, tchnlgyst_96x19, 96, 19);

        // gfx->fillScreen(GFX_BLACK);
        // drawGraph();
    }

    void AirQualityDisplay::loop()
    {
    }

    void AirQualityDisplay::update()
    {
        switch (state_) {
        case welcome: {
            gfx->draw16bitRGBBitmap(0, 0, bitmap_welcome, 96, 64);
            counter_++;
            if (counter_ > 3) {
                state_ = working;
            }
            break;
        }
        case working:
            Serial.println("Display update");
            if (!this->is_showing_graph_) {
                gfx->fillScreen(GFX_BLACK);
                draw_graph();
                this->is_showing_graph_ = true;
            }
            if (clock_) {
                set_time(clock_->now());
            }

            if (network_) {
                if (network_->is_connected()) {
                    if (!this->is_showing_connectivity_) {
                        set_connectivity(wifi);
                        this->is_showing_connectivity_ = true;
                    }
                } else {
                    if (!this->is_showing_connectivity_) {
                        set_connectivity(wifi);
                        this->is_showing_connectivity_ = true;
                    } else {
                        set_connectivity(none);
                        this->is_showing_connectivity_ = false;
                    }
                }
            }


            // MESSED UP THE FOLLOWING FUNCTIONS, CHECK AGAINST GITHUB
            if (this->sensor_co2_) {
                uint16_t sensor_state = (uint16_t)this->sensor_co2_->get_state();
                uint8_t co2_level = find_level(sensor_state, this->co2_levels_);
                set_co2(co2_level);
            }

            if (this->sensor_pm_1_0_ || this->sensor_pm_2_5_ || this->sensor_pm_10_) {
                uint8_t index = 0;
                if (sensor_pm_1_0_) {
                    uint16_t sensor_state = (uint16_t)this->sensor_pm_1_0_->get_state();
                    uint8_t pm_1_0_level = find_level(sensor_state, this->pm_1_0_levels_);
                    index = (pm_1_0_level > index) ? pm_1_0_level : index;
                }
                if (sensor_pm_2_5_) {
                    uint16_t sensor_state = (uint16_t)this->sensor_pm_2_5_->get_state();
                    uint8_t pm_2_5_level = find_level(sensor_state, this->pm_2_5_levels_);
                    index = (pm_2_5_level > index) ? pm_2_5_level : index;
                }
                if (sensor_pm_10_) {
                    uint16_t sensor_state = (uint16_t)this->sensor_pm_10_->get_state();
                    uint8_t pm_10_level = find_level(sensor_state, this->pm_10_levels_);
                    index = (pm_10_level > index) ? pm_10_level : index;
                }
                set_pm(index);
            }

            if (this->sensor_temperature_) {
                float sensor_state = (float)this->sensor_temperature_->get_state();
                if (!isnan(sensor_state)) {
                    if (sensor_state != this->temperature_level_) {
                        this->temperature_level_ = sensor_state;
                        print_temperature(0, 23, this->temperature_level_);
                    }
                }
            }

            if (this->sensor_humidity_) {
                float sensor_state = (float)this->sensor_humidity_->get_state();
                if (!isnan(sensor_state)) {
                    if ((uint8_t)sensor_state != this->humidity_level_) {
                        this->humidity_level_ = (uint8_t)sensor_state;
                        this->humidity_level_ = this->humidity_level_ > 99 ? 99 : this->humidity_level_;
                        print_humidity(52, 23, this->humidity_level_);
                    }
                }
            }

            if (this->sensor_voc_) {
                uint16_t sensor_state = (uint16_t)this->sensor_voc_->get_state();
                uint8_t voc_level = find_level(sensor_state, this->voc_levels_);
                set_voc(voc_level);
            }

            if (this->sensor_power_) {
                uint8_t sensor_state = (uint8_t)this->sensor_power_->get_state();
                if (!isnan(sensor_state)) {
                    if (sensor_state != this->fan_level_) {
                        this->fan_level_ = sensor_state;
                        set_fan(true, this->fan_level_);
                    }
                }
            }
            break;

        default:
            break;

        }
    }

    void AirQualityDisplay::print_temperature(int16_t x, int16_t y, float temperature)
    {
        gfx->fillRect(x, y - HUMIDITY_HEIGHT + 1, 3 * HUMIDITY_WIDTH + 5, HUMIDITY_HEIGHT, GFX_BLACK);
        gfx->setTextColor(GFX_WHITE);
        if (temperature < 10) {
            x = x + HUMIDITY_WIDTH + 1;
        }
        gfx->setTextColor(GFX_WHITE);
        gfx->setCursor(x, y);
        gfx->setFont(&FreeSansBold10pt7b);

        gfx->println(temperature, 1);
        gfx->setCursor(x + 42, y - 6);
        gfx->setFont();
        gfx->println("C");
        gfx->drawRect(x + 40, y - 6, 1, 1, GFX_WHITE);
    }

    void AirQualityDisplay::print_humidity(int16_t x, int16_t y, float humidity)
    {
        gfx->fillRect(x, y - HUMIDITY_HEIGHT + 1, 2 * HUMIDITY_WIDTH, HUMIDITY_HEIGHT, GFX_BLACK);
        gfx->setTextColor(GFX_WHITE);
        if (RH < 10) {
            x = x + HUMIDITY_WIDTH + 1;
        }
        gfx->setCursor(x, y);
        gfx->setFont(&FreeSansBold10pt7b);

        gfx->println(humidity, 0);
        gfx->setCursor(x + 25, y - 6);
        gfx->setFont();
        gfx->println("%RH");
    }

    void AirQualityDisplay::print_comma(int16_t x, int16_t y)
    {
        gfx->setTextColor(GFX_WHITE);
        gfx->setCursor(x, y);
        gfx->setFont(&FreeSansBold10pt7b);
        gfx->println(',');
    }

    void AirQualityDisplay::set_pm(uint8_t level)
    {
        draw_row(0, level, this->pm_level_);
        this->pm_level_ = level;
    }

    void AirQualityDisplay::set_co2(uint8_t level)
    {
        draw_row(1, level, this->co2_level_);
        this->co2_level_ = level;
    }

    void AirQualityDisplay::set_voc(uint8_t level)
    {
        draw_row(2, level, this->voc_level_);
        this->voc_level_ = level;
    }

    void AirQualityDisplay::set_time(ESPTime current_time)
    {
        gfx->fillRect(0, 0, 29, 7, GFX_BLACK);
        gfx->setCursor(0, 0);
        gfx->setFont();
        char str[6];
        time_t timeStamp = current_time.timestamp;
        strftime(str, sizeof(str), "%H:%M", localtime(&timeStamp));
        gfx->print(str);
    }

    void AirQualityDisplay::set_connectivity(uint8_t connect)
    {
        uint8_t x = 85;
        uint8_t y = 0;
        gfx->fillRect(x, y, 11, 7, GFX_BLACK);
        switch (connect) {
        case none:
            break;
        case wifi:
            // gfx->drawBitmap(x, y, bitmap_Wifi, 10, 8, GFX_WHITE);
            gfx->drawBitmap(x, y, bitmap_Wifi, 11, 7, GFX_WHITE);
            break;
        case bluetooth:
            gfx->drawBitmap(x, y, bitmap_BT_8x7, 8, 7, GFX_WHITE);
            break;
        }
    }

    void AirQualityDisplay::set_fan(bool show, uint8_t level)
    {
        uint8_t x = 0;
        uint8_t y = 28;
        gfx->setCursor(x, y);
        gfx->print("Fan: ");
        gfx->fillRect(x + 22, y, 30, 8, GFX_BLACK);
        gfx->print(level);
        gfx->print("%");

        //
        if (show) {
            // gfx->setCursor(x, 1);
            // gfx->setFont();
            // gfx->print("Fan");
            // gfx->drawBitmap(x, 0, bitmap_fan_10x10, 10, 10, GFX_WHITE);
            // gfx->drawRect(80, 1, 15, 7, GFX_WHITE);
            // gfx->fillRect(82, 3, (level * 11) / 10, 3, GFX_WHITE);
        }
    }

    void AirQualityDisplay::draw_row(uint8_t row, uint8_t new_level, int8_t prev_level)
    {
        if (prev_level == -1) {
            for (uint8_t i = 0; i <= new_level; i++) {
                draw_graph_level(i, row, true);
            }
        } else if (new_level > (uint8_t)prev_level) {
            for (uint8_t i = prev_level + 1; i <= new_level; i++) {
                draw_graph_level(i, row, true);
            }
        } else if (new_level < (uint8_t)prev_level) {
            for (uint8_t i = new_level + 1; i <= prev_level; i++) {
                draw_graph_level(i, row, false);
            }
        }
    }

    void AirQualityDisplay::draw_graph_level(uint8_t level, uint8_t row, bool flag)
    {
        int16_t x;
        int16_t y;
        switch (row) {
        case 0:
            y = PLOT_Y + 2;
            break;
        case 1:
            y = PLOT_Y + 2 + 1 * SEG_HEIGHT;
            break;
        case 2:
            y = PLOT_Y + 2 + 2 * SEG_HEIGHT;
            break;
        }

        switch (level) {
        case 0:
            x = PLOT_X + 2;
            break;
        case 1:
            x = PLOT_X + 2 + 1 * SEG_WIDTH;
            break;
        case 2:
            x = PLOT_X + 2 + 2 * SEG_WIDTH;
            break;
        case 3:
            x = PLOT_X + 2 + 3 * SEG_WIDTH;
            break;
        case 4:
            x = PLOT_X + 2 + 4 * SEG_WIDTH;
            break;
        case 5:
            x = PLOT_X + 2 + 5 * SEG_WIDTH;
            break;
        }

        if (flag) {
            gfx->fillRect(x, y, SEG_WIDTH, SEG_HEIGHT, this->colors[level]);
        } else {
            gfx->fillRect(x, y, SEG_WIDTH, SEG_HEIGHT, GFX_BLACK);
        }
    }

    void AirQualityDisplay::draw_graph()
    {
        gfx->setCursor(0, PLOT_Y + 2);
        gfx->setFont();
        gfx->println("PM");
        gfx->println("CO2");
        gfx->println("VOC");
        gfx->drawRect(PLOT_X, PLOT_Y, PLOT_WIDTH, PLOT_HEIGHT, GFX_WHITE);
        gfx->drawRect(PLOT_X + 1 + 1 * SEG_WIDTH, PLOT_Y, 1, 2, GFX_WHITE);
        gfx->drawRect(PLOT_X + 1 + 2 * SEG_WIDTH, PLOT_Y, 1, 2, GFX_WHITE);
        gfx->drawRect(PLOT_X + 1 + 3 * SEG_WIDTH, PLOT_Y, 1, 2, GFX_WHITE);
        gfx->drawRect(PLOT_X + 1 + 4 * SEG_WIDTH, PLOT_Y, 1, 2, GFX_WHITE);
        gfx->drawRect(PLOT_X + 1 + 5 * SEG_WIDTH, PLOT_Y, 1, 2, GFX_WHITE);

        gfx->drawRect(PLOT_X + 1 + 1 * SEG_WIDTH, PLOT_Y + PLOT_HEIGHT - 2, 1, 2, GFX_WHITE);
        gfx->drawRect(PLOT_X + 1 + 2 * SEG_WIDTH, PLOT_Y + PLOT_HEIGHT - 2, 1, 2, GFX_WHITE);
        gfx->drawRect(PLOT_X + 1 + 3 * SEG_WIDTH, PLOT_Y + PLOT_HEIGHT - 2, 1, 2, GFX_WHITE);
        gfx->drawRect(PLOT_X + 1 + 4 * SEG_WIDTH, PLOT_Y + PLOT_HEIGHT - 2, 1, 2, GFX_WHITE);
        gfx->drawRect(PLOT_X + 1 + 5 * SEG_WIDTH, PLOT_Y + PLOT_HEIGHT - 2, 1, 2, GFX_WHITE);
    }

    void AirQualityDisplay::draw_fan_square() {}

    uint8_t AirQualityDisplay::find_graph_level(uint16_t level, std::array<uint16_t, 5> levels)
    {
        for (uint8_t i = 0; i < levels.size(); i++) {
            if ((levels[i] - level) > 0) {
                return i;
            }
        }
        return levels.size();
    }
}
}