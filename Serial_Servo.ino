//Đkhiển Servo bằng lệnh gửi qua Serial
//- SER XXX:
// xoay servo đến góc XXX


String data = "";

void servo(int angle = 0, long holdTime = 20){
  int delayTime = 11.111111*angle+500;
  for(int i = 0; i<=holdTime/20;i++){
    digitalWrite(5, 1);
    delayMicroseconds(delayTime);
    digitalWrite(5, 0);
    delay(10);
    delayMicroseconds(10000-delayTime); 
  }
}



void setup() {
  Serial.begin(9600);
  pinMode (5, OUTPUT);
  pinMode (2, INPUT);
}

void loop() {
  if(Serial.available() > 0){   //Nhận chuỗi 
    delay(10);
    data = Serial.readString();
    Serial.println(data);
  }

  if(data.indexOf("SER") == 0){     //Tạo cú pháp SER xxx 
    long string_value = (data.substring(4,4+3)).toInt(); // cắt gtri xxx từ chuỗi nhận được và biến thành kiểu số
    long value = map(string_value, 0, 180, 0, 1023);     //scale gtri từ 0->180 thành 0->1023
    Serial.println(string_value);

    servo(180*value/1023, 20);  
  }

  if(data.indexOf("LED") == 0){


    
    long moc = millis();
    
    long led_value = (data.substring(4,4+3)).toInt();
  
    digitalWrite(2, 1);
    
    while((millis()-moc)<(led_value*1000)){
      if(Serial.available() > 0){  
        delay(10);
        data = Serial.readString();
        Serial.println(data);
      }
      if(data.indexOf("SER") == 0){     
      long string_value = (data.substring(4,4+3)).toInt();
      long value = map(string_value, 0, 180, 0, 1023);  
      Serial.println(string_value);

      servo(180*value/1023, 20);  
      }
    }

    digitalWrite(2, 0);
    data="";
  }
}
