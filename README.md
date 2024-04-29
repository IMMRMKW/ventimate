# my_component1
## Todo
* Create a platform component for power delivery
	- For now, it should only have sink capability, with multiple voltage setpoints
	- Create a sensor such that actual voltage is available within your ESPHome configuration
	- The FUSB302, __init__.py should be empty, code should be moved to power_delivery.py
	- Ensure the priority of FUSB302 is set automatically if it is not explicitly set in the configuration yaml file.
* Create a complete yaml configuration that shows the working of the project
	- Find out how to discard the name of the ESPHome device in front of each sensor. This clutters the Home assistant view
* Find out how to use ESPHome stand alone
	- Create a tutorial on how to do this
* Change name of MyFan
	- Think of something!
* Change name of this project
* Update gitignore file
* Create gauge card configuration for all sensor values using the AQI class for color limits and the current sensor values for the current readout.

## Uploading this project to your esp32
### Manually, using, e.g., VSCode
* Create a project folder in VSCode to which you clone this github project.
* Next, using the terminal, create a virtual environment in this folder:
```bash
python -m venv .venv
```
* Activate your virtual environment using:
``` bash
 .\.venv\Scripts\activate
```
* First, install wheel:
``` bash
pip install wheel 
```
* Next, install esphome:
``` bash
pip install esphome 
```
*You can upload the code using:
``` bash
esphome run config.yml --device COM1
```
Where the '1' behind 'COM' should be replaced by the actual COM port number of your device.

### Via Home Assistant
### Via your browser
https://web.esphome.io/
### Locally via USB
## Inserting fan art (pun intended) in your fan
Insert explanation of how to include fan art

