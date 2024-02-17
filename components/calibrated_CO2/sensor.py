import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID,  CONF_SENSOR

DEPENDENCIES = ["network"]
AUTO_LOAD = ["network"]
calibrated_CO2_ns = cg.esphome_ns.namespace('calibrated_CO2')

CALIBRATEDCO2 = calibrated_CO2_ns.class_('CALIBRATEDCO2', cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema(
{
    cv.GenerateID(): cv.declare_id(CALIBRATEDCO2),
    cv.Optional(CONF_SENSOR): cv.use_id(sensor.Sensor),
}).extend(cv.polling_component_schema('60s'))

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    sens = yield cg.get_variable(config[CONF_SENSOR])
    cg.add(var.set_sensor(sens))