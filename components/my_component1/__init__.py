# my_components/my_component1/__init__.py

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    CONF_INTERRUPT_PIN,
)

my_component_ns = cg.esphome_ns.namespace('my_component1')
MyComponent = my_component_ns.class_('MyComponent', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(MyComponent),
    cv.Required('iaq_accuracy'): cv.templatable(cv.float_),
    
    cv.Optional('update_interval', default='120s'): cv.positive_time_period_milliseconds,

})

def to_code(config):
  var = cg.new_Pvariable(config[CONF_ID])
  await cg.register_component(var, config)
  cg.add(var.set_iaq_accuracy(config['iaq_accuracy']))