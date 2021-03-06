/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Name        : PCA9685.cpp
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Dec 9, 2012
 *
 * Copyright © 2012 Georgi Todorov  <terahz@geodar.com>
 */

#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdio.h>      /* Standard I/O functions */
#include <fcntl.h>
#include <syslog.h>		/* Syslog functionallity */
#include <inttypes.h>
#include <errno.h>
#include <math.h>

#include "PCA9685.h"

//! Constructor takes bus and address arguments
/*!
 \param bus the bus to use in /dev/i2c-%d.
 \param address the device address on bus
 */
PCA9685::PCA9685(int address) {
	/* 0x40 is address of i2c */
    /* wiringpi lib */
	i2c = wiringPiI2CSetup(address);
    /* pigpio lib */
	// i2c = i2cOpen(1, 0x40, 0);  /* using i2c bus 1 (flags = 0) */
	reset();
	setPWMFreq(333);
}

PCA9685::~PCA9685() {
	/* delete i2c */
	// i2cClose(i2c);
}
//! Sets PCA9685 mode to 00
void PCA9685::reset() {
    /* wiringpi lib */
	wiringPiI2CWriteReg8      (i2c, MODE1, 0x00) ;  /* Normal mode */
	wiringPiI2CWriteReg8      (i2c, MODE2, 0x04) ;  /* totem pole  */
    /* pigpio lib */
	// i2cWriteByteData(i2c, MODE1, 0x00);  /* Normal mode */
	// i2cWriteByteData(i2c, MODE2, 0x04);  /* totem pole  */
}
//! Set the frequency of PWM
/*!
 \param freq desired frequency. 40Hz to 1000Hz using internal 25MHz oscillator.
 */
void PCA9685::setPWMFreq(int freq) {
	uint8_t prescale_val = (CLOCK_FREQ / 4096 / freq)  - 1;

    /* wiringpi lib */
	wiringPiI2CWriteReg8      (i2c, MODE1, 0x10) ;				/* sleep 							*/
	wiringPiI2CWriteReg8      (i2c, PRE_SCALE, prescale_val) ;  /* multiplayer for PWM frequency 	*/
	wiringPiI2CWriteReg8      (i2c, MODE1, 0x80) ;				/* restart							*/
	wiringPiI2CWriteReg8      (i2c, MODE2, 0x04) ;				/* totem pole (default)				*/
    /* pigpio lib */
	// i2cWriteByteData(i2c, MODE1, 0x10);				/* sleep 							*/
	// i2cWriteByteData(i2c, PRE_SCALE, prescale_val); 	/* multiplayer for PWM frequency 	*/
	// i2cWriteByteData(i2c, MODE1, 0x80);				/* restart							*/
	// i2cWriteByteData(i2c, MODE2, 0x04);				/* totem pole (default)				*/
}

//! PWM a single channel
/*!
 \param led channel (1-16) to set PWM value for
 \param value 0-4095 value for PWM
 */
void PCA9685::setPWM(uint8_t led, int value) {
	setPWM(led, 0, value);
}
//! PWM a single channel with custom on time
/*!
 \param led channel (1-16) to set PWM value for
 \param on_value 0-4095 value to turn on the pulse
 \param off_value 0-4095 value to turn off the pulse
 */
void PCA9685::setPWM(uint8_t led, int on_value, int off_value) {
    /* wiringpi lib */
	wiringPiI2CWriteReg8      (i2c, LED0_ON_L + LED_MULTIPLYER * (led), on_value & 0xFF) ;
	wiringPiI2CWriteReg8      (i2c, LED0_ON_H + LED_MULTIPLYER * (led), on_value >> 8) ;
	wiringPiI2CWriteReg8      (i2c, LED0_OFF_L + LED_MULTIPLYER * (led), off_value & 0xFF) ;
	wiringPiI2CWriteReg8      (i2c, LED0_OFF_H + LED_MULTIPLYER * (led), off_value >> 8) ;
    /* pigpio lib */
	// i2cWriteByteData(i2c, LED0_ON_L + LED_MULTIPLYER * (led), on_value & 0xFF);
	// i2cWriteByteData(i2c, LED0_ON_H + LED_MULTIPLYER * (led), on_value >> 8);
	// i2cWriteByteData(i2c, LED0_OFF_L + LED_MULTIPLYER * (led), off_value & 0xFF);
	// i2cWriteByteData(i2c, LED0_OFF_H + LED_MULTIPLYER * (led), off_value >> 8);

    /* original */
	//	i2c->write_byte(LED0_ON_L + LED_MULTIPLYER * (led - 1), on_value & 0xFF);
	//	i2c->write_byte(LED0_ON_H + LED_MULTIPLYER * (led - 1), on_value >> 8);
	//	i2c->write_byte(LED0_OFF_L + LED_MULTIPLYER * (led - 1), off_value & 0xFF);
	//	i2c->write_byte(LED0_OFF_H + LED_MULTIPLYER * (led - 1), off_value >> 8);
}

//! Get current PWM value
/*!
 \param led channel (1-16) to get PWM value from
 */
int PCA9685::getPWM(uint8_t led) {
	int ledval = 0;

	/* original: ledval = i2c->read_byte(LED0_OFF_H + LED_MULTIPLYER * (led-1)) */
    /* wiringpi lib */
	ledval = wiringPiI2CReadReg8(i2c, LED0_OFF_H + LED_MULTIPLYER * (led)) ;
    /* pigpio lib */
	// ledval = i2cReadByteData(i2c, LED0_OFF_H + LED_MULTIPLYER * (led));

	ledval = ledval & 0xf;
	ledval <<= 8;

	/* original: ledval += i2c->read_byte(LED0_OFF_L + LED_MULTIPLYER * (led-1)) */
    /* wiringpi lib */
	ledval += wiringPiI2CReadReg8(i2c, LED0_OFF_L + LED_MULTIPLYER * (led)) ;
    /* pigpio lib */
	// ledval += i2cReadByteData(i2c, LED0_OFF_L + LED_MULTIPLYER * (led));

	return ledval;
}
