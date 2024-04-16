
 ################################################
 # USB Power Delivery integration in ESPHome    #
 #	                                            #
 # Authors: groothuisss & IMMRMKW               #
 ################################################
 
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import i2c
from esphome.const import (
    CONF_ID,
    CONF_INTERRUPT_PIN,
)

DEPENDENCIES = ["i2c"]

CONF_OPTIONAL_MAX_SUPPLY_VOLTAGE = 'maximum_supply_voltage'

fusb302_ns = cg.esphome_ns.namespace('fusb302')
FUSB302 = fusb302_ns.class_('FUSB302', cg.Component)

MaximumSupplyVoltage = fusb302_ns.enum("MAXIMUM_SUPPLY_VOLTAGE")

MAXIMUM_SUPPLY_VOLTAGE_OPTIONS = {
    "5v": MaximumSupplyVoltage.PD5V,
    "9v": MaximumSupplyVoltage.PD9V,
    "12v": MaximumSupplyVoltage.PD12V,
    "15v": MaximumSupplyVoltage.PD15V,
    "20v": MaximumSupplyVoltage.PD20V,
}

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(FUSB302),
    cv.Required(CONF_INTERRUPT_PIN): cv.All(pins.internal_gpio_input_pin_schema),
    cv.Optional(CONF_OPTIONAL_MAX_SUPPLY_VOLTAGE, default="5v"): cv.enum(MAXIMUM_SUPPLY_VOLTAGE_OPTIONS, lower=True),
}).extend(i2c.i2c_device_schema(0x22)).extend(cv.polling_component_schema("10s"))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_OPTIONAL_MAX_SUPPLY_VOLTAGE in config:
        max_supply_voltage = config[CONF_OPTIONAL_MAX_SUPPLY_VOLTAGE]
        cg.add(var.set_maximum_supply_voltage(max_supply_voltage))
    
    if CONF_INTERRUPT_PIN in config:
        interrupt_pin = await cg.gpio_pin_expression(config[CONF_INTERRUPT_PIN])
        cg.add(var.set_interrupt_pin(interrupt_pin))


