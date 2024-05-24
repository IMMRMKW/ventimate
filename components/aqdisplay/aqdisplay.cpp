#include "aqdisplay.h"

namespace esphome {
namespace aqdisplay {

    void AQDISPLAY::setup()
    {

        bus_ = new Arduino_HWSPI(dc_pin_->get_pin(), cs_pin_->get_pin() /* CS */);
        gfx_ = new Arduino_SSD1331(bus_, rst_pin_->get_pin() /* RST */, 0 /* rotation */);

        gfx_->begin();
        dc_pin_->pin_mode(gpio::FLAG_OUTPUT);

        bus_->sendCommand(SSD1331_MASTERCURRENT); // 0x87
        bus_->sendCommand(brightness_);

        gfx_->fillScreen(GFX_BLACK);
        gfx_->setTextColor(GFX_WHITE);
    }

    void AQDISPLAY::update()
    {
        switch (state_) {
        case welcome: {
            gfx_->draw16bitRGBBitmap(0, 0, bitmap_welcome, 96, 64);
            counter_++;
            if (counter_ > 3) {
                state_ = working;
            }
            break;
        }
        case working:
            if (!graph_shown_) {
                gfx_->fillScreen(GFX_BLACK);
                drawGraph();
                graph_shown_ = true;
            }
            if (clock_) {
                setTime(0, 0, clock_->now());
            }

            if (network_) {
                if (network_->is_connected()) {
                    if (!connectivity_shown) {
                        setConnectivity(wifi);
                        connectivity_shown = true;
                    }
                } else {
                    if (!connectivity_shown) {
                        setConnectivity(wifi);
                        connectivity_shown = true;
                    } else {
                        setConnectivity(none);
                        connectivity_shown = false;
                    }
                }
            }

            if (sensor_co2_index_) {
                uint8_t index = (uint8_t)sensor_co2_index_->get_state();
                setCO2(index);
            }

            if (sensor_pm_index_) {
                uint8_t index = (uint8_t)sensor_pm_index_->get_state();
                setPM(index);
            }

            if (sensor_temp_) {
                float temp = (float)sensor_temp_->get_state();
                if (!isnan(temp)) {
                    if (temp != temp_level) {
                        temp_level = temp;
                        printTemp(0, 22, temp_level);
                    }
                }
            }

            if (sensor_rh_) {
                float rh = (float)sensor_rh_->get_state();
                if (!isnan(rh)) {
                    if ((uint8_t)rh != rh_level) {
                        rh_level = (uint8_t)rh;
                        rh_level = rh_level > 99 ? 99 : rh_level;
                        printRH(57, 22, rh_level);
                    }
                }
            }

            if (sensor_voc_index_) {
                uint8_t index = (uint8_t)sensor_voc_index_->get_state();
                setVOC(index);
            }

            if (sensor_power_) {
                uint8_t fan_level = (uint8_t)sensor_power_->get_state();
                if (!isnan(fan_level)) {
                    if (fan_level != fan_level_) {
                        fan_level_ = fan_level;
                        setFan(0, 26, fan_level_);
                    }
                }
            }
            break;

        default: {
            break;
        }
        }
    }

    void AQDISPLAY::printTemp(int16_t x, int16_t y, float temp)
    {
        int16_t x_bounds, y_bounds;
        uint16_t w, h;
        gfx_->setFont(&BIG_FONT);
        fill_textBounds_with_black("88.8", x, y, &x_bounds, &y_bounds, &w, &h);

        if (temp < 10) {
            int16_t dw = get_width_difference("88.8", "8.8");
            x = x + dw;
        }

        gfx_->setCursor(x, y);
        gfx_->println(temp, 1);
        gfx_->setCursor(x_bounds + w + 4, y - 6);
        gfx_->setFont();
        gfx_->println("C");
        gfx_->drawRect(x_bounds + w + 2, y - 6, 1, 1, GFX_WHITE);
    }

    void AQDISPLAY::printRH(int16_t x, int16_t y, float RH)
    {
        int16_t x_bounds, y_bounds;
        uint16_t w, h;
        gfx_->setFont(&BIG_FONT);
        fill_textBounds_with_black("88", x, y, &x_bounds, &y_bounds, &w, &h);

        if (RH < 10) {
            int16_t dw = get_width_difference("88", "8");
            x = x + dw;
        }
        gfx_->setCursor(x, y);

        gfx_->println(RH, 0);
        gfx_->setCursor(x_bounds + w + 2, y - 6);
        gfx_->setFont();
        gfx_->println("%RH");
    }

    void AQDISPLAY::setPM(uint8_t level)
    {
        drawRow(0, level, pm_level);
        pm_level = level;
    }

    void AQDISPLAY::setCO2(uint8_t level)
    {
        drawRow(1, level, CO2_level);
        CO2_level = level;
    }

    void AQDISPLAY::setVOC(uint8_t level)
    {
        drawRow(2, level, VOC_level);
        VOC_level = level;
    }

    void AQDISPLAY::setTime(int16_t x, int16_t y, ESPTime current_time)
    {
        int16_t x_bounds, y_bounds;
        uint16_t w, h;
        gfx_->setFont();
        fill_textBounds_with_black("88:88", x, y, &x_bounds, &y_bounds, &w, &h);
        gfx_->setCursor(0, 0);
        char str[6];
        time_t timeStamp = current_time.timestamp;
        strftime(str, sizeof(str), "%H:%M", localtime(&timeStamp));
        gfx_->print(str);
    }

    void AQDISPLAY::setConnectivity(uint8_t connect)
    {
        uint8_t x = 85;
        uint8_t y = 0;
        gfx_->fillRect(x, y, 11, 7, GFX_BLACK);
        switch (connect) {
        case none:
            break;
        case wifi:
            // gfx->drawBitmap(x, y, bitmap_Wifi, 10, 8, GFX_WHITE);
            gfx_->drawBitmap(x, y, bitmap_Wifi, 11, 7, GFX_WHITE);
            break;
        case Bluetooth:
            gfx_->drawBitmap(x, y, bitmap_BT_8x7, 8, 7, GFX_WHITE);
            break;
        }
    }

    void AQDISPLAY::setFan(int16_t x, int16_t y, uint8_t level)
    {
        int16_t x_bounds, y_bounds;
        uint16_t w, h;
        gfx_->setFont();
        gfx_->setCursor(x, y);
        gfx_->print("Fan:");
        x = gfx_->getCursorX();
        fill_textBounds_with_black("888", x, y, &x_bounds, &y_bounds, &w, &h);
        if (level < 10) {
            int16_t dw = get_width_difference("888", "8");
            x = x + dw;
        } else if (level < 100) {
            int16_t dw = get_width_difference("888", "88");
            x = x + dw;
        }
        gfx_->setCursor(x, y);
        gfx_->print(level);
        gfx_->print("%");
    }

    void AQDISPLAY::drawRow(uint8_t row, uint8_t new_level, int8_t prev_level)
    {
        if (prev_level == -1) {
            for (uint8_t i = 0; i <= new_level; i++) {
                drawLevel(i, row, true);
            }
        } else if (new_level > (uint8_t)prev_level) {
            for (uint8_t i = prev_level + 1; i <= new_level; i++) {
                drawLevel(i, row, true);
            }
        } else if (new_level < (uint8_t)prev_level) {
            for (uint8_t i = new_level + 1; i <= prev_level; i++) {
                drawLevel(i, row, false);
            }
        }
    }

    void AQDISPLAY::drawLevel(uint8_t level, uint8_t row, bool flag)
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
            gfx_->fillRect(x, y, SEG_WIDTH, SEG_HEIGHT, colors[level]);
        } else {
            gfx_->fillRect(x, y, SEG_WIDTH, SEG_HEIGHT, GFX_BLACK);
        }
    }

    void AQDISPLAY::drawGraph()
    {
        gfx_->setCursor(0, PLOT_Y + 2);
        gfx_->setFont();
        gfx_->println("PM");
        gfx_->println("CO2");
        gfx_->println("VOC");
        gfx_->drawRect(PLOT_X, PLOT_Y, PLOT_WIDTH, PLOT_HEIGHT, GFX_WHITE);
        gfx_->drawRect(PLOT_X + 1 + 1 * SEG_WIDTH, PLOT_Y, 1, 2, GFX_WHITE);
        gfx_->drawRect(PLOT_X + 1 + 2 * SEG_WIDTH, PLOT_Y, 1, 2, GFX_WHITE);
        gfx_->drawRect(PLOT_X + 1 + 3 * SEG_WIDTH, PLOT_Y, 1, 2, GFX_WHITE);
        gfx_->drawRect(PLOT_X + 1 + 4 * SEG_WIDTH, PLOT_Y, 1, 2, GFX_WHITE);
        gfx_->drawRect(PLOT_X + 1 + 5 * SEG_WIDTH, PLOT_Y, 1, 2, GFX_WHITE);

        gfx_->drawRect(PLOT_X + 1 + 1 * SEG_WIDTH, PLOT_Y + PLOT_HEIGHT - 2, 1, 2, GFX_WHITE);
        gfx_->drawRect(PLOT_X + 1 + 2 * SEG_WIDTH, PLOT_Y + PLOT_HEIGHT - 2, 1, 2, GFX_WHITE);
        gfx_->drawRect(PLOT_X + 1 + 3 * SEG_WIDTH, PLOT_Y + PLOT_HEIGHT - 2, 1, 2, GFX_WHITE);
        gfx_->drawRect(PLOT_X + 1 + 4 * SEG_WIDTH, PLOT_Y + PLOT_HEIGHT - 2, 1, 2, GFX_WHITE);
        gfx_->drawRect(PLOT_X + 1 + 5 * SEG_WIDTH, PLOT_Y + PLOT_HEIGHT - 2, 1, 2, GFX_WHITE);
    }

    int16_t AQDISPLAY::get_width_difference(const char* str1, const char* str2)
    {
        uint16_t w_1, h_1, w_2, h_2;
        int16_t x_1, y_1;
        gfx_->getTextBounds(str1, 0, 0, &x_1, &y_1, &w_1, &h_1);
        gfx_->getTextBounds(str2, 0, 0, &x_1, &y_1, &w_2, &h_2);
        return (int16_t)w_1 - w_2;
    }

    void AQDISPLAY::fill_textBounds_with_black(const char* str, int16_t x, int16_t y,
        int16_t* x1, int16_t* y1, uint16_t* w, uint16_t* h)
    {
        gfx_->getTextBounds(str, x, y, x1, y1, w, h);
        gfx_->fillRect(*x1, *y1, *w, *h, GFX_BLACK);
    }
}
}