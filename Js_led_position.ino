//ban đầu led đầu tiên sáng
//JS lên thì led ở trên sáng
//JS xuống thì led ở dưới sáng

//JS lên = 0
//JS xuống = 1017
//JS giữa = ~495

//JS trái tăng độ sáng 10%, tối đa 100%
//JS phải giảm độ sáng 10%, tối đa 0%

//JS trái = 251
//JS phải = 0
//JS giữa = 125

int pos = 7;  //vị trí hiện tại led sáng

int buf = 0;  //bộ nhớ đệm cho vị trí

signed long dosang=255;

void setup() {
  Serial.begin(9600);
  pinMode(A5, INPUT);
  pinMode(A0, INPUT);
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  
  digitalWrite(pos, HIGH);

  buf = pos;
}

void loop() {
  long numY = analogRead(A5);


  int numX = map(analogRead(A0), 0, 1023, 0, 255); //scale gtri từ 0->1023 thành 0->255
  
  //Serial.println(numX);
  
  if(numY<100){
    
    pos++;
    if(pos > 7)
      pos=2;

    if(pos!=buf){     //nếu vị trí thay đổi thì tắt led đang sáng và bật led kế tiếp
      digitalWrite(buf, LOW);
      analogWrite(pos, dosang);
      buf = pos;
    }
    
    while(numY<100){numY = analogRead(A5);delay(100);}; //chờ buông chống dội
    
  }

  if(numY>900){
    
    pos--;
    if(pos < 2)
      pos=7;

    if(pos!=buf){     //nếu vị trí thay đổi thì tắt led đang sáng và bật led kế tiếp
      digitalWrite(buf, LOW);
      analogWrite(pos, dosang);
      buf = pos;
    }
    
    while(numY>900){numY = analogRead(A5);delay(100);};
  }

  if(numX > 250){
    dosang += (255*10)/100;   //+10%

    if( dosang >255)
      dosang = 255;
    Serial.println(dosang);
    analogWrite(pos, dosang);

    while(numX > 250){numX = map(analogRead(A0), 0, 1023, 0, 255);delay(100);};
  }


  if(numX < 10){
    dosang -= (255*10)/100;   //-10%

    if(dosang < 0)
      dosang = 0;
    Serial.println(dosang);
    analogWrite(pos, dosang);

    while(numX < 10){numX = map(analogRead(A0), 0, 1023, 0, 255);delay(100);};
  }

 
}
