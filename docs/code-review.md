# Code review

The project sketch uses placeholders for the Blynk token, template ID, Wi-Fi SSID and Wi-Fi password. Formatting and comments were cleaned up; executable sensor and communication logic was retained.

## Findings to resolve before reuse

- The Blynk template definitions occur after the Blynk include. Check the required placement for the selected Blynk library version when preparing a runnable revision.
- The loop contains no `Blynk.run()` call and contains three one-second delays. A maintained revision should service the Blynk connection and schedule readings without these long blocking intervals.
- The MQ135 constructor uses the label `Arduino UNO` and a 5 V voltage resolution even though the application uses ESP8266 libraries. Confirm the actual board, A0 input range, MQ135 supply and any divider before changing this configuration or connecting a sensor.
- The bare ESP8266 ADC range is 0-1 V; development boards may include a divider. Do not infer the board's A0 range from the chip family alone. See the [ESP8266 core reference](https://arduino-esp8266.readthedocs.io/en/latest/reference.html#analog-input).
- The sketch fits several gas curves to the same MQ135 reading and adds 400 to its CO2 model output. These are algorithmic estimates, not evidence of gas-selective measurement or reference calibration. Original labels such as `NH4` and `C02` are retained in the archived code.
- The declared `temperature` and `humidity` constants are unused; the actual transmitted temperature and humidity come from DHT reads.
- BMP SPI pin macros are unused: `Adafruit_BMP280 bmp` uses I2C. They should not be treated as a wiring diagram.
- DHT read failures are not filtered before publication. Startup MQ calibration takes ten immediate samples; warm-up and calibration conditions require confirmation.

