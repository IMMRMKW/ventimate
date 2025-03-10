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

CONF_SENSOR_VOC_INDEX = "sensor_voc_index"
CONF_SENSOR_PM_INDEX = "sensor_pm_index"
CONF_SENSOR_CO2_INDEX = "sensor_index"

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



AIRPURIFIER_SCHEMA = cv.Schema({
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
    cv.Optional(CONF_SENSOR_CO2_INDEX): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_SENSOR_VOC_INDEX): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_SENSOR_PM_INDEX): cv.use_id(sensor.Sensor),

    cv.Optional(CONF_PROPORTIONAL_GAIN, default = [0, 20, 40, 60, 80, 100]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_INTEGRAL_GAIN, default = [0, 7200, 3600, 1800, 900, 300]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_USE_PURGE, default = True): cv.boolean,
    cv.Optional(CONF_PURGE_INTERVAL, default = 1800): cv.int_,
    cv.Optional(CONF_PURGE_DURATION, default = 60): cv.int_,
    cv.Optional(CONF_PURGE_POWER, default = 25): cv.int_,

}).extend(cv.polling_component_schema("1s"))


async def setup_airpurifier_core_(var, config):

    if CONF_SENSOR_VOC_INDEX in config:
        sens = await cg.get_variable(config[CONF_SENSOR_VOC_INDEX])
        cg.add(var.set_sensor_voc_index(sens))

    if CONF_SENSOR_PM_INDEX in config:
        sens = await cg.get_variable(config[CONF_SENSOR_PM_INDEX])
        cg.add(var.set_sensor_pm_index(sens))

    if CONF_SENSOR_CO2_INDEX in config:
        sens = await cg.get_variable(config[CONF_SENSOR_CO2_INDEX])
        cg.add(var.set_sensor_co2_index(sens))

    if CONF_POWER_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_POWER_SENSOR]) 
        cg.add(var.set_sensor_power(sens))
    
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
    
    
    