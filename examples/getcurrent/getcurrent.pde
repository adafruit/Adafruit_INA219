#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

float shuntvoltage = 0.0;
float busvoltage = 0.0;
float current_mA = 0.0;
float loadvoltage = 0.0;
float buspower_mW = 0.0;

void setup(void) 
{
  uint32_t currentFrequency;
    
  Serial.begin(115200);
  Serial.println("Hello!");
  Serial.println("Measuring voltage, current and power with INA219 ...");

  ina219.begin();
}

void loop(void) 
{

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  buspower_mW = ina219.getBusPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Bus Power:     "); Serial.print(buspower_mW); Serial.println(" mW");
  Serial.println("");

  delay(2000);
}
