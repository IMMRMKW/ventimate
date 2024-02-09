# my_components/my_component1/__init__.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import display, spi, ssd1331_base, ssd1331_spi
from esphome.const import CONF_DC_PIN, CONF_ID, CONF_LAMBDA, CONF_PAGES

CODEOWNERS = ["@kbx81"]

AUTO_LOAD = ["ssd1331_base"]
AUTO_LOAD = ["ssd1331_spi"]
DEPENDENCIES = ["spi"]

ssd1331_spi = cg.esphome_ns.namespace("my_component1")
MyComponent = ssd1331_spi.class_("MyComponent", ssd1331_base.SSD1331, spi.SPIDevice)

CONFIG_SCHEMA = cv.All(
    display.FULL_DISPLAY_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(MyComponent),
            
        }
    )
    .extend(cv.polling_component_schema("5s")),
    cv.has_at_most_one_key(CONF_PAGES, CONF_LAMBDA),
    cv.only_with_arduino,
    ssd1331_base.SSD1331_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(MyComponent),
            cv.Required(CONF_DC_PIN): pins.gpio_output_pin_schema,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(spi.spi_device_schema()),
    cv.has_at_most_one_key(CONF_PAGES, CONF_LAMBDA),
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await ssd1331_base.setup_ssd1331(var, config)
    await spi.register_spi_device(var, config)

    dc = await cg.gpio_pin_expression(config[CONF_DC_PIN])
    cg.add(var.set_dc_pin(dc))
