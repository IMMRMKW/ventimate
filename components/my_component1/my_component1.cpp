#include "my_component1.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"

namespace esphome {
namespace my_component1 {
    static const char* const TAG = "my_component1";
    printComma(int16_t x, int16_t y)
    {
        gfx->setTextColor(WHITE);
        gfx->setCursor(x, y);
        gfx->setFont(&FreeSansBold10pt7b);
        gfx->println(',');
    }
}
}
