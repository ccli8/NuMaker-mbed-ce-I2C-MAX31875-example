/*
 * Copyright (c) 2019 Nuvoton Tecnology Corp. All rights reserved.
 *
 * This example uses MAX31875 library to read Thermo 6 Click
 * (MAX31875 temperature sensor) which placed on mikroBUS of
 * Nuvoton NuMaker-IoT-M487 board.
 *
 */

#include "mbed.h"
#include "max31875.h"
#include "max31875_cpp.h"

/* Declare the I2C of mikroBUS on board */
I2C mikro_i2c(PG_3, PG_2);

/* Declare the MAX31875 sensor */
MAX31875 temp_sensor(mikro_i2c, MAX31875_I2C_SLAVE_ADR_R0);

int main()
{
    float f_temperature;

    printf("\r\nmbed OS version is %d.\r\n", MBED_VERSION);
    printf("Start to read temperature ...\r\n");

    /* Set frequency of I2C bus to 1MHz */
    mikro_i2c.frequency(1000000);
    
    /* Configure temperature sensor for 8 times per second */
    temp_sensor.write_cfg(MAX31875_CFG_CONV_RATE_8 | MAX31875_CFG_RESOLUTION_12BIT);

    while(true)
    {
        /* It should wait at least 1/8 seconds for next read */
        //wait(MAX31875_WAIT_CONV_RATE_8);   
        /* But to slow print out rate, wait 1 second here */
        wait(1);

        f_temperature = temp_sensor.read_reg_as_temperature(MAX31875_REG_TEMPERATURE);
        printf("Temperature is %3.4f Celsius, %3.4f Fahrenheit\r\n",
                f_temperature,
                temp_sensor.celsius_to_fahrenheit(f_temperature));
    }

}

