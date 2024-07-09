#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 
#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 190 
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motorL(2, MOTOR12_1KHZ); //motor L 
AF_DCMotor motorR(4, MOTOR34_1KHZ); //motor R
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {

  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
 int distanceR = 0;
 int distanceL = 0;
 delay(40);
 
 if(distance<=30)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);
  if(distanceR <= 30 && distanceL <= 30){
    turnAround();
    moveStop();
  } else {
    if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motorL.run(RELEASE); 
  motorR.run(RELEASE);
  goesForward = false;
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motorL.run(FORWARD);      
    motorR.run(FORWARD);  
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
   {
    motorL.setSpeed(speedSet);
    motorR.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motorL.run(BACKWARD);      
    motorR.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
  {
    motorL.setSpeed(speedSet);
    motorR.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  goesForward = false;
  motorL.run(FORWARD);
  motorR.run(BACKWARD);    
  delay(500);
  moveStop();
  moveForward();          
} 
 
void turnLeft() {
  goesForward = false;
  motorL.run(BACKWARD);     
  motorR.run(FORWARD);    
  delay(500);
  moveStop();
  moveForward();
}  

void turnAround() {
  goesForward = false;
  motorL.run(FORWARD);
  motorR.run(BACKWARD);    
  delay(1000);
  moveStop();
  moveForward();
}
