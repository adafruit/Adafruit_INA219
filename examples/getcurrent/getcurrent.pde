#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup(void) 
{
  uint32_t currentFrequency;
    
  Serial.begin(115200);
  Serial.println("Hello!");
  
  Serial.print("Measuring voltage and current with INA219 ...");
  ina219.begin();
}

void loop(void) 
{
  int16_t current_mA = 0;
  int16_t busvoltage = 0;
  int16_t shuntvoltage = 0;
  int16_t loadvoltage = 0;
  
  shuntvoltage = ina219.getShuntVoltage();
  busvoltage = ina219.getBusVoltage();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 100);
  
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage/100); Serial.print('.'); Serial.print(shuntvoltage%100); Serial.println("V");
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage/1000); Serial.print('.'); Serial.print(busvoltage%1000); Serial.println("V");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage/1000); Serial.print('.'); Serial.print(loadvoltage%1000); Serial.println("V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println("mA");
  Serial.println("");

  delay(2000);
}
