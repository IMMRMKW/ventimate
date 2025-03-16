# Ventimate
An esphome configuration that turns your [HA Mate](https://immrmkw.github.io/HA_Mate/) in an airpurifier.

## How to install
There are several methods to install ESPHome on your board. If you have Home Assistant with the ESPHome Device Builder addon already installed, [this](#install-using-home-assistant) may be the easiest option for you. If you are already acquinted with Python, uploading a configuration [this way](#install-using-python-and-esphome) is fairly easy as well. In all cases, [add the ESPHome integration](https://www.home-assistant.io/integrations/esphome/) to Home Assistant.
### Install using Home Assistant
- Connect the HA Mate to your laptop/computer using a USB cable.
- Go to [web.esphome.io](https://web.esphome.io/).
- Click *connect*
- Select the correct COM-port. Hint: the port will probably be named something like *USB JTAG/serial debug unit (COM1)*. Where the *1* can be any number depending on the number of similar devices you used in the past.
- Click *Prepare for first use*
- Follow the steps on the screen. If after the installation, the following error appears, `An error occured. Improv Wi-Fi Serial not detected`, press the reset button on your HA Mate, and restart the procedure.
- Click *Connect to Wi-Fi*, and enter your credentials.
- Now open the *ESPHome Device Builder* addon, or ESPHome builder for short, on your Home Assistant page.
- If everything went correctly, ESPHome builder automatically detected a new device connected to the network. This is indicated on the top of the screen. Click *Show*.
- A new ESPHome device will appear in the screen. Click *Take control*.
- Do not give your ESPHome device a new name. Just click *Take Control* again.
- In the next step, click *Skip*.
- Then click *Close*.
- Now the panel of your ESPHome device has a new button named *EDIT*. Click it. A new window with YAML code for your ESPHome configuration appears.
- Copy-paste the YAML code of the file `config_ESP32_S3.yml` to this window. Click 'Save'.
- Now, you should ensure that the credentials of your wifi and your Home Assistant API key are known to your configuration. There are two options for this:
    1. You can use the file editor addon. If you do not have it, you can [install it](https://www.home-assistant.io/common-tasks/os/#:~:text=To%20install%20and%20use%20the%20File%20Editor%20in%20Home%20Assistant,files%20within%20your%20%2Fconfig%20directory.). Your Home Assistant folder will have a file called *secrets.yaml*. Copy-paste the contents of the *secrets_example.yml* to *secrets.yaml* on your Home Assistant. Replace the wifi_ssid and wifi_password strings with the credentials that apply for your wifi. You can generate a Home Assistant Api key [here](https://esphome.io/components/api.html) (the site randomly generates a key upon accessing or refreshing the site). The access point credentials you can decide upon yourself.
    2. Simply type your credentials and API key in the configuration file:
    ```
    api:
      encryption:
      key: "your key"

    wifi:
      id: esp_wifi
      ssid: "your_wifi_ssid"
      password: "your_wifi_password"
    ```
- Go back to ESPHome builder and click *UPDATE*


### Install using Python and ESPhome
This method requires you to have installed [Python](https://www.python.org/downloads/) and [git](https://git-scm.com/downloads)
- Navigate to the folder where you want to clone the project.
- In this folder, open a terminal.
- Type `git clone git@github.com:IMMRMKW/ventimate.git`
- Still using the terminal, navigate to the folder containing the cloned project.
- In this folder, create a virtual environment by using `python -m venv`.
- Start the virtual environment using `.\.venv\Scripts\activate`
- Install ESPHome using `pip install esphome`
- Connect the HA Mate to your laptop/computer using a USB cable.
- Note down the number of the COM port that is assigned to the HA Mate.
- In the *ventimate* folder, create a file called *secrets.yml*. Copy-paste the contents of *secrets_example.yml* to the new file. Replace the wifi_ssid and wifi_password strings with the credentials that apply for your wifi. You can generate a Home Assistant Api key [here](https://esphome.io/components/api.html) (the site randomly generates a key upon accessing or refreshing the site). The access point credentials you can decide upon yourself.
- In your terminal, type `esphome run config_ESP32_S3.yml --device COM<number>`. Replace <number> with the number that is assigned to the COM port of your HA Mate. Press Enter.

The configuration should now be compiled an be uploaded to your HA Mate.