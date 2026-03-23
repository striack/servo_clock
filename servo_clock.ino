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
// #include <Servo.h>



// Servo Ocs;




// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
const byte SX1509_ADDRESS = 0x3E; // SX1509 I2C address
SX1509 io;                        // Create an SX1509 object to be used throughout

// SX1509 Pin definition:

const byte SX1509_LED_PIN_8  =  8;
const byte SX1509_LED_PIN_9  =  9;
const byte SX1509_LED_PIN_10 = 10;
const byte SX1509_LED_PIN_11 = 11;
const byte SX1509_LED_PIN_12 = 12;
const byte SX1509_LED_PIN_13 = 13;
const byte SX1509_LED_PIN_14 = 14;

const byte clock_arms[] = {
  SX1509_LED_PIN_8,
  SX1509_LED_PIN_9,
  SX1509_LED_PIN_10,
  SX1509_LED_PIN_11,
  SX1509_LED_PIN_12,
  SX1509_LED_PIN_13,
  SX1509_LED_PIN_14
};

const byte on_left = 150;
const byte off = 20;


const int num_arms = sizeof(clock_arms) / sizeof(clock_arms[0]);
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

  //   Serial.println("Before setting ext clock");
  // io.clock(EXTERNAL_CLOCK);
  // Serial.println("After setting ext clock");
  // pinMode(10, OUTPUT);
  // tone(9, 1000, 0);
  // Ocs.attach (10);
  // Ocs.writeMicroseconds (10000);
  

  // Use the pinMode(<pin>, <mode>) function to set our led
  // pin as an ANALOG_OUTPUT, which is required for PWM output
  for(int i=0; i<num_arms;i++){
    io.pinMode(clock_arms[i], ANALOG_OUTPUT);
    io.ledDriverInit(clock_arms[i],4);
    // Serial.println("After setting ext clock");
  }
  // io.pinMode(SX1509_LED_PIN_8, ANALOG_OUTPUT);
  // io.pinMode(SX1509_LED_PIN_12, ANALOG_OUTPUT);
  // io.pinMode(SX1509_LED_PIN_9, ANALOG_OUTPUT);
  //
  // io.ledDriverInit(SX1509_LED_PIN_8,4);
  // io.ledDriverInit(SX1509_LED_PIN_9,4);
  // io.ledDriverInit(SX1509_LED_PIN_12,4);

  

  //io.setupBlink(SX1509_LED_PIN_12, 1000, 1000);


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

  if (dutyMin == 2) {
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


void one()
{


  io.analogWrite(SX1509_LED_PIN_13, on_left);
  io.analogWrite(SX1509_LED_PIN_14, on_left);

  io.analogWrite(SX1509_LED_PIN_8, off);
  io.analogWrite(SX1509_LED_PIN_9, off);
  io.analogWrite(SX1509_LED_PIN_10, off);
  io.analogWrite(SX1509_LED_PIN_11, off);
  io.analogWrite(SX1509_LED_PIN_12, off);

}
void due()
{


  io.analogWrite(SX1509_LED_PIN_8, on_left);
  io.analogWrite(SX1509_LED_PIN_10, on_left);
  io.analogWrite(SX1509_LED_PIN_12, on_left);
  io.analogWrite(SX1509_LED_PIN_11, on_left);
  io.analogWrite(SX1509_LED_PIN_14, on_left);

  io.analogWrite(SX1509_LED_PIN_9, off);
  io.analogWrite(SX1509_LED_PIN_13, off);
}
void tre()
{


  io.analogWrite(SX1509_LED_PIN_8, on_left);
  io.analogWrite(SX1509_LED_PIN_10, on_left);
  io.analogWrite(SX1509_LED_PIN_12, on_left);
  io.analogWrite(SX1509_LED_PIN_11, on_left);
  io.analogWrite(SX1509_LED_PIN_9, on_left);

  io.analogWrite(SX1509_LED_PIN_14, off);
  io.analogWrite(SX1509_LED_PIN_13, off);
}

void quattro()
{



  io.analogWrite(SX1509_LED_PIN_10, on_left);
  io.analogWrite(SX1509_LED_PIN_12, on_left);
  io.analogWrite(SX1509_LED_PIN_13, on_left);
  io.analogWrite(SX1509_LED_PIN_9, on_left);

  io.analogWrite(SX1509_LED_PIN_8, off);
  io.analogWrite(SX1509_LED_PIN_14, off);
  io.analogWrite(SX1509_LED_PIN_11, off);
}

void cinque()
{
  io.analogWrite(SX1509_LED_PIN_8, on_left);
  io.analogWrite(SX1509_LED_PIN_10, on_left);
  io.analogWrite(SX1509_LED_PIN_13, on_left);
  io.analogWrite(SX1509_LED_PIN_11, on_left);
  io.analogWrite(SX1509_LED_PIN_9, on_left);

  io.analogWrite(SX1509_LED_PIN_14, off);
  io.analogWrite(SX1509_LED_PIN_12, off);
}

void six()
{


  io.analogWrite(SX1509_LED_PIN_8, on_left);
  io.analogWrite(SX1509_LED_PIN_10, on_left);
  io.analogWrite(SX1509_LED_PIN_13, on_left);
  io.analogWrite(SX1509_LED_PIN_11, on_left);
  io.analogWrite(SX1509_LED_PIN_9, on_left);
  io.analogWrite(SX1509_LED_PIN_14, on_left);

  io.analogWrite(SX1509_LED_PIN_12, off);
}
void sette()
{

  io.analogWrite(SX1509_LED_PIN_11, on_left);
  io.analogWrite(SX1509_LED_PIN_12, on_left);
  io.analogWrite(SX1509_LED_PIN_9, on_left);

  io.analogWrite(SX1509_LED_PIN_8, off);
  io.analogWrite(SX1509_LED_PIN_10, off);
  io.analogWrite(SX1509_LED_PIN_13, off);
  io.analogWrite(SX1509_LED_PIN_14, off);
}
void otto()
{

  io.analogWrite(SX1509_LED_PIN_8, on_left);
  io.analogWrite(SX1509_LED_PIN_10, on_left);
  io.analogWrite(SX1509_LED_PIN_13, on_left);
  io.analogWrite(SX1509_LED_PIN_11, on_left);
  io.analogWrite(SX1509_LED_PIN_9, on_left);
  io.analogWrite(SX1509_LED_PIN_14, on_left);

  io.analogWrite(SX1509_LED_PIN_12, on_left);
}
void nove()
{

  io.analogWrite(SX1509_LED_PIN_13, on_left);
  io.analogWrite(SX1509_LED_PIN_11, on_left);
  io.analogWrite(SX1509_LED_PIN_9, on_left);
  io.analogWrite(SX1509_LED_PIN_10, on_left);
  io.analogWrite(SX1509_LED_PIN_12, on_left);

  io.analogWrite(SX1509_LED_PIN_8, off);
  io.analogWrite(SX1509_LED_PIN_14, off);

}
void zero()
{

  io.analogWrite(SX1509_LED_PIN_13, on_left);
  io.analogWrite(SX1509_LED_PIN_11, on_left);
  io.analogWrite(SX1509_LED_PIN_9, on_left);
  io.analogWrite(SX1509_LED_PIN_14, on_left);
  io.analogWrite(SX1509_LED_PIN_12, on_left);

  io.analogWrite(SX1509_LED_PIN_8, on_left);
  
  io.analogWrite(SX1509_LED_PIN_10, off);

}


void loop() {


  const byte off = 20;
  const byte on_left = 150;


  //12 buttom left
  // io.analogWrite(SX1509_LED_PIN_12, 50);
  // io.analogWrite(SX1509_LED_PIN_8, 50);
  // io.analogWrite(SX1509_LED_PIN_9, 50);
  // // Ocs.write(0);
  // delay(1000);

  //on buttom left
 // for(int i=0; i<num_arms; i++){
  //  io.analogWrite(clock_arms[i], on_left);
  //  delay(50);
  //}
  zero();
  delay(1000);
  one();
  delay(1000);
  due();
  delay(1000);
  tre();
  delay(1000);
  quattro();
  delay(1000);
  cinque();
  delay(1000);
  six();
  delay(1000);
  sette();
  delay(1000);
  otto();
  delay(1000);
  nove();
  //io.analogWrite(SX1509_LED_PIN_8, on_left);

  //io.analogWrite(SX1509_LED_PIN_8, on_left);

  //io.analogWrite(SX1509_LED_PIN_8, off);
  delay(5000);

  //io.analogWrite(SX1509_LED_PIN_8, off);
  //for(int i=0; i<num_arms; i++){
  //  io.analogWrite(clock_arms[i], off);
  //  delay(50);
  //}
  //delay(1000);
  // io.analogWrite(SX1509_LED_PIN_12, on_left);
  //
  // // io.analogWrite(SX1509_LED_PIN_8, 255-on_left);
  // io.analogWrite(SX1509_LED_PIN_8, on_left);
  //
  // io.analogWrite(SX1509_LED_PIN_9, on_left);
  // Ocs.write(90);


  // io.analogWrite(SX1509_LED_PIN_12, off);
  //
  // io.analogWrite(SX1509_LED_PIN_8, off);
  //
  // io.analogWrite(SX1509_LED_PIN_9, off);
  // // Ocs.write(180);
  //   delay(1000);
}

//blink ()

/*{  


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
  
//
}*/
