#include <Servo.h>

//적외선 감지 상태
int state_1 = 1;
int state_2 = 1;
int state_3 = 1;

//적외선 핀 설정
int infrared_1 = 34;
int infrared_2 = 35;
int infrared_3 = 36;

//DC모터 핀 설정
int DC_en_1 = 2;
int DC_l_1 = 22;
int DC_r_1 = 24;

int DC_en_2 = 3;
int DC_l_2 = 23;
int DC_r_2 = 25;

int DC_en_3 = 4;
int DC_l_3 = 26;
int DC_r_3 = 28;

int DC_en_4 = 5;
int DC_l_4 = 27;
int DC_r_4 = 29;

//Servo모터 핀 설정
//int servoPin_1 = 7;
//int servoPin_2 = 8;
//int servoPin_3 = 9;
int direct_servo = 7;

//Servo모터가 돌아가는 각도
int angle = 0;

int direct_angle[3] = {60, 135, 180};

//Servo 객체 생성
//Servo servo_1;
//Servo servo_2;
//Servo servo_3;
Servo direct;

void setup() {
  // put your setup code here, to run once

  //Serial 통신 초기화
  Serial.begin(9600);
  Serial1.begin(9600); 

  //servo모터 attach
  //servo_1.attach(servoPin_1);
  //servo_2.attach(servoPin_2);
  //servo_3.attach(servoPin_3);
  direct.attach(direct_servo);
  
  //DC모터 핀모드 설정
  pinMode(DC_l_1, OUTPUT);
  pinMode(DC_r_1, OUTPUT);
  
  pinMode(DC_l_2, OUTPUT);
  pinMode(DC_r_2, OUTPUT);
  
  pinMode(DC_l_3, OUTPUT);
  pinMode(DC_r_3, OUTPUT);
  
  pinMode(DC_l_4, OUTPUT);
  pinMode(DC_r_4, OUTPUT);
  

  //DC모터 회전방향 설정
  digitalWrite(DC_l_1, HIGH);
  digitalWrite(DC_r_1, LOW);
  
  digitalWrite(DC_l_2, HIGH);
  digitalWrite(DC_r_2, LOW);
  
  digitalWrite(DC_l_3, HIGH);
  digitalWrite(DC_r_3, LOW);
  
  digitalWrite(DC_l_4, HIGH);
  digitalWrite(DC_r_4, LOW);

  //일단 약통문을 모두 닫아두기
  //servo_1.write(angle);
  //servo_2.write(angle);
  //servo_3.write(angle);
  direct.write(angle);
}

//Serial 통신으로 문자열을 한번에 받기 위한 함수
String readSerial()
{
  String str = "";
  char ch;

  while(Serial.available() > 0)
  {
    ch = Serial.read();
    str.concat(ch);
    delay(10);
  }

  return str;
}

/*
void cell_A(int n) {
  if(n==0) return;
  
  // 1번 약통 --------------------------------------------------
  // 감지가 될 때 까지 DC 모터를 돌린다.
  while(state_1 == 1) {
    analogWrite(DC_en_1, 100);

    servo_1.write(angle);
            
    state_1 = digitalRead(infrared_1);
  }
  // 감지가 되면 감지가 안될 때 까지 DC 모터를 멈추고 Servo 모터로 문을 연다.
  while(state_1 == 0) {
    analogWrite(DC_en_1, 0);

    angle = 90;
    servo_1.write(angle);
    angle = 0;

    state_1 = digitalRead(infrared_1);
  }
  //감지가 안되는 것이 확인되면 Servo모터로 문을 닫는다.
  servo_1.write(angle);
  // ------------------------------------------------------------

  cell_A(n-1);
}

void cell_B(int n) {
  if(n==0) return;
  
  // 2번 약통 --------------------------------------------------
  // 감지가 될 때 까지 DC 모터를 돌린다.
  while(state_2 == 1) {
    analogWrite(DC_en_2, 100);

    servo_2.write(angle);
            
    state_2 = digitalRead(infrared_2);
  }
  // 감지가 되면 감지가 안될 때 까지 DC 모터를 멈추고 Servo 모터로 문을 연다.
  while(state_2 == 0) {
    analogWrite(DC_en_2, 0);

    angle = 90;
    servo_2.write(angle);
    angle = 0;.l.

    state_2 = digitalRead(infrared_2);
  }
  //감지가 안되는 것이 확인되면 Servo모터로 문을 닫는다.
  servo_2.write(angle);
  // ------------------------------------------------------------

  cell_B(n-1);
}

void cell_C(int n) {
  if(n==0) return;
  
  // 3번 약통 --------------------------------------------------
  // 감지가 될 때 까지 DC 모터를 돌린다.
  while(state_3 == 1) {
    analogWrite(DC_en_3, 100);
    analogWrite(DC_en_4, 200);

    servo_3.write(angle);
            
    state_3 = digitalRead(infrared_1);
  }
  // 감지가 되면 감지가 안될 때 까지 DC 모터를 멈추고 Servo 모터로 문을 연다.
  while(state_3 == 0) {
    analogWrite(DC_en_3, 0);
    analogWrite(DC_en_4, 0);

    angle = 90;
    servo_3.write(angle);
    angle = 0;

    state_3 = digitalRead(infrared_3);
  }
  //감지가 안되는 것이 확인되면 Servo모터로 문을 닫는다.
  servo_3.write(angle);
  // ------------------------------------------------------------

  cell_C(n-1);
}
*/



void loop() {
  // put your main code here, to run repeatedly:
  String str="";
  if(Serial1.available()>0){
    str = Serial1.readString();
    Serial.println(str);
  }
  
  if(str == "");

  else {
    for(int i=0;i<9;i=i+3) {
      int a, b, c;

      a = int(str[i]-'0');
      Serial.print("1번 약통에서 ");
      Serial.print(a);
      Serial.println("개 추출됩니다.");
      
      b = int(str[i+1]-'0');
      Serial.print("2번 약통에서 ");
      Serial.print(b);
      Serial.println("개 추출됩니다.");
      
      c = int(str[i+2]-'0');
      Serial.print("조제약이 ");
      Serial.print(c);
      Serial.println("개 추출됩니다.");

      //direct.write(direct_angle[i/3]);
      
      Serial.println("1번 약통의 약을 추출합니다.");
      for(int j=0;j<a;j++) {
        // 1번 약통 --------------------------------------------------
        // 감지가 될 때 까지 DC 모터를 돌린다.
        while(state_1 == 1) {
          analogWrite(DC_en_1, 70);

          //servo_1.write(angle);
            
          state_1 = digitalRead(infrared_1);
        }
        // 감지가 되면 감지가 안될 때 까지 DC 모터를 멈추고 Servo 모터로 문을 연다.
        while(state_1 == 0) {
          analogWrite(DC_en_1, 0);

          //angle = 90;
          //servo_1.write(angle);
          //angle = 0;

          state_1 = digitalRead(infrared_1);
        }
        //감지가 안되는 것이 확인되면 Servo모터로 문을 닫는다.
        //servo_1.write(angle);
        // ------------------------------------------------------------
      }
      //cell_A(a);
      
      Serial.println("2번 약통의 약을 추출합니다.");
      for(int j=0;j<b;j++) {
        // 2번 약통 --------------------------------------------------
        // 감지가 될 때 까지 DC 모터를 돌린다.
        while(state_2 == 1) {
          analogWrite(DC_en_2, 70);

          //servo_2.write(angle);
            
          state_2 = digitalRead(infrared_2);
        }
        // 감지가 되면 감지가 안될 때 까지 DC 모터를 멈추고 Servo 모터로 문을 연다.
        while(state_2 == 0) {
          analogWrite(DC_en_2, 0);

          //angle = 90;
          //servo_2.write(angle);
          //angle = 0;

          state_2 = digitalRead(infrared_2);
        }
        //감지가 안되는 것이 확인되면 Servo모터로 문을 닫는다.
        //servo_2.write(angle);
        // ------------------------------------------------------------
      }
      //cell_B(b);
      
      delay(2000);
      //cell_C(c);
    }
  }
}
