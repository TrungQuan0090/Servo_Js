// code thầy cho mẫu 

void setup() {
  Serial.begin(9600);
  pinMode(A5, INPUT);
 

}

void ser(int servoPin, int angle=0, long holdTime=20){
  pinMode(servoPin, OUTPUT);
  
  int delayTime = 11.111111*angle+500;
  for(int i = 0; i<=holdTime/20;i++){
    digitalWrite(servoPin, 1);
    delayMicroseconds(delayTime);
    digitalWrite(servoPin, 0);
    delay(10);
    delayMicroseconds(1000-delayTime);
  }
}

void loop() {
  long gia_tri = analogRead(A5);
  ser(5,(180*gia_tri/1023),2);

}
