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

  busvoltage = ina219.getBusVoltage_V();
  shuntvoltage = ina219.getShuntVoltage_mV();
  current_mA = ina219.getCurrent_mA();
  buspower_mW = ina219.getBusPower_mW();
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println("\tV");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println("\tmV");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println("\tmA");
  Serial.print("Bus Power:     "); Serial.print(buspower_mW); Serial.println("\tmW");
  Serial.println("");

  delay(2000);
}
