/*
 * Author: Caleb Lochner
 * Version 0.0.6 A
 */

#define FechoPin 4 //Front echo pin
#define FpingPin 2 //Front Trigger pin

bool DEBUG = false;

void setup()
{
  Serial.begin(9600);
  pinMode(FpingPin, INPUT);
  pinMode(FechoPin, INPUT);
  pinMode(A0, OUTPUT);
}

void loop()
{
  Serial.println("Loop");
  delay(1000);
}
