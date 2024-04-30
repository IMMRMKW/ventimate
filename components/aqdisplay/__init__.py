import esphome.codegen as cg 
import esphome.config_validation as cv
from esphome import pins
from esphome.components.homeassistant import time
from esphome.components import sensor, wifi
from esphome.const import (
    CONF_ID,
    CONF_INTERRUPT_PIN,
)

CONF_CS_PIN = "chip_select_pin"
CONF_DC_PIN = "dc_pin"
CONF_RST_PIN = "reset_pin"


CONF_SENSOR_CO2 = "sensor_co2"
CONF_SENSOR_FAN_POWER = "sensor_fan_power"
CONF_SENSOR_PM_1_0 = "sensor_pm_1_0"
CONF_SENSOR_PM_2_5 = "sensor_pm_2_5"
CONF_SENSOR_PM_10 = "sensor_pm_10"
CONF_SENSOR_RH = "sensor_rh"
CONF_SENSOR_TEMP = "sensor_temp"
CONF_SENSOR_VOC = "sensor_voc"


CONF_CO2_LEVELS = "co2_levels"
CONF_PM_1_0_LEVELS = "pm_1_0_levels"
CONF_PM_2_5_LEVELS = "pm_2_5_levels"
CONF_PM_10_LEVELS = "pm_10_levels"
CONF_VOC_LEVELS = "voc_levels"

CONF_CLOCK = "clock"
CONF_NETWORK = "network"


aqdisplay_ns = cg.esphome_ns.namespace('aqdisplay')
AQDISPLAY = aqdisplay_ns.class_('AQDISPLAY', cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(AQDISPLAY),   
        cv.Optional(CONF_CS_PIN): cv.All(pins.internal_gpio_input_pin_schema),
        cv.Optional(CONF_DC_PIN): cv.All(pins.internal_gpio_input_pin_schema),
        cv.Optional(CONF_RST_PIN): cv.All(pins.internal_gpio_input_pin_schema),
        cv.Optional(CONF_SENSOR_CO2): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_FAN_POWER): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_PM_1_0): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_PM_2_5): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_PM_10): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_RH): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_TEMP): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_SENSOR_VOC): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_CO2_LEVELS, default = [650, 1500, 2000, 2500, 5000]) : cv.ensure_list(cv.int_),
        cv.Optional(CONF_PM_1_0_LEVELS, default = [12, 35, 55, 150, 250]) : cv.ensure_list(cv.int_),
        cv.Optional(CONF_PM_2_5_LEVELS, default = [12, 35, 55, 150, 250]) : cv.ensure_list(cv.int_),
        cv.Optional(CONF_PM_10_LEVELS, default = [54, 154, 254, 354, 424]) : cv.ensure_list(cv.int_),
        cv.Optional(CONF_VOC_LEVELS, default = [15, 25, 50, 75, 100]) : cv.ensure_list(cv.int_),
        cv.Optional(CONF_CLOCK) : cv.use_id(time.HomeassistantTime),
        cv.Optional(CONF_NETWORK) : cv.use_id(wifi.WiFiComponent),
    }).extend(cv.polling_component_schema("1s"))

async def to_code(config):
    cg.add_library("https://github.com/moononournation/Arduino_GFX","1.4.6")
 
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

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

    if CONF_SENSOR_CO2 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_CO2])
        cg.add(var.set_sensor_co2(sens))

    if CONF_SENSOR_FAN_POWER in config:
        sens = await cg.get_variable(config[CONF_SENSOR_FAN_POWER])
        cg.add(var.set_sensor_power(sens))

    if CONF_SENSOR_PM_1_0 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_PM_1_0])
        cg.add(var.set_sensor_pm_2_5(sens))

    if CONF_SENSOR_PM_2_5 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_PM_2_5])
        cg.add(var.set_sensor_pm_2_5(sens))

    if CONF_SENSOR_PM_10 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_PM_10])
        cg.add(var.set_sensor_pm_10(sens))
    
    if CONF_SENSOR_RH in config:
        sens = await cg.get_variable(config[CONF_SENSOR_RH])
        cg.add(var.set_sensor_rh(sens))
    
    if CONF_SENSOR_TEMP in config:
        sens = await cg.get_variable(config[CONF_SENSOR_TEMP])
        cg.add(var.set_sensor_temp(sens))

    if CONF_SENSOR_VOC in config:
        sens = await cg.get_variable(config[CONF_SENSOR_VOC])
        cg.add(var.set_sensor_voc(sens))
    
    if CONF_PM_1_0_LEVELS in config:
        levels = config[CONF_PM_2_5_LEVELS]
        cg.add(var.set_pm_1_0_levels(levels))

    if CONF_PM_2_5_LEVELS in config:
        levels = config[CONF_PM_2_5_LEVELS]
        cg.add(var.set_pm_2_5_levels(levels))
    
    if CONF_PM_10_LEVELS in config:
        levels = config[CONF_PM_10_LEVELS]
        cg.add(var.set_pm_10_levels(levels))
    
    if CONF_VOC_LEVELS in config:
        levels = config[CONF_VOC_LEVELS]
        cg.add(var.set_voc_levels(levels))
    
    if CONF_CO2_LEVELS in config:
        levels = config[CONF_CO2_LEVELS]
        cg.add(var.set_co2_levels(levels))
    
    

    
    
    if CONF_SENSOR_VOC in config:
        sens = await cg.get_variable(config[CONF_SENSOR_VOC])
        cg.add(var.set_sensor_voc(sens))
