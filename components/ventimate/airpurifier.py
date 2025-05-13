 ################################################
 # Air purifier in ESPHome                      #
 #	                                            #
 # Authors: groothuisss & IMMRMKW               #
 ################################################
 
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins

from esphome.components import airpurifier as ap
#from airpurifier import CONFIG_SCHEMA
from esphome.const import (
    CONF_ID,
)

CONF_POWER_EN_PIN = "power_enable_pin"
CONF_POWER_PWM_PIN = "power_pwm_pin"
CONF_FAN_PWM_PIN = "fan_pwm_pin"
CONF_TACHO_PIN = "fan_tacho_pin"
CONF_POWER_PWM_CHANNEL = "power_pwm_channel"
CONF_FAN_PWM_CHANNEL = "fan_pwm_channel"
CONF_MAX_VOLTAGE = "max_voltage"
CONF_MIN_VOLTAGE = "min_voltage"
CONF_FAN_PWM_FREQUENCY = "fan_pwm_frequency"
CONF_MIN_DUTY_CYCLE = "min_duty_cycle"

ventimate_ns = cg.esphome_ns.namespace('ventimate')
VENTIMATE = ventimate_ns.class_('VENTIMATE', ap.AIRPURIFIER)

AUTO_LOAD = ["airpurifier"]



CONFIG_SCHEMA = ap.AIRPURIFIER_SCHEMA.extend(cv.Schema(
    {
    cv.GenerateID(): cv.declare_id(VENTIMATE),
    cv.Optional(CONF_POWER_EN_PIN): cv.All(pins.internal_gpio_input_pin_schema),
    cv.Optional(CONF_POWER_PWM_PIN): cv.All(pins.internal_gpio_input_pin_schema),
    cv.Optional(CONF_FAN_PWM_PIN): cv.All(pins.internal_gpio_input_pin_schema),
    cv.Optional(CONF_TACHO_PIN): cv.All(pins.internal_gpio_input_pin_schema),
    cv.Optional(CONF_POWER_PWM_CHANNEL, default = 6): cv.int_range(0, 7),
    cv.Optional(CONF_FAN_PWM_CHANNEL, default = 7): cv.int_range(0, 7),
    cv.Optional(CONF_MAX_VOLTAGE, default = 12): cv.float_range(0,12),
    cv.Optional(CONF_MIN_VOLTAGE, default = 0): cv.float_range(0,12),
    cv.Optional(CONF_FAN_PWM_FREQUENCY, default = 20000): cv.int_,
    cv.Optional(CONF_MIN_DUTY_CYCLE): cv.float_range(0,1),

    }))





async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await ap.setup_airpurifier_core_(var, config)

    if CONF_POWER_EN_PIN in config:
        power_en_pin = await cg.gpio_pin_expression(config[CONF_POWER_EN_PIN])
        cg.add(var.set_power_en_pin(power_en_pin))

    if CONF_POWER_PWM_PIN in config:
        power_pwm_pin = await cg.gpio_pin_expression(config[CONF_POWER_PWM_PIN])
        cg.add(var.set_power_pwm_pin(power_pwm_pin))
    
    if CONF_FAN_PWM_PIN in config:
        pin = await cg.gpio_pin_expression(config[CONF_FAN_PWM_PIN])
        cg.add(var.set_fan_pwm_pin(pin))
        cg.add(var.set_fan_pwm_flag(True))
    
    if CONF_TACHO_PIN in config:
        tacho_pin = await cg.gpio_pin_expression(config[CONF_TACHO_PIN])
        cg.add(var.set_tacho_pin(tacho_pin))

    if CONF_POWER_PWM_CHANNEL in config:
        cg.add(var.set_power_pwm_channel(config[CONF_POWER_PWM_CHANNEL]))
    
    if CONF_FAN_PWM_CHANNEL in config:
        cg.add(var.set_fan_pwm_channel(config[CONF_FAN_PWM_CHANNEL]))

    if CONF_MAX_VOLTAGE in config:
        cg.add(var.set_max_voltage(config[CONF_MAX_VOLTAGE]))
    
    if CONF_MIN_VOLTAGE in config:
        cg.add(var.set_min_voltage(config[CONF_MIN_VOLTAGE]))

    if CONF_FAN_PWM_FREQUENCY in config:
        cg.add(var.set_fan_pwm_frequency(config[CONF_FAN_PWM_FREQUENCY]))

    if CONF_MIN_DUTY_CYCLE in config:
        cg.add(var.set_min_duty_cycle(config[CONF_MIN_DUTY_CYCLE]))
