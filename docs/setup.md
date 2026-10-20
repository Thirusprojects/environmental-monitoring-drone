# Sensor and dashboard setup reference

This reference records the sensor sketch's interface. Complete the code-review items before attempting hardware reuse.

## Dependencies

Use an ESP8266-compatible Arduino environment with:

- ESP8266 Arduino core (`ESP8266WiFi`, `Wire`, `SPI`, and `ESP8266HTTPClient`).
- Blynk library (`BlynkSimpleEsp8266`).
- Adafruit DHT sensor library and its Adafruit Unified Sensor dependency.
- Adafruit BMP280 library and its dependencies.
- MQUnifiedsensor library.

Select the exact ESP8266 development-board model used by the hardware. The project archive does not pin new dependency versions or claim a verified build with current libraries.

## Connections encoded in the sketch

| Signal | Code configuration |
|---|---|
| DHT22 data | GPIO14 |
| BMP280 | I2C, address 0x76; default board/core I2C pins |
| MQ135 analog signal | A0; verify input range and divider before connecting |
| Serial diagnostics | 9600 baud |

Supply voltages, level shifting, common grounding and sensor-module pinouts must follow the actual modules. Do not treat this table as a complete electrical schematic.

## Blynk configuration

1. Create a Blynk device/template for the ESP8266 and Wi-Fi connection.
2. Create numeric datastreams V0 (temperature, degrees Celsius), V1 (relative humidity, percent), V2 (pressure, bar).
3. Create string datastreams V3 and V4 for the archived gas-model text output.
4. Add numeric displays/gauges and text displays mapped to these pins.
5. Use a new device token and your own network credentials in a private local configuration. Never commit actual credentials.
6. Open the sketch whose folder and filename are both `original_environment_monitor`, resolve the review findings, and verify compilation for the selected board before uploading a revised copy.

The Blynk Wi-Fi data path is separate from manual flight control. Mission Planner was used for the aircraft setup; this sensor sketch does not control the flight controller.
