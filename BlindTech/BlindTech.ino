/*
 * Author: Caleb Lochner
 * Version 0.2.6 B
 */

#define FRechoPin 4 //Front echo pin
#define FRpingPin 2 //Front Trigger pin

#define REechoPin 5 //Back echo pin
#define REpingPin 3 //Back Trigger pin

#define LechoPin 6  //Left echo pin
#define LPingPin 7  //Left Trigger pin

#define RechoPin 8  //Right echo pin
#define RPingPin 9   //Right Trigger pin

#define VMFront A0  //Front Vibrator motor pin
#define VMBack A1   //Back Vibrator motor pin
#define VMLeft A2   //Left Vibrator motor pin
#define VMRight A3  //Right Vibrator motor pin

bool DEBUG = false;

void setup()
{
  //Serial Monitor for debug purposes
  Serial.begin(9600);
  
  //Ultrasonic Sensor pin set up
  pinMode(FRpingPin, INPUT);
  pinMode(FRechoPin, INPUT);
  
  pinMode(REpingPin, INPUT);
  pinMode(REechoPin, INPUT);

  pinMode(LPingPin, INPUT);
  pinMode(LechoPin, INPUT);
  
  pinMode(RPingPin, INPUT);
  pinMode(RechoPin, INPUT);
  
  //Vibrator motor Pin set up
  pinMode(VMFront, OUTPUT);
  pinMode(VMBack, OUTPUT);
  pinMode(VMLeft, OUTPUT);
  pinMode(VMRight, OUTPUT);
}

void loop()
{
  Serial.println("Loop");   //Loop ID
  
  long cmFR = detect(FRpingPin, FRechoPin);   //Distance from front
  long cmRE = detect(REpingPin, REechoPin);   //Distance from Rear
  long cmLE = detect(LPingPin, LechoPin);     //Distance From Left
  long cmRI = detect(RPingPin, RechoPin);     //Distance from Right
  
  analogWrite(VMFront, buzzlevel(cmFR));
  analogWrite(VMBack, buzzlevel(cmRE));
  analogWrite(VMLeft, buzzlevel(cmLE));
  analogWrite(VMRight, buzzlevel(cmRI));
}

long detect(int ping, int echo)           //Detect distance
{
  long duration, cm;
  pinMode(ping, OUTPUT);
  digitalWrite(ping, LOW);
  delayMicroseconds(2);
  digitalWrite(ping, HIGH);
  delayMicroseconds(10);
  digitalWrite(ping, LOW);
  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("Front: ");
  Serial.print(cm);
  Serial.println(" cm");
  return cm;
}

long microsecondsToCentimeters(long microseconds) //Convert to cm 
{
   return microseconds / 29 / 2;
}

int buzzlevel(long cm)            //Buzz level at vibrator motor
{
  int level = 0;
  if(cm < 40)
  {
    double BL = 0.0;
    BL = (0.057 * ( cm * cm) - (16.586 * cm) + 1072.2);
    level = (int) BL;
    Serial.println(level);
  }
  else
  {
    level = 0;
    Serial.println(level);
  }
  return level;
}
