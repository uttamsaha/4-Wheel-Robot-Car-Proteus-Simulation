
#include <AFMotor.h>
#include <NewPing.h>
#include<Servo.h>
#define trigger A1
#define echo A0
#define maxDistance 300
#define IR A5
#define motorSpeed 255

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

NewPing sonar(trigger, echo, maxDistance);

Servo myservo;
char voice;
int forwardSensor, backwardSensor; 

void setup() {
  Serial.begin(9600);
  myservo.attach(10);
  myservo.write(90);
  pinMode(IR, INPUT);
}

void loop() {
  int distance = sonar.ping_cm();
  
  if(Serial.available()>0) {
    voice="";   
    delay(2);
    voice = Serial.read();
    delay(2);
  
    if (voice == 'L') {
      left();
    }
 
    else if(voice == 'R') {
      right();
    }
    else if(voice == 'S'){
      Stop();
    }
  }
  while(voice=='F') {
     forward();
  }
  while(voice=='B') {
    backward();
  }
}



void forward() {
  int distance = sonar.ping_cm();
  if(distance < 30 || Serial.read()=='S'){
    Stop();
    voice="";
  }
  else {
    motor1.setSpeed(motorSpeed); 
    motor1.run(FORWARD); 
    motor2.setSpeed(motorSpeed);
    motor2.run(FORWARD);
    motor3.setSpeed(motorSpeed); 
    motor3.run(FORWARD); 
    motor4.setSpeed(motorSpeed); 
    motor4.run(FORWARD); 
  }
}

void backward() {
  int IR_Sensor = digitalRead(IR);
  if(IR_Sensor == 0 || Serial.read()=='S') {
    Stop();
    voice="";
  }
  else {
    motor1.setSpeed(motorSpeed); 
    motor1.run(BACKWARD); 
    motor2.setSpeed(motorSpeed); 
    motor2.run(BACKWARD); 
    motor3.setSpeed(motorSpeed); 
    motor3.run(BACKWARD);
    motor4.setSpeed(motorSpeed); 
    motor4.run(BACKWARD); 
  }
}

void left() {
  myservo.write(180);
  delay(400);
  myservo.write(90);
  delay(400);
  motor1.run(BACKWARD);
  motor1.setSpeed(motorSpeed);
  motor2.run(BACKWARD);
  motor2.setSpeed(motorSpeed);
  motor3.run(FORWARD);
  motor3.setSpeed(motorSpeed);
  motor4.run(FORWARD);
  motor4.setSpeed(motorSpeed);
  delay(380);
  Stop();
}

void right() {
  myservo.write(0);
  delay(400);
  myservo.write(90);
  delay(400);
  motor1.run(FORWARD);
  motor1.setSpeed(motorSpeed);
  motor2.run(FORWARD);
  motor2.setSpeed(motorSpeed);
  motor3.run(BACKWARD);
  motor3.setSpeed(motorSpeed);
  motor4.run(BACKWARD);
  motor4.setSpeed(motorSpeed);
  delay(380);
  Stop(); 
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
