int m[] = {0,13,12,11,10,9,8,7,6};
int echoPin = 2;
int trigPin = 3; 
int buzzer = 4;  
int led = 5; 
int data = 0; 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  for(int i=0; i<=8; i++) {
    pinMode(m[i],OUTPUT);
  }
  Serial.begin(9600); 
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  if((distance<=50)) {
    digitalWrite(led, HIGH);
    int i = 0; 
    for(int i = 0; i<2; i++){
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
    }
    delay(1000);
    
    // *****stop******
    digitalWrite(m[1], LOW);
    digitalWrite(m[2], LOW);
    
    digitalWrite(m[3], LOW);
    digitalWrite(m[4], LOW);
    
    digitalWrite(m[5], LOW);
    digitalWrite(m[6], LOW);
    
    digitalWrite(m[7], LOW);
    digitalWrite(m[8], LOW);
  }
  else if(distance>50){
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    if(Serial.available() > 0) {
      data = Serial.read();
      if( data=='1'){
        // *****front******
        digitalWrite(m[1], HIGH);
        digitalWrite(m[2], LOW);
      
        digitalWrite(m[3], HIGH);
        digitalWrite(m[4], LOW);
      
        digitalWrite(m[5], HIGH);
        digitalWrite(m[6], LOW);
      
        digitalWrite(m[7], HIGH);
        digitalWrite(m[8], LOW);
      }
      else if(data=='0') {
        // *****back******
        digitalWrite(m[1], LOW);
        digitalWrite(m[2], HIGH);
      
        digitalWrite(m[3], LOW);
        digitalWrite(m[4], HIGH);
      
        digitalWrite(m[5], LOW);
        digitalWrite(m[6], HIGH);
      
        digitalWrite(m[7], LOW);
        digitalWrite(m[8], HIGH);
      }
      else{
        // *****stop******
        digitalWrite(m[1], LOW);
        digitalWrite(m[2], LOW);
      
        digitalWrite(m[3], LOW);
        digitalWrite(m[4], LOW);
      
        digitalWrite(m[5], LOW);
        digitalWrite(m[6], LOW);
      
        digitalWrite(m[7], LOW);
        digitalWrite(m[8], LOW);
      }
    }
  }
  delay(500);
  
}
