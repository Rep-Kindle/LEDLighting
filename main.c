/* 
 * File:   main.c
 * Author: Jamie Raineault
 *
 * Created on August 25, 2016, 3:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f86j50.h>
/***************Crystal Frequency******/
#define XtalFreq 32768000

//I2c Functions for real time clock
void I2c_init();
void I2c_start();
void I2c_stop();
void I2c_restart();
void I2c_wait();
void I2c_send(unsigned char dat);
unsigned char I2c_read(void);

//real time clock Read Function
unsigned char rtc1307_read(unsigned char address); 
//variables for real time clock
unsigned char sec,min,hour;

// main program function
int main(int argc, char** argv) 
{
    //function to set the real time clock
    void RealTimeClock ()
    {
        //configuring portB pins as outputs for real time clock
        TRISB=0x00;
        //to generate the clock signal
        I2c_init();    
        I2c_start();
        I2c_send(0xD0);
        I2c_send(0x80);    //CH = 1 Stop oscillator
        
        //Set clock calender and time
        I2c_send(0x00);    //second
        I2c_send(0x01);    //minute
        I2c_send(0x01);    //hour
        I2c_stop();        //Stop the I2C Protocol
    
        //Have to start the Clock again
        I2c_start();
        I2c_send(0xD0);
        I2c_send(0x00);
        I2c_send(0x00);    //start Clock and set the second hand to Zero
        I2c_stop();
    }
    //configure all PORTA pins as inputs for user selector switch
    TRISA = 1;
    PORTA = 0xff;
    //Continuous loop for program
    while(1)
    {
        //reading the real time clock        
        sec = rtc1307_read(0x00);
        min = rtc1307_read(0x01);
        hour = rtc1307_read(0x02);
        __delay_ms(1);
    
    }
    return (EXIT_SUCCESS);
    
}

