## Description

These scripts are designed to interface with the plugin to expose the web-based valve. One script is a simple on/off switch (for taps, showers etc.) whereas the other modulates on/off and is useful for more niche cases like outdoor misting systems.

## Requirements

* NodeMCU

* Relay

* Micro-USB cable

## How-to

1. First, install the `ArduinoJson` library from the _Library manager_ in the Arduino IDE, then follow [this](https://gist.github.com/phenotypic/8d9d3b886936ccea9c21f495755640dd) gist which walks you through how to flash a NodeMCU.

2. Connect the NodeMCU to the relay board

3. Assuming that you already have [homebridge](https://github.com/homebridge/homebridge#installation) set up, the next thing you will have to do is install the plugin:
```
npm install -g homebridge-web-valve
```

4. Finally, update your `config.json` file following the example below:

```json
"accessories": [
     {
       "accessory": "WebValve",
       "name": "Valve",
       "apiroute": "http://valve.local"
     }
]
```

## Wiring

| NodeMCU | Relay Module |
| --- | --- |
| `3V3` | `VCC` |
| `GND` | `GND` |
| `D7` | `IN1` |
