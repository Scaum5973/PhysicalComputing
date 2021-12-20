#include<Servo.h>

#define PIN_SERVO1 8
#define PIN_SERVO2 7
#define PIN_SERVO3 6 //전후 이동 서보모터

Servo servo1,servo2, servo3;

int pos; //서보모터 각도 설정
int cm; //거리 설정

void setup()
{
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);
  servo3.attach(PIN_SERVO3); //서보모터 연결

  Serial.begin(9600);
}

//초음파 거리 센서 코드
long readUltrasonicDistance(int triggerPin, int echoPin){
  pinMode(triggerPin, OUTPUT); //clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  //sets the trigger pin tp HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  //Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);

}

//임시 트랙킹 코드
long trackingHand(){
  int pos;
  
  for (pos = 10; pos <= 170;){
    pos += 5 ;
    servo1.write(pos);
    servo2.write(pos);
    delay(20);
  }
  
  for (pos = 170; pos >= 10;){
    pos -= 5;
    servo2.write(pos);
    servo1.write(pos);
    delay(20);
  }
  Serial.println("Tracking the hand.");
}

//거리에 따른 전후 움직이는 코드
long movingForwardBackward(){
    if(pos == 180){
    pos -= 10;
  }
  
  for (pos > 0; pos < 180;){
    if(cm <= 10) {
      pos += 10;
    }
    else {
      pos -= 10;
    }
    
    delay(10);
    break;
  }
  servo3.write(pos);
}

void loop()
{
  cm = 0.01723*readUltrasonicDistance(12, 13);
  Serial.print(cm);
  Serial.println("cm");
  
  movingForwardBackward();
  
//  trackingHand();
}
