/******************************************************************************
SFE_ISL29125.h
Core header file for the ISL29125 RGB sensor library.
Jordan McConnell @ SparkFun Electronics
25 Mar 2014
https://github.com/sparkfun/ISL29125_Breakout

This header file declares the SFE_ISL29125 sensor class as well as its various
functions and variables. It also defines sensor specifics including register
addresses and masks for setting/interpreting register data.

Developed/Tested with:
Arduino Uno
Arduino IDE 1.0.5

This code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given. 
******************************************************************************/

#ifndef SFE_ISL29125_h
#define SFE_ISL29125_h

#include "Wire.h"

// ISL29125 I2C Address
#define ISL_I2C_ADDR 0x44

// ISL29125 Registers
#define DEVICE_ID 0x00 // default id is 0x7d, write 0x46 in 'the write only' to reset all registers to default states
#define CONFIG_1 0x01 // b2:b0 mode - 101 rgb, 100 standby, b3 range - 0 375 lux, 1 10,000 lux, b4 resolution - 0 16bits, 1 12 bits, b5 sync - 0 adc start at i2c write 0x01, 1 adc start at rising !int
#define CONFIG_2 0x02 // b5:b0 active ir compensation, b7 ir offset, not sure what default should be, see graph on page 11 of datasheet
#define CONFIG_3 0x03 // b1:b0 interrupt threshold - 00 no interrupt, 01 green, 10 red, 11 blue, b3:b2 interrupt persist control (# of interrupt conditions that must happen before interrupt flag and !int pin is set) - 00 1, 01 2, 10 4, 11 8, b4 rgb conversion done to !int control - 0 disable, 1 enable
#define THRESHOLD_LL 0x04 // lower interrupt threshold (causes interrupt when measurement is below this value), 0 by default
#define THRESHOLD_LH 0x05
#define THRESHOLD_HL 0x06 // high interrupt threshold (causes interrupt when measurement is above this value), 0 by default
#define THRESHOLD_HH 0x07
#define STATUS 0x08 // b0 RGBTHF - 0 interrupt is cleared or not triggered, 1 interrupt is triggered, b1 conversion - 0 still convert or cleared, 1 conversion completed, b2 brown out - 0 no brownout, 1 powerdown or brownout occured, b5:b4 rgb conversion - 00 no operation, 01 green, 10 red, 11 blue
#define GREEN_L 0x09 // green adc value
#define GREEN_H 0x0A
#define RED_L 0x0B // red adc value
#define RED_H 0x0C
#define BLUE_L 0x0D // blue adc value
#define BLUE_H 0x0E

// Configuration Settings
#define CFG_DEFAULT 0x00

// CONFIG1
#define CFG1_MODE_POWERDOWN 0x00
#define CFG1_MODE_G 0x01
#define CFG1_MODE_R 0x02
#define CFG1_MODE_B 0x03
#define CFG1_MODE_STANDBY 0x04
#define CFG1_MODE_RGB 0x05
#define CFG1_MODE_RG 0x06
#define CFG1_MODE_GB 0x07

#define CFG1_375LUX 0x00
#define CFG1_10KLUX 0x08

#define CFG1_16BIT 0x00
#define CFG1_12BIT 0x10

#define CFG1_ADC_SYNC_NORMAL 0x00
#define CFG1_ADC_SYNC_TO_INT 0x20

// CONFIG2
#define CFG2_IR_OFFSET_OFF 0x00
#define CFG2_IR_OFFSET_ON 0x80

#define CFG2_IR_ADJUST_LOW 0x00
#define CFG2_IR_ADJUST_MID 0x20
#define CFG2_IR_ADJUST_HIGH 0x3F

// CONFIG3
#define CFG3_NO_INT 0x00
#define CFG3_G_INT 0x01
#define CFG3_R_INT 0x02
#define CFG3_B_INT 0x03

#define CFG3_INT_PRST1 0x00
#define CFG3_INT_PRST2 0x04
#define CFG3_INT_PRST4 0x08
#define CFG3_INT_PRST8 0x0C

#define CFG3_RGB_CONV_TO_INT_DISABLE 0x00
#define CFG3_RGB_CONV_TO_INT_ENABLE 0x10

// STATUS FLAG MASKS
#define FLAG_INT 0x01
#define FLAG_CONV_DONE 0x02
#define FLAG_BROWNOUT 0x04
#define FLAG_CONV_G 0x10
#define FLAG_CONV_R 0x20
#define FLAG_CONV_B 0x30


class SFE_ISL29125
{
 public:
  SFE_ISL29125(uint8_t addr = ISL_I2C_ADDR);
  ~SFE_ISL29125();

  bool init();
  bool reset();
  bool config(uint8_t config1, uint8_t config2, uint8_t config3);
  
  void setUpperThreshold(uint16_t data);
  void setLowerThreshold(uint16_t data);
  uint16_t readUpperThreshold();
  uint16_t readLowerThreshold();
  
  uint16_t readRed();
  uint16_t readGreen();
  uint16_t readBlue();
  
  uint8_t readStatus();
  
 private:
  uint8_t _addr;
  
  uint8_t read8(uint8_t reg);
  void write8(uint8_t reg, uint8_t data);
  
  uint16_t read16(uint8_t reg);
  void write16(uint8_t reg, uint16_t data);
  
};

#endif