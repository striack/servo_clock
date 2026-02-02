/*************************************************************
  analogWrite.ino
  SparkFun SX1509 I/O Expander Example: pwm output (analogWrite)
  Jim Lindblom @ SparkFun Electronics
  Original Creation Date: September 21, 2015
  https://github.com/sparkfun/SparkFun_SX1509_Arduino_Library

  This example demonstrates the SX1509's analogWrite function.
  Connect an LED to the SX1509's pin 15 (or any other pin, they
  can all PWM!). The SX1509 can either sink or source current,
  just don't forget your limiting resistor!

  Hardware Hookup:
  SX1509 Breakout ------ Arduino -------- Breadboard
        GND -------------- GND
        3V3 -------------- 3.3V
      SDA ------------ SDA (A4)
      SCL ------------ SCL (A5)
      15 -------------------------------- LED+
                                     LED- -/\/\/\- GND
                                                330

  Development environment specifics:
  IDE: Arduino 1.6.5
  Hardware Platform: Arduino Uno
  SX1509 Breakout Version: v2.0

  This code is beerware; if you see me (or any other SparkFun
  employee) at the local, and you've found our code helpful,
  please buy us a round!

  Distributed as-is; no warranty is given.
*************************************************************/

#include <Wire.h>           // Include the I2C library (required)
#include <SparkFunSX1509.h> //Click here for the library: http://librarymanager/All#SparkFun_SX1509
#include <Servo.h>


Servo myServo0;




// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
const byte SX1509_ADDRESS = 0x3E; // SX1509 I2C address
SX1509 io;                        // Create an SX1509 object to be used throughout

// SX1509 Pin definition:
const byte SX1509_LED_PIN = 12; // LED to SX1509's pin 12

void setup()
{
  Serial.begin(9600);
  Serial.println("SX1509 Example");

  Wire.begin();

  // Call io.begin(<address>) to initialize the SX1509. If it
  // successfully communicates, it'll return 1.
  if (io.begin(SX1509_ADDRESS) == false)
  {
    Serial.println("Failed to communicate. Check wiring and address of SX1509.");
    while (1)
      ; // If we fail to communicate, loop forever. doesn't work
  }

  // Use the pinMode(<pin>, <mode>) function to set our led
  // pin as an ANALOG_OUTPUT, which is required for PWM output
  io.pinMode(SX1509_LED_PIN, ANALOG_OUTPUT);
  
}

int calculate_duty_cycle(int percentage)
{
  return 100 / percentage;
}

//void duty_cycle_50 ()
//{
  //for (int x = 0; x<= 10; x++) { 
  //  io.analogWrite(SX1509_LED_PIN, 1023);
    //delay (10);
    //io.analogWrite(SX1509_LED_PIN, 0);
    //delay (10);

//}
void duty (int value)
{
  int on_time = value * 200; // ,ocrpsec
  for (int x = 0; x <= 200; x++) { 
    io.analogWrite(SX1509_LED_PIN, 1023); 
    delayMicroseconds(on_time);              // 1.5ms
    io.analogWrite(SX1509_LED_PIN, 0);    
    delayMicroseconds(20000 - on_time);
                 // 18.5ms (Totale 20ms)
  };
  Serial.println (on_time);

}
void angle (int value)
{
  int duty = (value *45)
}



void loop()
{  


  Serial.println ("CIAO");
  
  duty (8);
  delay (1000);
  duty (12);
  delay (1000);
  duty (16);
  delay (1000);
  

}