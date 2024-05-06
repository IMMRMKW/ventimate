 ################################################
 # Air purifier in ESPHome                      #
 #	                                            #
 # Authors: groothuisss & IMMRMKW               #
 ################################################
 
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import sensor
from . import airpurifier_switch as sw
from . import airpurifier_number as num

from esphome.const import (
    UNIT_PERCENT,
    ICON_FAN,
    DEVICE_CLASS_SPEED,
    STATE_CLASS_MEASUREMENT,
)

IS_PLATFORM_COMPONENT = True
AUTO_LOAD = ["switch", "number"]

CONF_SENSOR_VOC = "sensor_voc"
CONF_SENSOR_PM_2_5 = "sensor_pm_2_5"
CONF_SENSOR_PM_10 = "sensor_pm_10"
CONF_SENSOR_CO2 = "sensor_co2"

CONF_PM_2_5_LEVELS = "pm_2_5_levels"
CONF_PM_10_LEVELS = "pm_10_levels"
CONF_VOC_LEVELS = "voc_levels"
CONF_CO2_LEVELS = "co2_levels"

CONF_SWITCH = "switcher"
CONF_MAX_PWM = "max_pwm"

CONF_INTEGRAL_GAIN = "integral_gain"
CONF_PROPORTIONAL_GAIN = "proportional_gain"
CONF_POWER_SENSOR = "power_sensor"

CONF_USE_PURGE = "use_purge"
CONF_PURGE_INTERVAL = "purge_interval"
CONF_PURGE_DURATION = "purge_duration"
CONF_PURGE_POWER = "purge_power"

airpurifier_ns = cg.esphome_ns.namespace('airpurifier')
AIRPURIFIER = airpurifier_ns.class_('AIRPURIFIER', cg.PollingComponent)



CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(AIRPURIFIER),
    cv.Required(CONF_POWER_SENSOR): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                icon=ICON_FAN,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_SPEED,
                state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Required(CONF_MAX_PWM): num.CONFIG_SCHEMA,
    cv.Required(CONF_SWITCH): sw.CONFIG_SCHEMA,
    cv.Optional(CONF_SENSOR_VOC): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_SENSOR_PM_2_5): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_SENSOR_PM_10): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_SENSOR_CO2): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_PROPORTIONAL_GAIN, default = [20, 40, 60, 80, 100]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_INTEGRAL_GAIN, default = [60, 120, 1800, 3600, 7200]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_PM_2_5_LEVELS, default = [12, 35, 55, 150, 250]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_PM_10_LEVELS, default = [54, 154, 254, 354, 424]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_VOC_LEVELS, default = [15, 25, 50, 75, 100]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_CO2_LEVELS, default = [650, 1500, 2000, 2500, 5000]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_USE_PURGE, default = True): cv.boolean,
    cv.Optional(CONF_PURGE_INTERVAL, default = 1800): cv.int_,
    cv.Optional(CONF_PURGE_DURATION, default = 60): cv.int_,
    cv.Optional(CONF_PURGE_POWER, default = 25): cv.int_,

}).extend(cv.polling_component_schema("1s"))


async def setup_airpurifier_core_(var, config):
    
    if CONF_SENSOR_VOC in config:
        sens = await cg.get_variable(config[CONF_SENSOR_VOC])
        cg.add(var.set_sensor_voc(sens))

    if CONF_SENSOR_PM_2_5 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_PM_2_5])
        cg.add(var.set_sensor_pm_2_5(sens))

    if CONF_SENSOR_PM_10 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_PM_10])
        cg.add(var.set_sensor_pm_10(sens))
    
    if CONF_SENSOR_CO2 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_CO2])
        cg.add(var.set_sensor_co2(sens))

    if CONF_POWER_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_POWER_SENSOR])
        cg.add(var.set_sensor_power(sens))
    
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
    
    if CONF_USE_PURGE in config:
        cg.add(var.set_purge(config[CONF_USE_PURGE]))
    
    if CONF_PURGE_DURATION in config:
        cg.add(var.set_purge_duration(config[CONF_PURGE_DURATION]))

    if CONF_PURGE_INTERVAL in config:
        cg.add(var.set_purge_interval(config[CONF_PURGE_INTERVAL]))
               
    if CONF_PURGE_POWER in config:
        cg.add(var.set_purge_power(config[CONF_PURGE_POWER]))
    
    if CONF_INTEGRAL_GAIN in config:
        constants = config[CONF_INTEGRAL_GAIN]
        cg.add(var.set_integral_gain(constants))

    if CONF_PROPORTIONAL_GAIN in config:
        constants = config[CONF_PROPORTIONAL_GAIN]
        cg.add(var.set_proportional_gain(constants))
    
    await sw.setup_switch(config[CONF_SWITCH])
    await num.setup_number(config[CONF_MAX_PWM])
    
    
    