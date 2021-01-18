# ESP32 DHT22 MHZ19 MQTT

This project is about reading dht22 and mhz19 sensor values and submit the sensor values to a mqtt broker.

# ESP32

In this project I am using an ESP-32S NodeMCU with a V1.1 pinout.

For an overview of the pin out, please check the following link: http://wei48221.blogspot.com/2017/11/esp32-working-with-nodemcu-board.html

Next to the 5V pin there is the FLASHCMD, which can be easily mistaken with a GND pin as on the pinout itself, the FLASHCMD is written CMD in small latters, which looks almost similar to GND.

Furthermore, the following blog post did give me a hint regarding the wiring of the MH-Z19B sensor with ESP-32.

https://shopofthings.ch/blog/2020/04/23/esp32-hardware-serial-neu-zuordnen/

# DHT-22

The sensor DHT-22 senses air temperature and humidity. The sensor consumes a voltage of 3.3 V. The adafruit DHT sensor library is probably the most popoular library for an Arudiono project integration out there:

https://github.com/adafruit/DHT-sensor-library

For downloading the data sheet, please refer to the following link: https://cdn.shopify.com/s/files/1/1509/1638/files/DHT_22_-_AM2302_Temperatur_und_Luftfeuchtigkeitssensor_Datenblatt.pdf?11983326290748777409

# MH-Z19B

The sensor MH-Z19B senses carbon dioxid (CO2). The sensor consumes a voltage of 4.5 to 5.5 V. The output is either serial or pwm. Several github repositories providd Arduino libraries to integrate the MH-Z19 or MH-Z19B sensor into an Arduino project: 

https://github.com/WifWaf/MH-Z19

https://github.com/crisap94/MHZ19

https://github.com/strange-v/MHZ19

For downloading the data sheet, please refer to the following link: https://cdn-reichelt.de/documents/datenblatt/X200/MH-Z19B_DB_EN.pdf.
