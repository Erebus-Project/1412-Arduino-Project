/*
 * Author: Caleb Lochner
 * Version 0.0.9 A
 */

#define FRechoPin 4 //Front echo pin
#define FRpingPin 2 //Front Trigger pin
#define REechoPin 5 //Back echo pin
#define REpingPin 3 //Back ping pin
#define IRLeft 10   //IR out pin left
#define IRRight 8   //IR out pin right
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

  //IR Sensor pin set up
  pinMode(IRLeft, INPUT);   //Need LED Pin
  
  pinMode(IRRight, INPUT);  //Need LED Pin
  
  //Vibrator motor Pin set up
  pinMode(VMFront, OUTPUT);
  pinMode(VMBack, OUTPUT);
  pinMode(VMLeft, OUTPUT);
  pinMode(VMRight, OUTPUT);
}

void loop()
{
  Serial.println("Loop");   //Loop ID
  
  long cmFR = detectFR();   //Distance from front
  long cmRE = detectRE();   //Distance from Rear

  if(cmFR < 40)             //Buzz Front on/off trigger
  {
    analogWrite(VMFront, buzzlevel(cmFR));
  }
  else
  {
    analogWrite(VMFront, 0);
  }
  
  if(cmRE < 40)             //Buzz Rear on/off Trigger
  {
    analogWrite(VMBack, buzzlevel(cmRE));
  }
  else
  {
    analogWrite(VMBack, 0);
  }  
}

long detectFR()           //Front detect distance
{
  long duration, cm;
  pinMode(FRpingPin, OUTPUT);
  digitalWrite(FRpingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(FRpingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(FRpingPin, LOW);
  duration = pulseIn(FRechoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("Front: ");
  Serial.print(cm);
  Serial.println(" cm");
  return cm;
}

long detectRE()           //Rear detect distance
{
  long duration, cm;
  pinMode(REpingPin, OUTPUT);
  digitalWrite(REpingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(REpingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(REpingPin, LOW);
  duration = pulseIn(REechoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("Back: ");
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
  double BL = 0.0;
  BL = (0.057 * ( cm * cm) - (16.586 * cm) + 1072.2);
  int level = (int) BL;
  Serial.println(level);
  return level;
}
