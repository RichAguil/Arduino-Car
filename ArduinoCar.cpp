#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //Creating motorshield object from the Adafruit_Motorshield class
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1); //Creating motor object from the Adafruit_DCMotor class
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);//the number in .getmotor() signifies the port number
Adafruit_DCMotor *Motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *Motor4 = AFMS.getMotor(4);

void setup() 
{
  Serial.begin(9600); //Opens up serial connection and sets transmission rate at 9600 bps
  pinMode(6, OUTPUT); //Setting pin 6 to be the trigger (transmitter)
  pinMode(7, INPUT); //Setting pin 7 as the receiver (echo)
  AFMS.begin(); //Connects to the motor controller
  delay(5000); //delays program for 5000 milliseconds
  Motor1->run(FORWARD);
  Motor1->setSpeed(200); //sets default motor speed at a PWM value of 200
  
  Motor2->run(FORWARD);
  Motor2->setSpeed(200);
  
  Motor3->run(FORWARD);
  Motor3->setSpeed(200);
  
  Motor4->run(FORWARD);
  Motor4->setSpeed(200);
}

void loop() 
{
  unsigned long Time;
  Time=millis(); //Keep track of time since program began running
  double duration, distance;
  double Vs=13385.8; //velocity of sound in air, in/s
  digitalWrite(6, LOW); //Sets a LOW value for pin 6, LOW = 0 volts
  delayMicroseconds(10);
  digitalWrite(6, HIGH); //Sets a HIGH value for pin 6, HIGh = 6 volts
  delayMicroseconds(10);
  digitalWrite(6, LOW);
  delayMicroseconds(10);
  duration=pulseIn(7, HIGH); //pulseIn function measures pulses from digital input pins
  distance=((duration/2)*Vs)/1000000; //duration is in microseconds, thus division by 1e6 is necessary
  Serial.write("Distance: ");
  Serial.println(distance);
  Serial.print("Duration: ");
  Serial.println(duration);
    if (distance <= 7.0)
   {
    Motor1->run(RELEASE); //Cuts power to DC motors
    Motor2->run(RELEASE);
    Motor3->run(RELEASE);
    Motor4->run(RELEASE);
    delay(1000);
    Motor1->run(BACKWARD);
    Motor2->run(BACKWARD);
    Motor3->run(BACKWARD);
    Motor4->run(BACKWARD);
    delay(250);
    Motor3->run(FORWARD);
    Motor4->run(FORWARD);
    delay(725);
    Motor3->run(RELEASE);
    Motor4->run(RELEASE);      
  }
  else
  {     
   Motor1->run(FORWARD);
   Motor2->run(FORWARD);
   Motor3->run(FORWARD);
   Motor4->run(FORWARD);  
  }
  while(Time>40000) //only want program to "run" for 40 seconds)
  {
    Time=millis();
    Motor1->run(RELEASE);
    Motor2->run(RELEASE);
    Motor3->run(RELEASE);
    Motor4->run(RELEASE); 
  }
  delayMicroseconds(10);
}