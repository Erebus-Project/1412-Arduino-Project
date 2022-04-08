/*
 * Author: Caleb Lochner
 * Version 0.0.6 A
 */

#define FRechoPin 4 //Front echo pin
#define FRpingPin 2 //Front Trigger pin

bool DEBUG = false;

void setup()
{
  Serial.begin(9600);
  pinMode(FRpingPin, INPUT);
  pinMode(FRechoPin, INPUT);
  pinMode(A0, OUTPUT);
}

void loop()
{
  Serial.println("Loop");
  delay(1000);
}
