#include "aqdisplay.h"

namespace esphome {
namespace aqdisplay {

    void AQDISPLAY::setup()
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

    void AQDISPLAY::loop()
    {
    }

    void AQDISPLAY::update()
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
            if (!graph_shown_) {
                gfx->fillScreen(GFX_BLACK);
                drawGraph();
                graph_shown_ = true;
            }
            if (clock_) {
                setTime(clock_->now());
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

            if (sensor_co2_) {
                uint16_t level = (uint16_t)sensor_co2_->get_state();
                uint8_t temp = find_level(level, co2_levels_);
                setCO2(temp);
            }

            if (sensor_pm_1_0_ || sensor_pm_2_5_ || sensor_pm_10_) {
                uint8_t index = 0;
                if (sensor_pm_1_0_) {
                    uint16_t level = (uint16_t)sensor_pm_1_0_->get_state();
                    uint8_t temp = find_level(level, pm_1_0_levels_);
                    index = (temp > index) ? temp : index;
                }
                if (sensor_pm_2_5_) {
                    uint16_t level = (uint16_t)sensor_pm_2_5_->get_state();
                    uint8_t temp = find_level(level, pm_2_5_levels_);
                    index = (temp > index) ? temp : index;
                }
                if (sensor_pm_10_) {
                    uint16_t level = (uint16_t)sensor_pm_10_->get_state();
                    uint8_t temp = find_level(level, pm_10_levels_);
                    index = (temp > index) ? temp : index;
                }
                setPM(index);
            }

            if (sensor_temp_) {
                float temp = (float)sensor_temp_->get_state();
                if (!isnan(temp)) {
                    if (temp != temp_level) {
                        temp_level = temp;
                        printTemp(0, 23, temp_level);
                    }
                }
            }

            if (sensor_rh_) {
                float rh = (float)sensor_rh_->get_state();
                if (!isnan(rh)) {
                    if ((uint8_t)rh != rh_level) {
                        rh_level = (uint8_t)rh;
                        rh_level = rh_level > 99 ? 99 : rh_level;
                        printRH(52, 23, rh_level);
                    }
                }
            }

            if (sensor_voc_) {
                uint16_t level = (uint16_t)sensor_voc_->get_state();
                uint8_t temp = find_level(level, voc_levels_);
                setVOC(temp);
            }

            if (sensor_power_) {
                uint8_t level = (uint8_t)sensor_power_->get_state();
                setFan(true, level);
            }
            break;

        default: {
            break;
        }
        }
    }

    void AQDISPLAY::printTemp(int16_t x, int16_t y, float temp)
    {
        gfx->fillRect(x, y - RH_HEIGHT + 1, 3 * RH_WIDTH + 5, RH_HEIGHT, GFX_BLACK);
        gfx->setTextColor(GFX_WHITE);
        if (temp < 10) {
            x = x + RH_WIDTH + 1;
        }
        gfx->setTextColor(GFX_WHITE);
        gfx->setCursor(x, y);
        gfx->setFont(&FreeSansBold10pt7b);

        gfx->println(temp, 1);
        gfx->setCursor(x + 42, y - 6);
        gfx->setFont();
        gfx->println("C");
        gfx->drawRect(x + 40, y - 6, 1, 1, GFX_WHITE);
    }

    void AQDISPLAY::printRH(int16_t x, int16_t y, float RH)
    {
        gfx->fillRect(x, y - RH_HEIGHT + 1, 2 * RH_WIDTH, RH_HEIGHT, GFX_BLACK);
        gfx->setTextColor(GFX_WHITE);
        if (RH < 10) {
            x = x + RH_WIDTH + 1;
        }
        gfx->setCursor(x, y);
        gfx->setFont(&FreeSansBold10pt7b);

        gfx->println(RH, 0);
        gfx->setCursor(x + 25, y - 6);
        gfx->setFont();
        gfx->println("%RH");
    }

    void AQDISPLAY::printComma(int16_t x, int16_t y)
    {
        gfx->setTextColor(GFX_WHITE);
        gfx->setCursor(x, y);
        gfx->setFont(&FreeSansBold10pt7b);
        gfx->println(',');
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

    void AQDISPLAY::setTime(ESPTime current_time)
    {
        gfx->fillRect(0, 0, 29, 7, GFX_BLACK);
        gfx->setCursor(0, 0);
        gfx->setFont();
        char str[6];
        time_t timeStamp = current_time.timestamp;
        strftime(str, sizeof(str), "%H:%M", localtime(&timeStamp));
        gfx->print(str);
    }

    void AQDISPLAY::setConnectivity(uint8_t connect)
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
        case Bluetooth:
            gfx->drawBitmap(x, y, bitmap_BT_8x7, 8, 7, GFX_WHITE);
            break;
        }
    }

    void AQDISPLAY::setFan(bool show, uint8_t level)
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
            gfx->fillRect(x, y, SEG_WIDTH, SEG_HEIGHT, colors[level]);
        } else {
            gfx->fillRect(x, y, SEG_WIDTH, SEG_HEIGHT, GFX_BLACK);
        }
    }

    void AQDISPLAY::drawGraph()
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

    uint8_t AQDISPLAY::find_level(uint16_t level, std::array<uint16_t, 5> levels)
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