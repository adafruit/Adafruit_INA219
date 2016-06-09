#include <Wire.h>
#include <Adafruit_INA219.h>

//#define _CHIBIOS_RT_

#ifdef _CHIBIOS_RT_
 #include "ChibiOS_ARM.h"
#endif

#ifndef _CHIBIOS_RT_  

//Adafruit_INA219 ina219; // using Wire  
Adafruit_INA219 ina219(INA219_ADDRESS,Wire1); // using Wire1

#else // using ChibiOS
// using another 1 msec delay funtion
// concretely the one used with ChibiOS
// in project A-Tirma
//Adafruit_INA219 ina219(
//  INA219_ADDRESS, // INA219's I2C address
//  Wire, // using the second I2C device on the DUE
//  //using a specific ChibiOS function for the
//  // 1 msec delay necessary using when reading
//  // the INA219
//  [](void) { chThdSleepMilliseconds(1); }
//); // using Wire
Adafruit_INA219 ina219(
  INA219_ADDRESS, // INA219's I2C address
  Wire1, // using the second I2C device on the DUE
  //using a specific ChibiOS function for the
  // 1 msec delay necessary using when reading
  // the INA219
  [](void) { chThdSleepMilliseconds(1); }
); // using Wire1
#endif

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

void setup(void) 
{
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  uint32_t currentFrequency;
    
  Serial.begin(115200);
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  ina219.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.println("");

  delay(2000);
}
