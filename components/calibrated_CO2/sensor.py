import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_CO2,
    CONF_ID,  
    CONF_SENSOR,
    DEVICE_CLASS_CARBON_DIOXIDE,
    ICON_MOLECULE_CO2,
    STATE_CLASS_MEASUREMENT,
    UNIT_PARTS_PER_MILLION, 
)
from esphome.core import CORE

CONF_RETRIEVE_CO2_ONLINE = 'retrieve_co2_online'
CONF_DEFAULT_OUTDOOR_CO2 = 'default_outdoor_co2'

calibrated_co2_ns = cg.esphome_ns.namespace('calibrated_co2')
CALIBRATEDCO2 = calibrated_co2_ns.class_('CalibratedCo2', cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema(
{
    cv.GenerateID(): cv.declare_id(CALIBRATEDCO2),
    cv.Optional(CONF_SENSOR): cv.use_id(sensor.Sensor),
    cv.Optional(CONF_RETRIEVE_CO2_ONLINE, default = False): cv.boolean,
    cv.Optional(CONF_DEFAULT_OUTDOOR_CO2, default = 420): cv.float_range(min = 0.0, max = 1000.0),
    cv.Required(CONF_CO2): sensor.sensor_schema(
                unit_of_measurement=UNIT_PARTS_PER_MILLION,
                icon=ICON_MOLECULE_CO2,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_CARBON_DIOXIDE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
}).extend(cv.polling_component_schema('5s'))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    sens = await cg.get_variable(config[CONF_SENSOR])
    cg.add(var.set_sensor(sens))
    if CONF_CO2 in config:
        sensor_co2 = await sensor.new_sensor(config[CONF_CO2])
        cg.add(var.set_co2_sensor(sensor_co2))
    if CORE.is_esp32:
        cg.add_library("WiFiClientSecure", None)
        cg.add_library("HTTPClient", None)
    if CONF_RETRIEVE_CO2_ONLINE in config:
        cg.add(var.set_flag_retrieving_co2_online_(config[CONF_RETRIEVE_CO2_ONLINE]))
    if CONF_DEFAULT_OUTDOOR_CO2 in config:
        cg.add(var.set_default_outdoor_co2(config[CONF_DEFAULT_OUTDOOR_CO2]))

