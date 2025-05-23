import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import switch
from esphome.const import (
    CONF_ASSUMED_STATE,
    CONF_ID,
    CONF_LAMBDA,
    CONF_OPTIMISTIC,
    CONF_RESTORE_STATE,
    CONF_STATE,
    CONF_TURN_OFF_ACTION,
    CONF_TURN_ON_ACTION,
)

airpurifier_ns = cg.esphome_ns.namespace('airpurifier')
AirpurifierSwitch = airpurifier_ns.class_("AirpurifierSwitch", switch.Switch, cg.Component)


def validate(config):
    if (
        not config[CONF_OPTIMISTIC]
        and CONF_TURN_ON_ACTION not in config
        and CONF_TURN_OFF_ACTION not in config
    ):
        raise cv.Invalid(
            "Either optimistic mode must be enabled, or turn_on_action or turn_off_action must be set, "
            "to handle the switch being set."
        )
    return config


CONFIG_SCHEMA = cv.All(
    switch.switch_schema(AirpurifierSwitch)
    .extend(
        {
            cv.Optional(CONF_LAMBDA): cv.returning_lambda,
            cv.Optional(CONF_OPTIMISTIC, default=False): cv.boolean,
            cv.Optional(CONF_ASSUMED_STATE, default=False): cv.boolean,
            cv.Optional(CONF_TURN_OFF_ACTION): automation.validate_automation(
                single=True
            ),
            cv.Optional(CONF_TURN_ON_ACTION): automation.validate_automation(
                single=True
            ),
            cv.Optional(CONF_RESTORE_STATE): cv.invalid(
                "The restore_state option has been removed in 2023.7.0. Use the restore_mode option instead"
            ),
        }
    )
    .extend(cv.COMPONENT_SCHEMA),
    validate,
)



async def setup_switch(config):
    
    var = await switch.new_switch(config)
    await cg.register_component(var, config)
    
    if CONF_LAMBDA in config:
        template_ = await cg.process_lambda(
            config[CONF_LAMBDA], [], return_type=cg.optional.template(bool)
        )
        cg.add(var.set_state_lambda(template_))
    if CONF_TURN_OFF_ACTION in config:
        await automation.build_automation(
            var.get_turn_off_trigger(), [], config[CONF_TURN_OFF_ACTION]
        )
    if CONF_TURN_ON_ACTION in config:
        await automation.build_automation(
            var.get_turn_on_trigger(), [], config[CONF_TURN_ON_ACTION]
        )
    cg.add(var.set_optimistic(config[CONF_OPTIMISTIC]))
    cg.add(var.set_assumed_state(config[CONF_ASSUMED_STATE]))


@automation.register_action(
    "switch.template.publish",
    switch.SwitchPublishAction,
    cv.Schema(
        {
            cv.Required(CONF_ID): cv.use_id(switch.Switch),
            cv.Required(CONF_STATE): cv.templatable(cv.boolean),
        }
    ),
)
async def switch_template_publish_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    template_ = await cg.templatable(config[CONF_STATE], args, bool)
    cg.add(var.set_state(template_))
    return var
