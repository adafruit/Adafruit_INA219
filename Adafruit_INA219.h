/**************************************************************************/
/*! 
    @file     Adafruit_INA219.h
    @author   K. Townsend (Adafruit Industries)
	@license  BSD (see license.txt)
	
	This is a library for the Adafruit INA219 breakout board
	----> https://www.adafruit.com/products/???
	
	Adafruit invests time and resources providing this open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

	@section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define INA219_ADDRESS                          (0x40)    // 1000000 (A0+A1=GND)
    #define INA219_READ                             (0x01)
/*=========================================================================*/

/*=========================================================================
    CONFIG REGISTER (R/W)
    -----------------------------------------------------------------------*/
    #define INA219_REG_CONFIG                       (0x00)
    /*---------------------------------------------------------------------*/
    #define INA219_CONFIG_RESET                     (0x8000)  // Reset Bit
	
    #define INA219_CONFIG_BVOLTAGERANGE_MASK        (0x2000)  // Bus Voltage Range Mask
    #define INA219_CONFIG_BVOLTAGERANGE_16V         (0x0000)  // 0-16V Range
    #define INA219_CONFIG_BVOLTAGERANGE_32V         (0x2000)  // 0-32V Range (power-on default)
	
    #define INA219_CONFIG_GAIN_MASK                 (0x1800)  // Gain Mask
    #define INA219_CONFIG_GAIN_1_40MV               (0x0000)  // Gain 1, 40mV Range
    #define INA219_CONFIG_GAIN_2_80MV               (0x0800)  // Gain 2, 80mV Range
    #define INA219_CONFIG_GAIN_4_160MV              (0x1000)  // Gain 4, 160mV Range
    #define INA219_CONFIG_GAIN_8_320MV              (0x1800)  // Gain 8, 320mV Range (power-on default)
	
    #define INA219_CONFIG_BADCRES_MASK              (0x0780)  // Bus ADC Resolution and Averaging Mask
    #define INA219_CONFIG_BADCRES_9BIT              (0x0080)  // 1 x 9-bit bus sample
    #define INA219_CONFIG_BADCRES_10BIT             (0x0100)  // 1 x 10-bit bus sample
    #define INA219_CONFIG_BADCRES_11BIT             (0x0200)  // 1 x 11-bit bus sample
    #define INA219_CONFIG_BADCRES_12BIT             (0x0180)  // 1 x 12-bit bus sample (power-on default)
    #define INA219_CONFIG_BADCRES_12BIT_1S_532US    (0x0400)  // 1 x 12-bit bus sample
    #define INA219_CONFIG_BADCRES_12BIT_2S_1060US   (0x0480)  // 2 x 12-bit bus samples averaged together
    #define INA219_CONFIG_BADCRES_12BIT_4S_2130US   (0x0500)  // 4 x 12-bit bus samples averaged together
    #define INA219_CONFIG_BADCRES_12BIT_8S_4260US   (0x0580)  // 8 x 12-bit bus samples averaged together
    #define INA219_CONFIG_BADCRES_12BIT_16S_8510US  (0x0600)  // 16 x 12-bit bus samples averaged together
    #define INA219_CONFIG_BADCRES_12BIT_32S_17MS    (0x0680)  // 32 x 12-bit bus samples averaged together
    #define INA219_CONFIG_BADCRES_12BIT_64S_34MS    (0x0700)  // 64 x 12-bit bus samples averaged together
    #define INA219_CONFIG_BADCRES_12BIT_128S_69MS   (0x0780)  // 128 x 12-bit bus samples averaged together
    
    #define INA219_CONFIG_SADCRES_MASK              (0x0078)  // Shunt ADC Resolution and Averaging Mask
    #define INA219_CONFIG_SADCRES_9BIT              (0x0000)  // 1 x 9-bit shunt sample
    #define INA219_CONFIG_SADCRES_10BIT             (0x0008)  // 1 x 10-bit shunt sample
    #define INA219_CONFIG_SADCRES_11BIT             (0x0010)  // 1 x 11-bit shunt sample
    #define INA219_CONFIG_SADCRES_12BIT             (0x0018)  // 1 x 12-bit shunt sample (power-on default)
    #define INA219_CONFIG_SADCRES_12BIT_1S_532US    (0x0040)  // 1 x 12-bit shunt sample
    #define INA219_CONFIG_SADCRES_12BIT_2S_1060US   (0x0048)  // 2 x 12-bit shunt samples averaged together
    #define INA219_CONFIG_SADCRES_12BIT_4S_2130US   (0x0050)  // 4 x 12-bit shunt samples averaged together
    #define INA219_CONFIG_SADCRES_12BIT_8S_4260US   (0x0058)  // 8 x 12-bit shunt samples averaged together
    #define INA219_CONFIG_SADCRES_12BIT_16S_8510US  (0x0060)  // 16 x 12-bit shunt samples averaged together
    #define INA219_CONFIG_SADCRES_12BIT_32S_17MS    (0x0068)  // 32 x 12-bit shunt samples averaged together
    #define INA219_CONFIG_SADCRES_12BIT_64S_34MS    (0x0070)  // 64 x 12-bit shunt samples averaged together
    #define INA219_CONFIG_SADCRES_12BIT_128S_69MS   (0x0078)  // 128 x 12-bit shunt samples averaged together
	
    #define INA219_CONFIG_MODE_MASK                 (0x0007)  // Operating Mode Mask
    #define INA219_CONFIG_MODE_POWERDOWN            (0x0000)
    #define INA219_CONFIG_MODE_SVOLT_TRIGGERED      (0x0001)
    #define INA219_CONFIG_MODE_BVOLT_TRIGGERED      (0x0002)
    #define INA219_CONFIG_MODE_SANDBVOLT_TRIGGERED  (0x0003)
    #define INA219_CONFIG_MODE_ADCOFF               (0x0004)
    #define INA219_CONFIG_MODE_SVOLT_CONTINUOUS     (0x0005)
    #define INA219_CONFIG_MODE_BVOLT_CONTINUOUS     (0x0006)
    #define INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS (0x0007)  // (power-on default)
/*=========================================================================*/

/*=========================================================================
    SHUNT VOLTAGE REGISTER (R)
    -----------------------------------------------------------------------*/
    #define INA219_REG_SHUNTVOLTAGE                 (0x01)
/*=========================================================================*/

/*=========================================================================
    BUS VOLTAGE REGISTER (R)
    -----------------------------------------------------------------------*/
    #define INA219_REG_BUSVOLTAGE                   (0x02)
/*=========================================================================*/

/*=========================================================================
    POWER REGISTER (R)
    -----------------------------------------------------------------------*/
    #define INA219_REG_POWER                        (0x03)
/*=========================================================================*/

/*=========================================================================
    CURRENT REGISTER (R)
    -----------------------------------------------------------------------*/
    #define INA219_REG_CURRENT                      (0x04)
/*=========================================================================*/

/*=========================================================================
    CALIBRATION REGISTER (R/W)
    -----------------------------------------------------------------------*/
    #define INA219_REG_CALIBRATION                  (0x05)
/*=========================================================================*/

class Adafruit_INA219{
 public:
  Adafruit_INA219(uint8_t addr = INA219_ADDRESS);
  void begin(void);
  float getBusVoltage_V(void);
  float getShuntVoltage_mV(void);
  float getCurrent_mA(void);
  float getBusPower_mW(void);

 private:
  uint8_t ina219_i2caddr;
  uint32_t ina219_calValue;
  // The following multipliers are used to convert raw voltage, current and
  // power bit values to mV, uV, uA and uW, taking into account the current
  // config settings. Then they are converted to the final units.
  // We only do floating point math at the very last step in each function 
  // to limit performance impact.
  uint32_t ina219_shuntVoltageMultiplier_uV;
  uint32_t ina219_currentMultiplier_uA;
  uint32_t ina219_busVoltageMultiplier_mV;
  uint32_t ina219_busPowerMultiplier_uW;

  
  void wireWriteRegister(uint8_t reg, uint16_t value);
  void wireReadRegister(uint8_t reg, uint16_t *value);
  void ina219SetCalibration_32V_2A(void);
  void ina219SetCalibration_32V_1A(void);
  void ina219SetCalibration_16V_400mA(void);
  int16_t getShuntVoltage_raw(void);
  int16_t getCurrent_raw(void);
  uint16_t getBusVoltage_raw(void);
  uint16_t getBusPower_raw(void);
};
