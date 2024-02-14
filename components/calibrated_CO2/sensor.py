import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, UNIT_EMPTY, ICON_EMPTY

calibrated_CO2_ns = cg.esphome_ns.namespace('calibrated_CO2')

CALIBRATEDCO2 = calibrated_CO2_ns.class_('CALIBRATEDCO2', cg.PollingComponent)

CONFIG_SCHEMA = sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 1).extend({
    cv.GenerateID(): cv.declare_id(CALIBRATEDCO2)
    cv.Optional(CONF_SENSOR): cv.use_id(sensor.Sensor),
}).extend(cv.polling_component_schema('60s'))

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield sensor.register_sensor(var, config)
    sens = yield cg.get_variable(config[CONF_SENSOR])
    cg.add(var.set_sensor(sens))