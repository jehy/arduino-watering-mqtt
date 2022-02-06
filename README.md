# Arduino auto watering with MQQT

[![Compile Sketch](https://github.com/jehy/arduino-watering-mqtt/actions/workflows/compile-sketch.yaml/badge.svg)](https://github.com/jehy/arduino-came-reader/actions/workflows/compile-sketch.yaml)
[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.me/jehyrus)

Simple dryness (humidity) sensor with self watering via 12v pump and MQQT for reporting.

Needs a pump, ground humidity sensor and relay.

Sample config for Home Assistant:

```yaml
binary_sensor:
  - platform: mqtt
  unique_id: esp-water-1
  name: "ESP water 1"
  state_topic: "esp/water/1/state"
  payload_on: "1"
  payload_off: "0"
  device_class: "running"
  qos: 0

sensor:
  - platform: mqtt
    unique_id: esp-water-1
    name: "ESP water 1 status"
    state_topic: "esp/water/1/status"
    qos: 0
    unit_of_measurement: "ue"
```
