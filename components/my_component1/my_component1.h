
 /**
 * USB Power Delivery integration in ESPHome
 *	
 * Authors: groothuisss & IMMRMKW
 */
 
#ifndef MY_CUSTOM_COMPONENT_H
#define MY_CUSTOM_COMPONENT_H 

#pragma once

#include <Arduino.h>
#include "esphome/core/gpio.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"


namespace esphome {
namespace my_component1 {

class MyComponent : public Component {
 public:

  uint8_t _level = 0;
  void setup() override {
    // This will be called once to set up the component
    // Think of it as the `setup()` call in Arduino

  }

  void loop() override {
    // This will be called very often after setup time
    // Think of it as the `loop()` call in Arduino
	delay(1000)
	ESP_LOGD("custom", _level);
    
  }
  void set_iaq_accuracy(uint8_t level)
  {
	  _level = level
  }
};

#endif  // MY_CUSTOM_COMPONENT_H
}  // namespace fusb302
}  // namespace esphome