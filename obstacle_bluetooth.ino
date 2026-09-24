#include <AFMotor.h>
#include <Servo.h>
#include <SoftwareSerial.h>


 #define trigPin  4
 #define echoPin  5

 char command;

SoftwareSerial BT(A2,A3);


AF_DCMotor motor1(1);
AF_DCMotor motor2(3);

Servo servoMotor;
const int servoCenter = 90;

void setup() {
  Serial.begin(38400);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  motor1.setSpeed(220);
  motor2.setSpeed(255);
  BT.begin(38400);
  Serial.println("bt ready"); 
  servoMotor.attach(3); 
  servoMotor.write(servoCenter);
  delay(2000); 
  
}

void loop() {
 int swVal=digitalRead(swPin);

 if(BT.available() > 0){
  bluetoothMode();
 }
 else{
  obstacleMode();
 }
}

 void bluetoothMode(){
 
   command = BT.read();

switch (command){
  case 'F': BmoveForward();
  break;

  case 'B': BmoveBackward();
  break;

  case 'R': BturnRight();
  break;

  case 'L': BturnLeft();
  break;

  case 'S': BstopBot();
  break;

  default:
  break;
}

 }


void BmoveForward(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
void BmoveBackward(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}

void BturnLeft(){
  
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  
}

void BturnRight(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

void BstopBot(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
 
 

 void obstacleMode(){ 
   int distance=getDistance();

  if (distance > 20) {
    moveForward();

    
    while (true) {
      int newDist = getDistance();
      Serial.print("Forward dist: ");
      Serial.println(newDist);

      if (newDist <= 20) {
        stopRobot();
        delay(300);
        moveBackward();
        delay(600);
        stopRobot();
        delay(300);

        int distRight = lookRight();
        delay(300);
        int distLeft = lookLeft();
        delay(300);

        if (distRight > distLeft) turnRight();
        else turnLeft();

        break; 
      }
    }
  }  
  else {
    stopRobot();
  }
   }

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void moveBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}

void stopRobot() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void turnRight() {
  stopRobot();
  delay(300);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(1000);
  stopRobot();
}

void turnLeft() {
  stopRobot();
  delay(300);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(1000);
  stopRobot();
}

int lookRight() {
  servoMotor.write(30);
  delay(500);
  int distanceCm=getDistance();
  servoMotor.write(servoCenter);
  return distanceCm;
}

int lookLeft() {
  servoMotor.write(150);
  delay(500);
  int distanceCm=getDistance();
  servoMotor.write(servoCenter);
  return distanceCm;
}

int getDistance(){
  
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);  
  int distance = duration*0.034/2;  

  return distance;
 }