/*
*@autor DanielBlancoR
*@email danielcblancor@gmail.com
*@ide Keil uVision
*/

#ifndef INA226_H_
#define INA226_H_


#ifdef __cplusplus
extern "C"
{	
#endif

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "stm32f7xx_hal.h"
//#include "main.h"

#define INA226_ADDRESS           0x40
#define R_SHUNT                  0.01

#define INA226_CONFIG_REG        0x00
#define INA226_SHUNT_VOLTAGE_REG 0x01
#define INA226_BUS_VOLTAGE_REG 	 0x02
#define INA226_POWER_REG         0x03
#define INA226_CURRENT_REG       0x04
#define INA226_CALIBRATION_REG   0x05
#define INA226_MASK_ENABLE_REG   0x06
#define INA226_ALERT_LIMIT_REG   0x07
#define INA226_MANUFACTURER_REG  0xFE
#define INA226_DIE_ID_REG        0xFF

typedef enum
{	
	Num_AVG_1    = 0x0,
	Num_AVG_4    = 0x1,
	Num_AVG_16   = 0x2,
	Num_AVG_64   = 0x3,
	Num_AVG_128  = 0x4,
	Num_AVG_256  = 0x5,
	Num_AVG_512  = 0x6,
	Num_AVG_1024 = 0x7
	
}Bit_AVG_t;

typedef enum
{
	ConvTime_140us  = 0x0,
	ConvTime_204us  = 0x1,
	ConvTime_332us  = 0x2,
	ConvTime_588us  = 0x3,
	ConvTime_1ms1   = 0x4,
	ConvTime_2ms116 = 0x5,
	ConvTime_4ms156 = 0x6,
	ConvTime_8ms244 = 0x7
		
}Bit_ConvTime_t;

typedef enum
{
	PowerDown        = 0x0,
	ShuntVoltage     = 0x1,
	BusVoltage       = 0x2,
	ShuntAndBus      = 0x3,
	PowerDown_       = 0x4,
	ShuntVoltageCont = 0x5,
	BusVoltageCont   = 0x6,
	ShuntAndBusCont  = 0x7

}Mode_t;

/* Configuration Register (00h) (Read/Write)
		[15] RST : Reset Bit.
		[9-11] AVG : Averaging Mode.
		[6-8] VBUSCT : Bus Voltage Conversion Time.
		[3-5] VSHCT : Shunt Voltage Conversion Time.
		[0-2] MODE : Operating Mode. */

typedef struct
{
	uint16_t       Config_mask;
	uint8_t        RST; 
	Bit_AVG_t      AVG;
	Bit_ConvTime_t VBUSCT;
	Bit_ConvTime_t VSHCT;
	Mode_t         MODE;

}INA226_Init;

typedef struct
{
	uint16_t ShuntVoltage;
	uint16_t BusVoltage;
	uint16_t Power;
	uint16_t Current;
	uint16_t Calibration;
	
	float CurrentLSB;
	
	
}INA226_Values;

void INA226_INIT (void);
void INA226_Config (Mode_t mode, Bit_ConvTime_t shuntVoltTime, Bit_ConvTime_t BusVoltTime , Bit_AVG_t AVGMode);
void INA226_Reset (void);
uint16_t INA226_ID(void);

void INA226_Voltage_Current_Power(float *volt, float *current, float *power);
float INA226_ShuntVoltage (void);
float INA226_BusVoltage (void);
float INA226_Power (void);
float INA226_Current(void);
void INA226_SetCalibration(float R_Shunt,float MaxExpCurrent);
uint16_t INA226_GetCalibration(void);

//void INA226_I2C_Write (uint8_t pByte, uint16_t Data);
//void INA226_I2C_Read (uint8_t pByte, uint16_t* pData);


#ifdef __cplusplus
}
#endif
#endif
