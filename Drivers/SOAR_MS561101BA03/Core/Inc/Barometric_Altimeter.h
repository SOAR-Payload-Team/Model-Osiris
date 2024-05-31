/*
 * Barometric_Altimeter.h
 *
 *  Created on: May 25, 2024
 *      Author: shaan
 */
#include "stm32h7xx_hal.h"
#include <stdint.h>

#ifndef INC_BAROMETRIC_ALTIMETER_H_
#define INC_BAROMETRIC_ALTIMETER_H_
#define MS5611_ADDR 0b11101111   //Shifted address for 7-bit I2C address
#define TEST_REG    0x00       // Register address to send test message


class MS5611
{
public:

MS5611(I2C_HandleTypeDef port)
{
this->port = port;
}

    /* Initalizes the I2C line and resets IMU*/
    uint8_t init();

    void read();

    /*Reads ADC value from barometer and returns unisgned 32 bit int*/
    uint8_t readADCP();
    uint8_t readADCT();

    void readPROM();

    void calculate();

    /* Requests Message from Barometer. Stores result in msg*/
    void receive(uint8_t length, uint8_t *msg);

    /*Reads + converts pressure to digital number, stores in barometer eeprom*/
    void convertT();
    void convertP();

    uint32_t temperature;
    uint32_t pressure;

    uint8_t reset_data = 0x1E;  // reset CMD
    uint8_t cmdReadADC = 0x00; // read CMD for ADC
    uint8_t osrP;
    uint8_t osrT;
    uint8_t bufP[3];
    uint8_t bufT[3];
    uint32_t dpv;
    uint32_t dtv;
    uint8_t delayP;
    uint8_t delayT;
    uint16_t prom[6];
    HAL_StatusTypeDef ret;

    I2C_HandleTypeDef port;
};



#endif /* INC_BAROMETRIC_ALTIMETER_H_ */
