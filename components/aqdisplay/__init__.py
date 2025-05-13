import esphome.codegen as cg 
import esphome.config_validation as cv
from esphome import pins
from esphome.components.homeassistant import time
from esphome.components import sensor, wifi
from esphome.const import (
    CONF_ID,
    CONF_INTERRUPT_PIN,
)

CONF_SCLK_PIN = "sclk_pin"
CONF_MOSI_PIN = "mosi_pin"
CONF_CS_PIN = "chip_select_pin"
CONF_DC_PIN = "dc_pin"
CONF_RST_PIN = "reset_pin"

CONF_SENSOR_FAN_POWER = "sensor_fan_power"

CONF_SENSOR_CO2_INDEX = "sensor_co2_index"
CONF_SENSOR_PM_INDEX = "sensor_pm_index"
CONF_SENSOR_VOC_INDEX = "sensor_voc_index"

CONF_SENSOR_RH = "sensor_rh"
CONF_SENSOR_TEMP = "sensor_temp"

CONF_CLOCK = "clock"
CONF_NETWORK = "network"

CONF_BRIGHTNESS = "brightness"


aqdisplay_ns = cg.esphome_ns.namespace('aqdisplay')
AQDISPLAY = aqdisplay_ns.class_('AQDISPLAY', cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(AQDISPLAY), 
        cv.Optional(CONF_SCLK_PIN): cv.All(pins.internal_gpio_input_pin_schema), 
        cv.Optional(CONF_MOSI_PIN): cv.All(pins.internal_gpio_input_pin_schema), 
        cv.Optional(CONF_CS_PIN): cv.All(pins.internal_gpio_input_pin_schema),
        cv.Optional(CONF_DC_PIN): cv.All(pins.internal_gpio_input_pin_schema),
        cv.Optional(CONF_RST_PIN): cv.All(pins.internal_gpio_input_pin_schema),
        cv.Optional(CONF_SENSOR_CO2_INDEX): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_FAN_POWER): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_PM_INDEX): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_RH): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_TEMP): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_VOC_INDEX): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_CLOCK) : cv.use_id(time.HomeassistantTime),
        cv.Optional(CONF_NETWORK) : cv.use_id(wifi.WiFiComponent),
        cv.Optional(CONF_BRIGHTNESS, default=1) : cv.int_range(min = 1, max = 16),
    }).extend(cv.polling_component_schema("1s"))

async def to_code(config):
    cg.add_library(name="Arduino_GFX",
                   version="v1.5.5",
                   repository="https://github.com/moononournation/Arduino_GFX.git")
 
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if CONF_SCLK_PIN in config:
        pin = await cg.gpio_pin_expression(config[CONF_SCLK_PIN])
        cg.add(var.set_sclk_pin(pin))

    if CONF_MOSI_PIN in config:
        pin = await cg.gpio_pin_expression(config[CONF_MOSI_PIN])
        cg.add(var.set_mosi_pin(pin))
    
    if CONF_CS_PIN in config:
        pin = await cg.gpio_pin_expression(config[CONF_CS_PIN])
        cg.add(var.set_cs_pin(pin))

    if CONF_DC_PIN in config:
        pin = await cg.gpio_pin_expression(config[CONF_DC_PIN])
        cg.add(var.set_dc_pin(pin))

    if CONF_RST_PIN in config:
        pin = await cg.gpio_pin_expression(config[CONF_RST_PIN])
        cg.add(var.set_rst_pin(pin))

    if CONF_CLOCK in config:
        clock = await cg.get_variable(config[CONF_CLOCK])
        cg.add(var.set_clock(clock))

    if CONF_NETWORK in config:
        network = await cg.get_variable(config[CONF_NETWORK])
        cg.add(var.set_network(network))

    if CONF_SENSOR_FAN_POWER in config:
        sens = await cg.get_variable(config[CONF_SENSOR_FAN_POWER])
        cg.add(var.set_sensor_power(sens))
    
    if CONF_SENSOR_RH in config:
        sens = await cg.get_variable(config[CONF_SENSOR_RH])
        cg.add(var.set_sensor_rh(sens))
    
    if CONF_SENSOR_TEMP in config:
        sens = await cg.get_variable(config[CONF_SENSOR_TEMP])
        cg.add(var.set_sensor_temp(sens))

    if CONF_SENSOR_CO2_INDEX in config:
        sens = await cg.get_variable(config[CONF_SENSOR_PM_INDEX])
        cg.add(var.set_sensor_pm_index(sens))

    if CONF_SENSOR_PM_INDEX in config:
        sens = await cg.get_variable(config[CONF_SENSOR_CO2_INDEX])
        cg.add(var.set_sensor_co2_index(sens))

    if CONF_SENSOR_VOC_INDEX in config:
        sens = await cg.get_variable(config[CONF_SENSOR_VOC_INDEX])
        cg.add(var.set_sensor_voc_index(sens))

    if CONF_BRIGHTNESS in config:
        cg.add(var.set_brightness(config[CONF_BRIGHTNESS]))
    
