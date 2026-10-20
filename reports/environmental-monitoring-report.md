# Environmental Monitoring Hexacopter

**Portfolio report - revised scope**  
**Thiruppathi P**

This report covers the hexacopter build, environmental sensing payload, Blynk dashboard and flight testing.

## Purpose

Build an airborne environmental sensing platform that combines manual hexacopter flight with a remote Blynk dashboard. The payload acquires temperature, humidity, atmospheric pressure and an experimental MQ135 gas response.

## Aircraft

The aircraft uses an APM 2.8 flight controller, six 1000 KV brushless motors, 10-inch propellers, 30 A ESCs, a 5200 mAh 3S LiPo battery and a FlySky FS-i6 radio system. I used Mission Planner for setup and flew the aircraft manually.

![Assembled aircraft](../media/photos/build.jpg)

## Sensing and communication

An ESP8266 reads a DHT22 on GPIO14, a BMP280 at I2C address 0x76 and an MQ135 through A0, as configured in the sensor sketch. Temperature and humidity readings are transmitted directly; pressure in pascals is divided by 100000 to display bar. The MQ135 reading is processed with multiple regression coefficient pairs to generate experimental gas-model outputs.

The ESP8266 transmits readings over Wi-Fi to Blynk. V0, V1 and V2 carry temperature, humidity and pressure. V3 and V4 carry text strings from the gas-model calculations. Readings reached the dashboard during flight.

## My contribution

I handled drone assembly, wiring, flight setup, sensor programming, Blynk dashboard configuration and CAD work. The archive contains seven CAD screenshots and three photographs of the physical aircraft.

## Demonstrated outcome

The aircraft was assembled and flown manually, with environmental readings transmitted to Blynk during flight. The source sketch and media document the implementation. Gas-model outputs are presented as experimental estimates rather than independently validated concentrations.

## Implementation references

- [Sanitized source sketch](../firmware/original_environment_monitor/original_environment_monitor.ino)
- [Source review](../docs/code-review.md)
- [Dashboard and connection reference](../docs/setup.md)
- [CAD gallery](../docs/cad-gallery.md)

Student registration numbers and personal contact details are excluded from this edited report.
