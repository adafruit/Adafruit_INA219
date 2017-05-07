#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

#define R_SHUNT 0.00375
#define V_SHUNT_MAX 0.075
#define V_BUS_MAX 16
#define I_MAX_EXPECTED 20

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.println("Hello - Adafruit_INA219!");

  ina219.begin();
  // Sets user defined calibration
  ina219.setCalibration_Def(R_SHUNT, V_SHUNT_MAX, V_BUS_MAX, I_MAX_EXPECTED);
}

void loop() {
  // put your main code here, to run repeatedly:
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float batvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  batvoltage = busvoltage + (shuntvoltage / 1000);

  Serial.print("Bus Voltage (V-) : "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage :    "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Bat Voltage (V+) : "); Serial.print(batvoltage); Serial.println(" V");
  Serial.print("Current:           "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:             "); Serial.print(power_mW); Serial.println(" mW");

  Serial.println("");

  delay(500);
}
