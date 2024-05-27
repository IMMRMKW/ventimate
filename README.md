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

## Aquality index
There are loads of different air quality indexes (see, [Wikipedia](https://en.wikipedia.org/wiki/Air_quality_index#)).
[this paper](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC8876806/) has a measure for safe levels of VOCs.



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
* You can upload the code using:
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
## Creating gauge cards indicating air quality index
[converting 16 bit colors to 24 bit colors]{https://stackoverflow.com/questions/2442576/how-does-one-convert-16-bit-rgb565-to-24-bit-rgb888} and [vice versa]{https://greekgeeks.net/#maker-tools_convertColor}

```yaml
type: gauge
entity: sensor.esphome_web_79a218_pm_2_5_m
needle: true
min: 0
max: 300
segments:
  - from: 0
    color: '#009600'
  - from: 12
    color: '#8CC600'
  - from: 35
    color: '#FFEF00'
  - from: 55
    color: '#FFB200'
  - from: 150
    color: '#F79600'
  - from: 250
    color: '#FF0000'
```

