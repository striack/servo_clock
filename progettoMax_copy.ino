pro /*************************************************************
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
const byte SX1509_LED_PIN_12 = 12; // LED to SX1509's pin 12

const byte SX1509_LED_PIN_15 = 15;

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
  io.pinMode(SX1509_LED_PIN_12, ANALOG_OUTPUT);
  io.pinMode(SX1509_LED_PIN_15, ANALOG_OUTPUT);
  
}

int calculate_duty_cycle(int percentage)
{
  return 100 / percentage;
}

void duty (int value, byte pin)
{
  int on_time = value * 200; // ,ocrpsec
  for (int x = 0; x <= 200; x++) { 
    io.analogWrite(pin, 1023); 
    delayMicroseconds(on_time);              // 1.5ms
    io.analogWrite(pin, 0);    
    delayMicroseconds(20000 - on_time);
                 // 18.5ms (Totale 20ms)
  };
  Serial.println (on_time);

}

//angolo da 0 a 16, upmaxmin intervallo in ms up,
//analogwriteup pin 1 e 2 fino a upmin
//analogwritedown su pin relativo a upmin
//analogwritedown su entrambi pin
//fine periodo 200ms, torna all'inizio
//quante cose si possono mettere fuori dal loop?
//magari fare conti e ordine variabili fuori da loop e inserire solo logica gia ordinata nel loop
void duty2 (int angle1, int angle2, byte pin1, byte pin2)
{
  int dutyMin = 1;
  int upMax = 16+angle2;
  int upMin = 16+angle1;

  if (angle1 > angle2) {
    dutyMin = 2;
  }

  if dutyMin == 2 {
    //swap upMin upMax
  }


  int period= 200;
  for (int x =0; x<200; x++)  {
    
  }
}

void angle (int value)
{
  int duty = (value *45);
}



void loop()
{  


  Serial.println ("CIAO");
  
  duty (8, SX1509_LED_PIN_12);
  duty (8, SX1509_LED_PIN_15);
  delay (1000);
  duty (12, SX1509_LED_PIN_15);
  duty (12, SX1509_LED_PIN_12);
  delay (1000);
  duty (16, SX1509_LED_PIN_15);
  duty (16, SX1509_LED_PIN_12);
  delay (1000);
  

}