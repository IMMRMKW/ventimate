import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_CO2,
    CONF_ID,  
    CONF_SENSOR,
    DEVICE_CLASS_CARBON_DIOXIDE,
    DEVICE_CLASS_AQI,
    ICON_MOLECULE_CO2,
    ICON_CHEMICAL_WEAPON,
    ICON_RADIATOR,
    STATE_CLASS_MEASUREMENT,
    UNIT_EMPTY,
)
from esphome.core import CORE

CONF_CO2_INDEX = "co2_index"
CONF_PM_INDEX = "pm_index"
CONF_VOC_INDEX = "voc_index"

CONF_SENSOR_VOC = "sensor_voc"
CONF_SENSOR_PM_1_0 = "sensor_pm_1_0"
CONF_SENSOR_PM_2_5 = "sensor_pm_2_5"
CONF_SENSOR_PM_10 = "sensor_pm_10"
CONF_SENSOR_CO2 = "sensor_co2"

CONF_PM_1_0_LEVELS = "pm_1_0_levels"
CONF_PM_2_5_LEVELS = "pm_2_5_levels"
CONF_PM_10_LEVELS = "pm_10_levels"
CONF_VOC_LEVELS = "voc_levels"
CONF_CO2_LEVELS = "co2_levels"


aqi_ns = cg.esphome_ns.namespace('aqi')

AQI = aqi_ns.class_('AQI', cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema(
{
    cv.GenerateID(): cv.declare_id(AQI),
    cv.Required(CONF_CO2_INDEX): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_MOLECULE_CO2,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_AQI,
                state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Required(CONF_PM_INDEX): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_AQI,
                state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Required(CONF_VOC_INDEX): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_RADIATOR,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_AQI,
                state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_SENSOR_CO2): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_SENSOR_PM_1_0): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_SENSOR_PM_2_5): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_SENSOR_PM_10): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_SENSOR_VOC): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_CO2_LEVELS, default = [650, 1500, 2000, 2500, 5000]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_PM_1_0_LEVELS, default = [12, 35, 55, 150, 250]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_PM_2_5_LEVELS, default = [12, 35, 55, 150, 250]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_PM_10_LEVELS, default = [54, 154, 254, 354, 424]) : cv.ensure_list(cv.int_),
    cv.Optional(CONF_VOC_LEVELS, default = [15, 25, 50, 75, 100]) : cv.ensure_list(cv.int_),
    

}).extend(cv.polling_component_schema('1s'))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    if CONF_CO2_INDEX in config:
        sens = await sensor.new_sensor(config[CONF_CO2_INDEX])
        cg.add(var.set_sensor_co2_index(sens))

    if CONF_PM_INDEX in config:
        sens = await sensor.new_sensor(config[CONF_PM_INDEX])
        cg.add(var.set_sensor_pm_index(sens))

    if CONF_VOC_INDEX in config:
        sens = await sensor.new_sensor(config[CONF_VOC_INDEX])
        cg.add(var.set_sensor_voc_index(sens))

    if CONF_SENSOR_VOC in config:
        sens = await cg.get_variable(config[CONF_SENSOR_VOC])
        cg.add(var.set_sensor_voc(sens))

    if CONF_SENSOR_PM_1_0 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_PM_2_5])
        cg.add(var.set_sensor_pm_1_0(sens))

    if CONF_SENSOR_PM_2_5 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_PM_2_5])
        cg.add(var.set_sensor_pm_2_5(sens))

    if CONF_SENSOR_PM_10 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_PM_10])
        cg.add(var.set_sensor_pm_10(sens))
    
    if CONF_SENSOR_CO2 in config:
        sens = await cg.get_variable(config[CONF_SENSOR_CO2])
        cg.add(var.set_sensor_co2(sens))

    if CONF_CO2_LEVELS in config:
        levels = config[CONF_CO2_LEVELS]
        cg.add(var.set_co2_levels(levels))

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
    
    