// Auto generated code by esphome
// ========== AUTO GENERATED INCLUDE BLOCK BEGIN ===========
#include "esphome.h"
using namespace esphome;
using std::isnan;
using std::min;
using std::max;
using namespace switch_;
using namespace text_sensor;
using namespace time;
logger::Logger *logger_logger;
web_server_base::WebServerBase *web_server_base_webserverbase;
captive_portal::CaptivePortal *captive_portal_captiveportal;
wifi::WiFiComponent *esp_wifi;
mdns::MDNSComponent *mdns_mdnscomponent;
ota::OTAComponent *ota_otacomponent;
api::APIServer *api_apiserver;
using namespace api;
using namespace sensor;
using namespace number;
using namespace i2c;
i2c::ArduinoI2CBus *i2c_arduinoi2cbus;
preferences::IntervalSyncer *preferences_intervalsyncer;
fusb302::FUSB302 *fusb302_fusb302;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin;
using namespace uart;
uart::ESP32ArduinoUARTComponent *PMS_uart;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_2;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_3;
bme680_bsec::BME680BSECComponent *bme680_bsec_bme680bseccomponent;
aqdisplay::AQDISPLAY *aqmonitor;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_4;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_5;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_6;
myfan::MYFAN *fancyfan;
sensor::Sensor *current_power;
airpurifier::AirpurifierSwitch *myfanSwitch;
switch_::SwitchTurnOnTrigger *switch__switchturnontrigger;
Automation<> *automation;
LambdaAction<> *lambdaaction;
airpurifier::AirpurifierNumber *myfanSlider;
number::NumberStateTrigger *number_numberstatetrigger;
Automation<float> *automation_2;
LambdaAction<float> *lambdaaction_2;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_7;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_8;
gpio::GPIOSwitch *pms_set;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_9;
sensor::Sensor *bme680_temperature;
sensor::MedianFilter *sensor_medianfilter;
sensor::Sensor *bme680_pressure;
sensor::MedianFilter *sensor_medianfilter_2;
sensor::Sensor *bme680_humidity;
sensor::MedianFilter *sensor_medianfilter_3;
sensor::Sensor *sensor_sensor;
sensor::MedianFilter *sensor_medianfilter_4;
sensor::Sensor *iaq;
sensor::MedianFilter *sensor_medianfilter_5;
sensor::Sensor *sensor_sensor_2;
sensor::Sensor *sensor_sensor_3;
sensor::MedianFilter *sensor_medianfilter_6;
sensor::Sensor *bvoc;
sensor::MedianFilter *sensor_medianfilter_7;
scd4x::SCD4XComponent *scd4x_scd4xcomponent;
sensor::Sensor *scd4x_co2;
sensor::Sensor *sensor_sensor_4;
sensor::Sensor *sensor_sensor_5;
pmsx003::PMSX003Component *pmsx003_pmsx003component;
sensor::Sensor *pmsx003_pm01;
sensor::Sensor *pmsx003_pm25;
sensor::Sensor *pmsx003_pm10;
text_sensor::TextSensor *text_sensor_textsensor;
template_::TemplateTextSensor *iaq_classification;
using namespace output;
gpio::GPIOBinaryOutput *statusLED;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_10;
homeassistant::HomeassistantTime *esptime;
interval::IntervalTrigger *interval_intervaltrigger;
Automation<> *automation_3;
switch_::TurnOnAction<> *switch__turnonaction;
DelayAction<> *delayaction;
switch_::TurnOffAction<> *switch__turnoffaction;
interval::IntervalTrigger *interval_intervaltrigger_2;
Automation<> *automation_4;
output::TurnOnAction<> *output_turnonaction;
DelayAction<> *delayaction_2;
output::TurnOffAction<> *output_turnoffaction;
#define yield() esphome::yield()
#define millis() esphome::millis()
#define micros() esphome::micros()
#define delay(x) esphome::delay(x)
#define delayMicroseconds(x) esphome::delayMicroseconds(x)
#include "airpurifier.h"
// ========== AUTO GENERATED INCLUDE BLOCK END ==========="

void setup() {
  // ========== AUTO GENERATED CODE BEGIN ===========
  // async_tcp:
  //   {}
  // esphome:
  //   name: esphome-web-79a218
  //   friendly_name: My Only Fan
  //   includes:
  //   - components/airpurifier/airpurifier.h
  //   build_path: build/esphome-web-79a218
  //   area: ''
  //   platformio_options: {}
  //   libraries: []
  //   name_add_mac_suffix: false
  //   min_version: 2024.3.0
  App.pre_setup("esphome-web-79a218", "My Only Fan", "", "", __DATE__ ", " __TIME__, false);
  // switch:
  // text_sensor:
  // time:
  // logger:
  //   id: logger_logger
  //   baud_rate: 115200
  //   tx_buffer_size: 512
  //   deassert_rts_dtr: false
  //   hardware_uart: UART0
  //   level: DEBUG
  //   logs: {}
  logger_logger = new logger::Logger(115200, 512);
  logger_logger->set_uart_selection(logger::UART_SELECTION_UART0);
  logger_logger->pre_setup();
  logger_logger->set_component_source("logger");
  App.register_component(logger_logger);
  // web_server_base:
  //   id: web_server_base_webserverbase
  web_server_base_webserverbase = new web_server_base::WebServerBase();
  web_server_base_webserverbase->set_component_source("web_server_base");
  App.register_component(web_server_base_webserverbase);
  // captive_portal:
  //   id: captive_portal_captiveportal
  //   web_server_base_id: web_server_base_webserverbase
  captive_portal_captiveportal = new captive_portal::CaptivePortal(web_server_base_webserverbase);
  captive_portal_captiveportal->set_component_source("captive_portal");
  App.register_component(captive_portal_captiveportal);
  // wifi:
  //   id: esp_wifi
  //   ap:
  //     ssid: Esphome-Web-79A218
  //     password: bJhPXchn93Ux
  //     id: wifi_wifiap
  //     ap_timeout: 1min
  //   domain: .local
  //   reboot_timeout: 15min
  //   power_save_mode: LIGHT
  //   fast_connect: false
  //   passive_scan: false
  //   enable_on_boot: true
  //   networks:
  //   - ssid: !secret 'wifi_ssid'
  //     password: !secret 'wifi_password'
  //     id: wifi_wifiap_2
  //     priority: 0.0
  //   use_address: esphome-web-79a218.local
  esp_wifi = new wifi::WiFiComponent();
  esp_wifi->set_use_address("esphome-web-79a218.local");
  {
  wifi::WiFiAP wifi_wifiap_2 = wifi::WiFiAP();
  wifi_wifiap_2.set_ssid("FRITZ!Box 5490 GB");
  wifi_wifiap_2.set_password("65078093878898291217");
  wifi_wifiap_2.set_priority(0.0f);
  esp_wifi->add_sta(wifi_wifiap_2);
  }
  {
  wifi::WiFiAP wifi_wifiap = wifi::WiFiAP();
  wifi_wifiap.set_ssid("Esphome-Web-79A218");
  wifi_wifiap.set_password("bJhPXchn93Ux");
  esp_wifi->set_ap(wifi_wifiap);
  }
  esp_wifi->set_ap_timeout(60000);
  esp_wifi->set_reboot_timeout(900000);
  esp_wifi->set_power_save_mode(wifi::WIFI_POWER_SAVE_LIGHT);
  esp_wifi->set_fast_connect(false);
  esp_wifi->set_passive_scan(false);
  esp_wifi->set_enable_on_boot(true);
  esp_wifi->set_component_source("wifi");
  App.register_component(esp_wifi);
  // mdns:
  //   id: mdns_mdnscomponent
  //   disabled: false
  //   services: []
  mdns_mdnscomponent = new mdns::MDNSComponent();
  mdns_mdnscomponent->set_component_source("mdns");
  App.register_component(mdns_mdnscomponent);
  // ota:
  //   id: ota_otacomponent
  //   safe_mode: true
  //   version: 2
  //   port: 3232
  //   reboot_timeout: 5min
  //   num_attempts: 10
  ota_otacomponent = new ota::OTAComponent();
  ota_otacomponent->set_port(3232);
  ota_otacomponent->set_component_source("ota");
  App.register_component(ota_otacomponent);
  if (ota_otacomponent->should_enter_safe_mode(10, 300000)) return;
  // api:
  //   encryption:
  //     key: Hcbp/oa8VWQlhAf43Wk14DNFKqqNPyOP2ZOKlPQNpNg=
  //   id: api_apiserver
  //   port: 6053
  //   password: ''
  //   reboot_timeout: 15min
  api_apiserver = new api::APIServer();
  api_apiserver->set_component_source("api");
  App.register_component(api_apiserver);
  api_apiserver->set_port(6053);
  api_apiserver->set_password("");
  api_apiserver->set_reboot_timeout(900000);
  api_apiserver->set_noise_psk({29, 198, 233, 254, 134, 188, 85, 100, 37, 132, 7, 248, 221, 105, 53, 224, 51, 69, 42, 170, 141, 63, 35, 143, 217, 147, 138, 148, 244, 13, 164, 216});
  // sensor:
  // number:
  // i2c:
  //   id: i2c_arduinoi2cbus
  //   sda: 21
  //   scl: 22
  //   frequency: 50000.0
  //   scan: true
  i2c_arduinoi2cbus = new i2c::ArduinoI2CBus();
  i2c_arduinoi2cbus->set_component_source("i2c");
  App.register_component(i2c_arduinoi2cbus);
  i2c_arduinoi2cbus->set_sda_pin(21);
  i2c_arduinoi2cbus->set_scl_pin(22);
  i2c_arduinoi2cbus->set_frequency(50000);
  i2c_arduinoi2cbus->set_scan(true);
  // substitutions:
  //   pm_2_5_substitution: '[12, 35, 55, 150, 250]'
  // esp32:
  //   board: esp32dev
  //   framework:
  //     version: 2.0.5
  //     source: ~3.20005.0
  //     platform_version: platformio/espressif32@5.4.0
  //     type: arduino
  //   flash_size: 4MB
  //   variant: ESP32
  // preferences:
  //   id: preferences_intervalsyncer
  //   flash_write_interval: 60s
  preferences_intervalsyncer = new preferences::IntervalSyncer();
  preferences_intervalsyncer->set_write_interval(60000);
  preferences_intervalsyncer->set_component_source("preferences");
  App.register_component(preferences_intervalsyncer);
  // external_components:
  //   - source:
  //       path: components
  //       type: local
  //     refresh: 1d
  //     components: all
  // fusb302:
  //   setup_priority: 900.0
  //   maximum_supply_voltage: 9v
  //   interrupt_pin:
  //     number: 36
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin
  //     inverted: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   id: fusb302_fusb302
  //   i2c_id: i2c_arduinoi2cbus
  //   address: 0x22
  //   update_interval: 10s
  fusb302_fusb302 = new fusb302::FUSB302();
  fusb302_fusb302->set_setup_priority(900.0f);
  fusb302_fusb302->set_update_interval(10000);
  fusb302_fusb302->set_component_source("fusb302");
  App.register_component(fusb302_fusb302);
  fusb302_fusb302->set_i2c_bus(i2c_arduinoi2cbus);
  fusb302_fusb302->set_i2c_address(0x22);
  fusb302_fusb302->set_maximum_supply_voltage(fusb302::PD9V);
  esp32_esp32internalgpiopin = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin->set_pin(::GPIO_NUM_36);
  esp32_esp32internalgpiopin->set_inverted(false);
  esp32_esp32internalgpiopin->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin->set_flags(gpio::Flags::FLAG_INPUT);
  fusb302_fusb302->set_interrupt_pin(esp32_esp32internalgpiopin);
  // uart:
  //   id: PMS_uart
  //   tx_pin:
  //     number: 17
  //     mode:
  //       output: true
  //       input: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_2
  //     inverted: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   rx_pin:
  //     number: 16
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_3
  //     inverted: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   baud_rate: 9600
  //   rx_buffer_size: 256
  //   stop_bits: 1
  //   data_bits: 8
  //   parity: NONE
  PMS_uart = new uart::ESP32ArduinoUARTComponent();
  PMS_uart->set_component_source("uart");
  App.register_component(PMS_uart);
  PMS_uart->set_baud_rate(9600);
  esp32_esp32internalgpiopin_2 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_2->set_pin(::GPIO_NUM_17);
  esp32_esp32internalgpiopin_2->set_inverted(false);
  esp32_esp32internalgpiopin_2->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_2->set_flags(gpio::Flags::FLAG_OUTPUT);
  PMS_uart->set_tx_pin(esp32_esp32internalgpiopin_2);
  esp32_esp32internalgpiopin_3 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_3->set_pin(::GPIO_NUM_16);
  esp32_esp32internalgpiopin_3->set_inverted(false);
  esp32_esp32internalgpiopin_3->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_3->set_flags(gpio::Flags::FLAG_INPUT);
  PMS_uart->set_rx_pin(esp32_esp32internalgpiopin_3);
  PMS_uart->set_rx_buffer_size(256);
  PMS_uart->set_stop_bits(1);
  PMS_uart->set_data_bits(8);
  PMS_uart->set_parity(uart::UART_CONFIG_PARITY_NONE);
  // bme680_bsec:
  //   address: 0x77
  //   temperature_offset: 0.0
  //   iaq_mode: STATIC
  //   sample_rate: LP
  //   state_save_interval: 6h
  //   id: bme680_bsec_bme680bseccomponent
  //   i2c_id: i2c_arduinoi2cbus
  bme680_bsec_bme680bseccomponent = new bme680_bsec::BME680BSECComponent();
  bme680_bsec_bme680bseccomponent->set_component_source("bme680_bsec");
  App.register_component(bme680_bsec_bme680bseccomponent);
  bme680_bsec_bme680bseccomponent->set_i2c_bus(i2c_arduinoi2cbus);
  bme680_bsec_bme680bseccomponent->set_i2c_address(0x77);
  bme680_bsec_bme680bseccomponent->set_device_id("bme680_bsec_bme680bseccomponent");
  bme680_bsec_bme680bseccomponent->set_temperature_offset(0.0f);
  bme680_bsec_bme680bseccomponent->set_iaq_mode(bme680_bsec::IAQ_MODE_STATIC);
  bme680_bsec_bme680bseccomponent->set_sample_rate(bme680_bsec::SAMPLE_RATE_LP);
  bme680_bsec_bme680bseccomponent->set_state_save_interval(21600000);
  // aqdisplay:
  //   id: aqmonitor
  //   chip_select_pin:
  //     number: 5
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_4
  //     inverted: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   dc_pin:
  //     number: 19
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_5
  //     inverted: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   reset_pin:
  //     number: 4
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_6
  //     inverted: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   sensor_co2: scd4x_co2
  //   sensor_pm_1_0: pmsx003_pm01
  //   sensor_pm_2_5: pmsx003_pm25
  //   sensor_pm_10: pmsx003_pm10
  //   sensor_voc: bvoc
  //   sensor_rh: bme680_humidity
  //   sensor_temp: bme680_temperature
  //   sensor_fan_power: current_power
  //   clock: esptime
  //   network: esp_wifi
  //   co2_levels:
  //   - 650
  //   - 1500
  //   - 2000
  //   - 2500
  //   - 5000
  //   pm_1_0_levels:
  //   - 12
  //   - 35
  //   - 55
  //   - 150
  //   - 250
  //   pm_2_5_levels:
  //   - 12
  //   - 35
  //   - 55
  //   - 150
  //   - 250
  //   pm_10_levels:
  //   - 54
  //   - 154
  //   - 254
  //   - 354
  //   - 424
  //   voc_levels:
  //   - 15
  //   - 25
  //   - 50
  //   - 75
  //   - 100
  //   update_interval: 1s
  aqmonitor = new aqdisplay::AQDISPLAY();
  aqmonitor->set_update_interval(1000);
  aqmonitor->set_component_source("aqdisplay");
  App.register_component(aqmonitor);
  esp32_esp32internalgpiopin_4 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_4->set_pin(::GPIO_NUM_5);
  esp32_esp32internalgpiopin_4->set_inverted(false);
  esp32_esp32internalgpiopin_4->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_4->set_flags(gpio::Flags::FLAG_INPUT);
  aqmonitor->set_cs_pin(esp32_esp32internalgpiopin_4);
  esp32_esp32internalgpiopin_5 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_5->set_pin(::GPIO_NUM_19);
  esp32_esp32internalgpiopin_5->set_inverted(false);
  esp32_esp32internalgpiopin_5->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_5->set_flags(gpio::Flags::FLAG_INPUT);
  aqmonitor->set_dc_pin(esp32_esp32internalgpiopin_5);
  esp32_esp32internalgpiopin_6 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_6->set_pin(::GPIO_NUM_4);
  esp32_esp32internalgpiopin_6->set_inverted(false);
  esp32_esp32internalgpiopin_6->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_6->set_flags(gpio::Flags::FLAG_INPUT);
  aqmonitor->set_rst_pin(esp32_esp32internalgpiopin_6);
  // airpurifier.myfan:
  //   platform: myfan
  //   id: fancyfan
  //   power_enable_pin:
  //     number: 33
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_7
  //     inverted: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   power_pwm_pin:
  //     number: 2
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_8
  //     inverted: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   min_voltage: 3.6
  //   purge_interval: 30
  //   purge_duration: 10
  //   power_sensor:
  //     name: Current power
  //     id: current_power
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: '%'
  //     icon: mdi:fan
  //     accuracy_decimals: 0
  //     device_class: speed
  //     state_class: measurement
  //   switcher:
  //     name: manual/auto
  //     id: myfanSwitch
  //     optimistic: true
  //     on_turn_on:
  //     - then:
  //       - lambda: !lambda |-
  //           id(fancyfan).set_manual(true);
  //         type_id: lambdaaction
  //       automation_id: automation
  //       trigger_id: switch__switchturnontrigger
  //     disabled_by_default: false
  //     restore_mode: ALWAYS_OFF
  //     assumed_state: false
  //   max_pwm:
  //     name: Max power
  //     id: myfanSlider
  //     min_value: 1.0
  //     max_value: 100.0
  //     step: 1.0
  //     initial_value: 100.0
  //     optimistic: true
  //     on_value:
  //     - then:
  //       - lambda: !lambda "id(fancyfan).set_max_power(x); \n   "
  //         type_id: lambdaaction_2
  //       automation_id: automation_2
  //       trigger_id: number_numberstatetrigger
  //     disabled_by_default: false
  //     mode: AUTO
  //     update_interval: 60s
  //   proportional_gain:
  //   - 20
  //   - 40
  //   - 60
  //   - 80
  //   - 100
  //   integral_gain:
  //   - 60
  //   - 120
  //   - 1800
  //   - 3600
  //   - 7200
  //   pm_2_5_levels:
  //   - 12
  //   - 35
  //   - 55
  //   - 150
  //   - 250
  //   pm_10_levels:
  //   - 54
  //   - 154
  //   - 254
  //   - 354
  //   - 424
  //   voc_levels:
  //   - 15
  //   - 25
  //   - 50
  //   - 75
  //   - 100
  //   co2_levels:
  //   - 650
  //   - 1500
  //   - 2000
  //   - 2500
  //   - 5000
  //   use_purge: true
  //   purge_power: 25
  //   update_interval: 1s
  //   power_pwm_channel: 14
  //   fan_pwm_channel: 15
  //   max_voltage: 12.0
  fancyfan = new myfan::MYFAN();
  fancyfan->set_update_interval(1000);
  fancyfan->set_component_source("myfan.airpurifier");
  App.register_component(fancyfan);
  current_power = new sensor::Sensor();
  App.register_sensor(current_power);
  current_power->set_name("Current power");
  current_power->set_object_id("current_power");
  current_power->set_disabled_by_default(false);
  current_power->set_icon("mdi:fan");
  current_power->set_device_class("speed");
  current_power->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  current_power->set_unit_of_measurement("%");
  current_power->set_accuracy_decimals(0);
  current_power->set_force_update(false);
  fancyfan->set_sensor_power(current_power);
  fancyfan->set_pm_2_5_levels({12, 35, 55, 150, 250});
  fancyfan->set_pm_10_levels({54, 154, 254, 354, 424});
  fancyfan->set_voc_levels({15, 25, 50, 75, 100});
  fancyfan->set_co2_levels({650, 1500, 2000, 2500, 5000});
  fancyfan->set_purge(true);
  fancyfan->set_purge_duration(10);
  fancyfan->set_purge_interval(30);
  fancyfan->set_purge_power(25);
  fancyfan->set_integral_gain({60, 120, 1800, 3600, 7200});
  fancyfan->set_proportional_gain({20, 40, 60, 80, 100});
  myfanSwitch = new airpurifier::AirpurifierSwitch();
  App.register_switch(myfanSwitch);
  myfanSwitch->set_name("manual/auto");
  myfanSwitch->set_object_id("manual_auto");
  myfanSwitch->set_disabled_by_default(false);
  switch__switchturnontrigger = new switch_::SwitchTurnOnTrigger(myfanSwitch);
  automation = new Automation<>(switch__switchturnontrigger);
  lambdaaction = new LambdaAction<>([=]() -> void {
      #line 219 "config.yml"
      fancyfan->set_manual(true);
  });
  automation->add_actions({lambdaaction});
  myfanSwitch->set_restore_mode(switch_::SWITCH_ALWAYS_OFF);
  myfanSwitch->set_component_source("airpurifier.airpurifier_switch");
  App.register_component(myfanSwitch);
  myfanSwitch->set_optimistic(true);
  myfanSwitch->set_assumed_state(false);
  myfanSlider = new airpurifier::AirpurifierNumber();
  myfanSlider->set_update_interval(60000);
  myfanSlider->set_component_source("airpurifier.airpurifier_number");
  App.register_component(myfanSlider);
  App.register_number(myfanSlider);
  myfanSlider->set_name("Max power");
  myfanSlider->set_object_id("max_power");
  myfanSlider->set_disabled_by_default(false);
  myfanSlider->traits.set_min_value(1.0f);
  myfanSlider->traits.set_max_value(100.0f);
  myfanSlider->traits.set_step(1.0f);
  myfanSlider->traits.set_mode(number::NUMBER_MODE_AUTO);
  number_numberstatetrigger = new number::NumberStateTrigger(myfanSlider);
  automation_2 = new Automation<float>(number_numberstatetrigger);
  lambdaaction_2 = new LambdaAction<float>([=](float x) -> void {
      #line 235 "config.yml"
      fancyfan->set_max_power(x); 
         
  });
  automation_2->add_actions({lambdaaction_2});
  myfanSlider->set_optimistic(true);
  myfanSlider->set_initial_value(100.0f);
  esp32_esp32internalgpiopin_7 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_7->set_pin(::GPIO_NUM_33);
  esp32_esp32internalgpiopin_7->set_inverted(false);
  esp32_esp32internalgpiopin_7->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_7->set_flags(gpio::Flags::FLAG_INPUT);
  fancyfan->set_power_en_pin(esp32_esp32internalgpiopin_7);
  esp32_esp32internalgpiopin_8 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_8->set_pin(::GPIO_NUM_2);
  esp32_esp32internalgpiopin_8->set_inverted(false);
  esp32_esp32internalgpiopin_8->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_8->set_flags(gpio::Flags::FLAG_INPUT);
  fancyfan->set_power_pwm_pin(esp32_esp32internalgpiopin_8);
  fancyfan->set_power_pwm_channel(14);
  fancyfan->set_fan_pwm_channel(15);
  fancyfan->set_max_voltage(12.0f);
  fancyfan->set_min_voltage(3.6f);
  // switch.gpio:
  //   platform: gpio
  //   pin:
  //     number: 12
  //     mode:
  //       output: true
  //       input: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_9
  //     inverted: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   id: pms_set
  //   name: Start measuring PM concentrations
  //   internal: true
  //   disabled_by_default: false
  //   restore_mode: ALWAYS_OFF
  //   interlock_wait_time: 0ms
  pms_set = new gpio::GPIOSwitch();
  App.register_switch(pms_set);
  pms_set->set_name("Start measuring PM concentrations");
  pms_set->set_object_id("start_measuring_pm_concentrations");
  pms_set->set_disabled_by_default(false);
  pms_set->set_internal(true);
  pms_set->set_restore_mode(switch_::SWITCH_ALWAYS_OFF);
  pms_set->set_component_source("gpio.switch");
  App.register_component(pms_set);
  esp32_esp32internalgpiopin_9 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_9->set_pin(::GPIO_NUM_12);
  esp32_esp32internalgpiopin_9->set_inverted(false);
  esp32_esp32internalgpiopin_9->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_9->set_flags(gpio::Flags::FLAG_OUTPUT);
  pms_set->set_pin(esp32_esp32internalgpiopin_9);
  // sensor.bme680_bsec:
  //   platform: bme680_bsec
  //   temperature:
  //     name: BME680 Temperature
  //     id: bme680_temperature
  //     sample_rate: LP
  //     filters:
  //     - median:
  //         window_size: 5
  //         send_every: 5
  //         send_first_at: 1
  //       type_id: sensor_medianfilter
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: °C
  //     accuracy_decimals: 1
  //     device_class: temperature
  //     state_class: measurement
  //   pressure:
  //     name: BME680 Pressure
  //     id: bme680_pressure
  //     sample_rate: LP
  //     filters:
  //     - median:
  //         window_size: 5
  //         send_every: 5
  //         send_first_at: 1
  //       type_id: sensor_medianfilter_2
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: hPa
  //     accuracy_decimals: 1
  //     device_class: atmospheric_pressure
  //     state_class: measurement
  //   humidity:
  //     name: BME680 Humidity
  //     id: bme680_humidity
  //     sample_rate: LP
  //     filters:
  //     - median:
  //         window_size: 5
  //         send_every: 5
  //         send_first_at: 1
  //       type_id: sensor_medianfilter_3
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: '%'
  //     accuracy_decimals: 1
  //     device_class: humidity
  //     state_class: measurement
  //   gas_resistance:
  //     name: BME680 Gas Resistance
  //     internal: true
  //     filters:
  //     - median:
  //         window_size: 5
  //         send_every: 5
  //         send_first_at: 1
  //       type_id: sensor_medianfilter_4
  //     disabled_by_default: false
  //     id: sensor_sensor
  //     force_update: false
  //     unit_of_measurement: Ω
  //     icon: mdi:gas-cylinder
  //     accuracy_decimals: 0
  //     state_class: measurement
  //   iaq:
  //     name: BME680 IAQ
  //     id: iaq
  //     filters:
  //     - median:
  //         window_size: 5
  //         send_every: 5
  //         send_first_at: 1
  //       type_id: sensor_medianfilter_5
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: IAQ
  //     icon: mdi:gauge
  //     accuracy_decimals: 0
  //     state_class: measurement
  //   iaq_accuracy:
  //     name: BME680 Numeric IAQ Accuracy
  //     internal: true
  //     disabled_by_default: false
  //     id: sensor_sensor_2
  //     force_update: false
  //     icon: mdi:checkbox-marked-circle-outline
  //     accuracy_decimals: 0
  //     state_class: measurement
  //   co2_equivalent:
  //     name: BME680 CO2 Equivalent
  //     internal: true
  //     filters:
  //     - median:
  //         window_size: 5
  //         send_every: 5
  //         send_first_at: 1
  //       type_id: sensor_medianfilter_6
  //     disabled_by_default: false
  //     id: sensor_sensor_3
  //     force_update: false
  //     unit_of_measurement: ppm
  //     accuracy_decimals: 1
  //     device_class: carbon_dioxide
  //     state_class: measurement
  //   breath_voc_equivalent:
  //     id: bvoc
  //     name: BME680 Breath VOC Equivalent
  //     internal: false
  //     filters:
  //     - median:
  //         window_size: 5
  //         send_every: 5
  //         send_first_at: 1
  //       type_id: sensor_medianfilter_7
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: ppm
  //     accuracy_decimals: 1
  //     device_class: volatile_organic_compounds_parts
  //     state_class: measurement
  //   bme680_bsec_id: bme680_bsec_bme680bseccomponent
  bme680_temperature = new sensor::Sensor();
  App.register_sensor(bme680_temperature);
  bme680_temperature->set_name("BME680 Temperature");
  bme680_temperature->set_object_id("bme680_temperature");
  bme680_temperature->set_disabled_by_default(false);
  bme680_temperature->set_device_class("temperature");
  bme680_temperature->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  bme680_temperature->set_unit_of_measurement("\302\260C");
  bme680_temperature->set_accuracy_decimals(1);
  bme680_temperature->set_force_update(false);
  sensor_medianfilter = new sensor::MedianFilter(5, 5, 1);
  bme680_temperature->set_filters({sensor_medianfilter});
  bme680_bsec_bme680bseccomponent->set_temperature_sensor(bme680_temperature);
  bme680_bsec_bme680bseccomponent->set_temperature_sample_rate(bme680_bsec::SAMPLE_RATE_LP);
  bme680_pressure = new sensor::Sensor();
  App.register_sensor(bme680_pressure);
  bme680_pressure->set_name("BME680 Pressure");
  bme680_pressure->set_object_id("bme680_pressure");
  bme680_pressure->set_disabled_by_default(false);
  bme680_pressure->set_device_class("atmospheric_pressure");
  bme680_pressure->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  bme680_pressure->set_unit_of_measurement("hPa");
  bme680_pressure->set_accuracy_decimals(1);
  bme680_pressure->set_force_update(false);
  sensor_medianfilter_2 = new sensor::MedianFilter(5, 5, 1);
  bme680_pressure->set_filters({sensor_medianfilter_2});
  bme680_bsec_bme680bseccomponent->set_pressure_sensor(bme680_pressure);
  bme680_bsec_bme680bseccomponent->set_pressure_sample_rate(bme680_bsec::SAMPLE_RATE_LP);
  bme680_humidity = new sensor::Sensor();
  App.register_sensor(bme680_humidity);
  bme680_humidity->set_name("BME680 Humidity");
  bme680_humidity->set_object_id("bme680_humidity");
  bme680_humidity->set_disabled_by_default(false);
  bme680_humidity->set_device_class("humidity");
  bme680_humidity->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  bme680_humidity->set_unit_of_measurement("%");
  bme680_humidity->set_accuracy_decimals(1);
  bme680_humidity->set_force_update(false);
  sensor_medianfilter_3 = new sensor::MedianFilter(5, 5, 1);
  bme680_humidity->set_filters({sensor_medianfilter_3});
  bme680_bsec_bme680bseccomponent->set_humidity_sensor(bme680_humidity);
  bme680_bsec_bme680bseccomponent->set_humidity_sample_rate(bme680_bsec::SAMPLE_RATE_LP);
  sensor_sensor = new sensor::Sensor();
  App.register_sensor(sensor_sensor);
  sensor_sensor->set_name("BME680 Gas Resistance");
  sensor_sensor->set_object_id("bme680_gas_resistance");
  sensor_sensor->set_disabled_by_default(false);
  sensor_sensor->set_internal(true);
  sensor_sensor->set_icon("mdi:gas-cylinder");
  sensor_sensor->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  sensor_sensor->set_unit_of_measurement("\316\251");
  sensor_sensor->set_accuracy_decimals(0);
  sensor_sensor->set_force_update(false);
  sensor_medianfilter_4 = new sensor::MedianFilter(5, 5, 1);
  sensor_sensor->set_filters({sensor_medianfilter_4});
  bme680_bsec_bme680bseccomponent->set_gas_resistance_sensor(sensor_sensor);
  iaq = new sensor::Sensor();
  App.register_sensor(iaq);
  iaq->set_name("BME680 IAQ");
  iaq->set_object_id("bme680_iaq");
  iaq->set_disabled_by_default(false);
  iaq->set_icon("mdi:gauge");
  iaq->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  iaq->set_unit_of_measurement("IAQ");
  iaq->set_accuracy_decimals(0);
  iaq->set_force_update(false);
  sensor_medianfilter_5 = new sensor::MedianFilter(5, 5, 1);
  iaq->set_filters({sensor_medianfilter_5});
  bme680_bsec_bme680bseccomponent->set_iaq_sensor(iaq);
  sensor_sensor_2 = new sensor::Sensor();
  App.register_sensor(sensor_sensor_2);
  sensor_sensor_2->set_name("BME680 Numeric IAQ Accuracy");
  sensor_sensor_2->set_object_id("bme680_numeric_iaq_accuracy");
  sensor_sensor_2->set_disabled_by_default(false);
  sensor_sensor_2->set_internal(true);
  sensor_sensor_2->set_icon("mdi:checkbox-marked-circle-outline");
  sensor_sensor_2->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  sensor_sensor_2->set_accuracy_decimals(0);
  sensor_sensor_2->set_force_update(false);
  bme680_bsec_bme680bseccomponent->set_iaq_accuracy_sensor(sensor_sensor_2);
  sensor_sensor_3 = new sensor::Sensor();
  App.register_sensor(sensor_sensor_3);
  sensor_sensor_3->set_name("BME680 CO2 Equivalent");
  sensor_sensor_3->set_object_id("bme680_co2_equivalent");
  sensor_sensor_3->set_disabled_by_default(false);
  sensor_sensor_3->set_internal(true);
  sensor_sensor_3->set_device_class("carbon_dioxide");
  sensor_sensor_3->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  sensor_sensor_3->set_unit_of_measurement("ppm");
  sensor_sensor_3->set_accuracy_decimals(1);
  sensor_sensor_3->set_force_update(false);
  sensor_medianfilter_6 = new sensor::MedianFilter(5, 5, 1);
  sensor_sensor_3->set_filters({sensor_medianfilter_6});
  bme680_bsec_bme680bseccomponent->set_co2_equivalent_sensor(sensor_sensor_3);
  bvoc = new sensor::Sensor();
  App.register_sensor(bvoc);
  bvoc->set_name("BME680 Breath VOC Equivalent");
  bvoc->set_object_id("bme680_breath_voc_equivalent");
  bvoc->set_disabled_by_default(false);
  bvoc->set_internal(false);
  bvoc->set_device_class("volatile_organic_compounds_parts");
  bvoc->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  bvoc->set_unit_of_measurement("ppm");
  bvoc->set_accuracy_decimals(1);
  bvoc->set_force_update(false);
  sensor_medianfilter_7 = new sensor::MedianFilter(5, 5, 1);
  bvoc->set_filters({sensor_medianfilter_7});
  bme680_bsec_bme680bseccomponent->set_breath_voc_equivalent_sensor(bvoc);
  // sensor.scd4x:
  //   platform: scd4x
  //   address: 0x62
  //   temperature_offset: 3.0
  //   update_interval: 5s
  //   temperature:
  //     name: SCD4x Temperature
  //     internal: true
  //     disabled_by_default: false
  //     id: sensor_sensor_4
  //     force_update: false
  //     unit_of_measurement: °C
  //     icon: mdi:thermometer
  //     accuracy_decimals: 2
  //     device_class: temperature
  //     state_class: measurement
  //   humidity:
  //     name: SCD4x Humidity
  //     internal: true
  //     disabled_by_default: false
  //     id: sensor_sensor_5
  //     force_update: false
  //     unit_of_measurement: '%'
  //     icon: mdi:water-percent
  //     accuracy_decimals: 2
  //     device_class: humidity
  //     state_class: measurement
  //   co2:
  //     name: SCD4x CO2
  //     id: scd4x_co2
  //     internal: true
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: ppm
  //     icon: mdi:molecule-co2
  //     accuracy_decimals: 0
  //     device_class: carbon_dioxide
  //     state_class: measurement
  //   id: scd4x_scd4xcomponent
  //   automatic_self_calibration: true
  //   altitude_compensation: 0
  //   measurement_mode: periodic
  //   i2c_id: i2c_arduinoi2cbus
  scd4x_scd4xcomponent = new scd4x::SCD4XComponent();
  scd4x_scd4xcomponent->set_update_interval(5000);
  scd4x_scd4xcomponent->set_component_source("scd4x.sensor");
  App.register_component(scd4x_scd4xcomponent);
  scd4x_scd4xcomponent->set_i2c_bus(i2c_arduinoi2cbus);
  scd4x_scd4xcomponent->set_i2c_address(0x62);
  scd4x_scd4xcomponent->set_automatic_self_calibration(true);
  scd4x_scd4xcomponent->set_altitude_compensation(0);
  scd4x_scd4xcomponent->set_temperature_offset(3.0f);
  scd4x_co2 = new sensor::Sensor();
  App.register_sensor(scd4x_co2);
  scd4x_co2->set_name("SCD4x CO2");
  scd4x_co2->set_object_id("scd4x_co2");
  scd4x_co2->set_disabled_by_default(false);
  scd4x_co2->set_internal(true);
  scd4x_co2->set_icon("mdi:molecule-co2");
  scd4x_co2->set_device_class("carbon_dioxide");
  scd4x_co2->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  scd4x_co2->set_unit_of_measurement("ppm");
  scd4x_co2->set_accuracy_decimals(0);
  scd4x_co2->set_force_update(false);
  scd4x_scd4xcomponent->set_co2_sensor(scd4x_co2);
  sensor_sensor_4 = new sensor::Sensor();
  App.register_sensor(sensor_sensor_4);
  sensor_sensor_4->set_name("SCD4x Temperature");
  sensor_sensor_4->set_object_id("scd4x_temperature");
  sensor_sensor_4->set_disabled_by_default(false);
  sensor_sensor_4->set_internal(true);
  sensor_sensor_4->set_icon("mdi:thermometer");
  sensor_sensor_4->set_device_class("temperature");
  sensor_sensor_4->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  sensor_sensor_4->set_unit_of_measurement("\302\260C");
  sensor_sensor_4->set_accuracy_decimals(2);
  sensor_sensor_4->set_force_update(false);
  scd4x_scd4xcomponent->set_temperature_sensor(sensor_sensor_4);
  sensor_sensor_5 = new sensor::Sensor();
  App.register_sensor(sensor_sensor_5);
  sensor_sensor_5->set_name("SCD4x Humidity");
  sensor_sensor_5->set_object_id("scd4x_humidity");
  sensor_sensor_5->set_disabled_by_default(false);
  sensor_sensor_5->set_internal(true);
  sensor_sensor_5->set_icon("mdi:water-percent");
  sensor_sensor_5->set_device_class("humidity");
  sensor_sensor_5->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  sensor_sensor_5->set_unit_of_measurement("%");
  sensor_sensor_5->set_accuracy_decimals(2);
  sensor_sensor_5->set_force_update(false);
  scd4x_scd4xcomponent->set_humidity_sensor(sensor_sensor_5);
  scd4x_scd4xcomponent->set_measurement_mode(scd4x::PERIODIC);
  // sensor.pmsx003:
  //   platform: pmsx003
  //   uart_id: PMS_uart
  //   type: PMSX003
  //   pm_1_0:
  //     name: PM < 1.0 µm
  //     id: pmsx003_pm01
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: µg/m³
  //     icon: mdi:chemical-weapon
  //     accuracy_decimals: 0
  //     device_class: pm1
  //     state_class: measurement
  //   pm_2_5:
  //     name: PM < 2.5 µm
  //     id: pmsx003_pm25
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: µg/m³
  //     icon: mdi:chemical-weapon
  //     accuracy_decimals: 0
  //     device_class: pm25
  //     state_class: measurement
  //   pm_10_0:
  //     name: PM < 10.0 µm
  //     id: pmsx003_pm10
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: µg/m³
  //     icon: mdi:chemical-weapon
  //     accuracy_decimals: 0
  //     device_class: pm10
  //     state_class: measurement
  //   id: pmsx003_pmsx003component
  //   update_interval: 0s
  pmsx003_pmsx003component = new pmsx003::PMSX003Component();
  pmsx003_pmsx003component->set_update_interval(0);
  pmsx003_pmsx003component->set_component_source("pmsx003.sensor");
  App.register_component(pmsx003_pmsx003component);
  pmsx003_pmsx003component->set_uart_parent(PMS_uart);
  pmsx003_pmsx003component->set_type(pmsx003::PMSX003_TYPE_X003);
  pmsx003_pm01 = new sensor::Sensor();
  App.register_sensor(pmsx003_pm01);
  pmsx003_pm01->set_name("PM < 1.0 \302\265m");
  pmsx003_pm01->set_object_id("pm___1_0__m");
  pmsx003_pm01->set_disabled_by_default(false);
  pmsx003_pm01->set_icon("mdi:chemical-weapon");
  pmsx003_pm01->set_device_class("pm1");
  pmsx003_pm01->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  pmsx003_pm01->set_unit_of_measurement("\302\265g/m\302\263");
  pmsx003_pm01->set_accuracy_decimals(0);
  pmsx003_pm01->set_force_update(false);
  pmsx003_pmsx003component->set_pm_1_0_sensor(pmsx003_pm01);
  pmsx003_pm25 = new sensor::Sensor();
  App.register_sensor(pmsx003_pm25);
  pmsx003_pm25->set_name("PM < 2.5 \302\265m");
  pmsx003_pm25->set_object_id("pm___2_5__m");
  pmsx003_pm25->set_disabled_by_default(false);
  pmsx003_pm25->set_icon("mdi:chemical-weapon");
  pmsx003_pm25->set_device_class("pm25");
  pmsx003_pm25->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  pmsx003_pm25->set_unit_of_measurement("\302\265g/m\302\263");
  pmsx003_pm25->set_accuracy_decimals(0);
  pmsx003_pm25->set_force_update(false);
  pmsx003_pmsx003component->set_pm_2_5_sensor(pmsx003_pm25);
  pmsx003_pm10 = new sensor::Sensor();
  App.register_sensor(pmsx003_pm10);
  pmsx003_pm10->set_name("PM < 10.0 \302\265m");
  pmsx003_pm10->set_object_id("pm___10_0__m");
  pmsx003_pm10->set_disabled_by_default(false);
  pmsx003_pm10->set_icon("mdi:chemical-weapon");
  pmsx003_pm10->set_device_class("pm10");
  pmsx003_pm10->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  pmsx003_pm10->set_unit_of_measurement("\302\265g/m\302\263");
  pmsx003_pm10->set_accuracy_decimals(0);
  pmsx003_pm10->set_force_update(false);
  pmsx003_pmsx003component->set_pm_10_0_sensor(pmsx003_pm10);
  pmsx003_pmsx003component->set_update_interval(0);
  // text_sensor.bme680_bsec:
  //   platform: bme680_bsec
  //   iaq_accuracy:
  //     name: BME680 IAQ Accuracy
  //     internal: true
  //     disabled_by_default: false
  //     id: text_sensor_textsensor
  //     icon: mdi:checkbox-marked-circle-outline
  //   bme680_bsec_id: bme680_bsec_bme680bseccomponent
  text_sensor_textsensor = new text_sensor::TextSensor();
  App.register_text_sensor(text_sensor_textsensor);
  text_sensor_textsensor->set_name("BME680 IAQ Accuracy");
  text_sensor_textsensor->set_object_id("bme680_iaq_accuracy");
  text_sensor_textsensor->set_disabled_by_default(false);
  text_sensor_textsensor->set_internal(true);
  text_sensor_textsensor->set_icon("mdi:checkbox-marked-circle-outline");
  bme680_bsec_bme680bseccomponent->set_iaq_accuracy_text_sensor(text_sensor_textsensor);
  // text_sensor.template:
  //   platform: template
  //   name: BME680 IAQ Classification
  //   id: iaq_classification
  //   icon: mdi:checkbox-marked-circle-outline
  //   lambda: !lambda |-
  //     if ( int(id(iaq).state) <= 50) {
  //       return {"Excellent"};
  //     }
  //     else if (int(id(iaq).state) >= 51 && int(id(iaq).state) <= 100) {
  //       return {"Good"};
  //     }
  //     else if (int(id(iaq).state) >= 101 && int(id(iaq).state) <= 150) {
  //       return {"Lightly polluted"};
  //     }
  //     else if (int(id(iaq).state) >= 151 && int(id(iaq).state) <= 200) {
  //       return {"Moderately polluted"};
  //     }
  //     else if (int(id(iaq).state) >= 201 && int(id(iaq).state) <= 250) {
  //       return {"Heavily polluted"};
  //     }
  //     else if (int(id(iaq).state) >= 251 && int(id(iaq).state) <= 350) {
  //       return {"Severely polluted"};
  //     }
  //     else if (int(id(iaq).state) >= 351) {
  //       return {"Extremely polluted"};
  //     }
  //     else {
  //       return {"Error"};
  //     }
  //   disabled_by_default: false
  //   update_interval: 60s
  iaq_classification = new template_::TemplateTextSensor();
  App.register_text_sensor(iaq_classification);
  iaq_classification->set_name("BME680 IAQ Classification");
  iaq_classification->set_object_id("bme680_iaq_classification");
  iaq_classification->set_disabled_by_default(false);
  iaq_classification->set_icon("mdi:checkbox-marked-circle-outline");
  iaq_classification->set_update_interval(60000);
  iaq_classification->set_component_source("template.text_sensor");
  App.register_component(iaq_classification);
  iaq_classification->set_template([=]() -> optional<std::string> {
      #line 381 "config.yml"
      if ( int(iaq->state) <= 50) {
        return {"Excellent"};
      }
      else if (int(iaq->state) >= 51 && int(iaq->state) <= 100) {
        return {"Good"};
      }
      else if (int(iaq->state) >= 101 && int(iaq->state) <= 150) {
        return {"Lightly polluted"};
      }
      else if (int(iaq->state) >= 151 && int(iaq->state) <= 200) {
        return {"Moderately polluted"};
      }
      else if (int(iaq->state) >= 201 && int(iaq->state) <= 250) {
        return {"Heavily polluted"};
      }
      else if (int(iaq->state) >= 251 && int(iaq->state) <= 350) {
        return {"Severely polluted"};
      }
      else if (int(iaq->state) >= 351) {
        return {"Extremely polluted"};
      }
      else {
        return {"Error"};
      }
  });
  // output:
  // output.gpio:
  //   platform: gpio
  //   id: statusLED
  //   pin:
  //     number: 27
  //     mode:
  //       output: true
  //       input: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_10
  //     inverted: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  statusLED = new gpio::GPIOBinaryOutput();
  statusLED->set_component_source("gpio.output");
  App.register_component(statusLED);
  esp32_esp32internalgpiopin_10 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_10->set_pin(::GPIO_NUM_27);
  esp32_esp32internalgpiopin_10->set_inverted(false);
  esp32_esp32internalgpiopin_10->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_10->set_flags(gpio::Flags::FLAG_OUTPUT);
  statusLED->set_pin(esp32_esp32internalgpiopin_10);
  // time.homeassistant:
  //   platform: homeassistant
  //   id: esptime
  //   timezone: CET-1CEST,M3.5.0,M10.5.0/3
  //   update_interval: 15min
  esptime = new homeassistant::HomeassistantTime();
  esptime->set_timezone("CET-1CEST,M3.5.0,M10.5.0/3");
  esptime->set_update_interval(900000);
  esptime->set_component_source("homeassistant.time");
  App.register_component(esptime);
  // interval:
  //   - interval: 120s
  //     then:
  //     - switch.turn_on:
  //         id: pms_set
  //       type_id: switch__turnonaction
  //     - delay: 20s
  //       type_id: delayaction
  //     - switch.turn_off:
  //         id: pms_set
  //       type_id: switch__turnoffaction
  //     trigger_id: trigger
  //     automation_id: automation_3
  //     id: interval_intervaltrigger
  //     startup_delay: 0s
  //   - interval: 1000ms
  //     then:
  //     - output.turn_on:
  //         id: statusLED
  //       type_id: output_turnonaction
  //     - delay: 500ms
  //       type_id: delayaction_2
  //     - output.turn_off:
  //         id: statusLED
  //       type_id: output_turnoffaction
  //     trigger_id: trigger_2
  //     automation_id: automation_4
  //     id: interval_intervaltrigger_2
  //     startup_delay: 0s
  interval_intervaltrigger = new interval::IntervalTrigger();
  interval_intervaltrigger->set_component_source("interval");
  App.register_component(interval_intervaltrigger);
  automation_3 = new Automation<>(interval_intervaltrigger);
  switch__turnonaction = new switch_::TurnOnAction<>(pms_set);
  delayaction = new DelayAction<>();
  delayaction->set_component_source("interval");
  App.register_component(delayaction);
  delayaction->set_delay(20000);
  switch__turnoffaction = new switch_::TurnOffAction<>(pms_set);
  automation_3->add_actions({switch__turnonaction, delayaction, switch__turnoffaction});
  interval_intervaltrigger->set_update_interval(120000);
  interval_intervaltrigger->set_startup_delay(0);
  interval_intervaltrigger_2 = new interval::IntervalTrigger();
  interval_intervaltrigger_2->set_component_source("interval");
  App.register_component(interval_intervaltrigger_2);
  automation_4 = new Automation<>(interval_intervaltrigger_2);
  output_turnonaction = new output::TurnOnAction<>(statusLED);
  delayaction_2 = new DelayAction<>();
  delayaction_2->set_component_source("interval");
  App.register_component(delayaction_2);
  delayaction_2->set_delay(500);
  output_turnoffaction = new output::TurnOffAction<>(statusLED);
  automation_4->add_actions({output_turnonaction, delayaction_2, output_turnoffaction});
  interval_intervaltrigger_2->set_update_interval(1000);
  interval_intervaltrigger_2->set_startup_delay(0);
  // socket:
  //   implementation: bsd_sockets
  // network:
  //   enable_ipv6: false
  aqmonitor->set_clock(esptime);
  aqmonitor->set_network(esp_wifi);
  aqmonitor->set_sensor_co2(scd4x_co2);
  aqmonitor->set_sensor_power(current_power);
  aqmonitor->set_sensor_pm_2_5(pmsx003_pm01);
  aqmonitor->set_sensor_pm_2_5(pmsx003_pm25);
  aqmonitor->set_sensor_pm_10(pmsx003_pm10);
  aqmonitor->set_sensor_rh(bme680_humidity);
  aqmonitor->set_sensor_temp(bme680_temperature);
  aqmonitor->set_sensor_voc(bvoc);
  aqmonitor->set_pm_2_5_levels({12, 35, 55, 150, 250});
  aqmonitor->set_pm_2_5_levels({12, 35, 55, 150, 250});
  aqmonitor->set_pm_10_levels({54, 154, 254, 354, 424});
  aqmonitor->set_voc_levels({15, 25, 50, 75, 100});
  aqmonitor->set_co2_levels({650, 1500, 2000, 2500, 5000});
  aqmonitor->set_sensor_voc(bvoc);
  // =========== AUTO GENERATED CODE END ============
  App.setup();
}

void loop() {
  App.loop();
}
