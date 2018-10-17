/*  The difference with getcurrent example is that 
 *  INA219 will not be constantly measuring values but only when triggered by calling the configuration function
 *  hence it will be measuring for 69 ms every 2 seconds (delay(200) + delay(1800) in this example)
 *  During the 1800 ms timelap the INA219 is put to power dowm using enterPowerSave()
 *  It would be particularly helpfull if you put the MCU in sleep mode during this period so both MCU and INA219 would consumme close to 0.
 */

#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;


void setup(void) 
{
  Serial.begin(115200);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }

  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  ina219.begin();

  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  // Configuring the INA (in trigger mode) will trigger measurement. Use the appropriate calibration function
  ina219.setCalibration_32V_2A(true);
  //ina219.setCalibration_32V_1A(true);
  //ina219.setCalibration_16V_400mA(true); 

  // Some time to do the measurement (more than 69 ms)
  delay(200);

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");  

  // Now INA219 is sleeping, using a couple of uA instead of 1mA
  ina219.enterPowerSave(); 
  delay(1800);
}
