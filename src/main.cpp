/**
 * I, Noah Tomkins, 0000790079 certify that this material is my original work.
 * No other person's work has been used without due acknowledgement.
 */

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = D3;
OneWire oneWire(oneWireBus);
DallasTemperature DS18B20(&oneWire);
DeviceAddress Thermometer;

bool connected = false;

String getTempString(double temp) {
    if (temp < 10)
        return "Cold!";
    if (temp < 15)
        return "Cool";
    if (temp < 25)
        return "Perfect";
    if (temp < 30)
        return "Warm";
    if (temp < 35)
        return "Hot";
    else
        return "Too Hot!";
}

String getAddressString(DeviceAddress deviceAddress)
{ 
    String addr = "";

    for (uint8_t i = 0; i < 8; i++)
    {
        addr += "0x";
        if (deviceAddress[i] < 0x10) Serial.print("0");
        addr += String(deviceAddress[i], HEX);
    }
   
    return addr;
}

bool checkConnected() {
    DS18B20.getAddress(Thermometer, 0);

    if (!DS18B20.isConnected(Thermometer)) {
        Serial.println("No DS18B20 temperature sensors are installed!");
        return false;
    }

    DS18B20.getAddress(Thermometer, 0);
    Serial.println("Found DS18B20 sensor with address: " + getAddressString(Thermometer));

    return true;
}

void setup() {
    Serial.begin(115200);

    DS18B20.begin();

    Serial.print("\n\n\nTemperature Application\n");
    checkConnected();
}

void loop() {
    DS18B20.getAddress(Thermometer, 0);
    if (DS18B20.isConnected(Thermometer)) {
        float fTemp;

        DS18B20.requestTemperatures();
        fTemp = DS18B20.getTempCByIndex(0);

        Serial.println("Current temp: " + String(fTemp) + "°C or " + getTempString(fTemp));
    }
    delay(5000);
}
