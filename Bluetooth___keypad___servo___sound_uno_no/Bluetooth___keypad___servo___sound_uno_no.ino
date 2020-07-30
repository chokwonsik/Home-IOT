
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Servo.h>  //서보모터 사용
#include <Keypad.h> //키패드 사용
#include<Wire.h>

#define SLAVE 4 // 우노끼리 통신하여 데이터 값 보낼 때 사용
SoftwareSerial s(0,1);


Servo servo;

int servoPin = 11;
int angle = 0; // 서보모터 각도 (servo position in degrees )
int trues = 0; // 값이 일치하는지 확인하기 위한 변수
int count = 0; // 몇번 입력했는지 Count하기 위한 변수


char pw[4] = {'1','2','3','4'};//현관문 비밀번호

const byte ROWS = 4;
const byte COLS = 4;
byte rowpins[ROWS] = {9,8,7,6};
byte colpins[COLS] = {5,4,3,2};
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'} 
};

//Keypad 사용
//Keypad keypad = Keypad( makeKeymap(keys), rowpins, colpins, ROWS, COLS);
SoftwareSerial BTSerial(12, 10);   
String datas = "";
  
  void setup() { 
    
    Wire.begin(SLAVE);//우노끼리 통신
    s.begin(9600);  

    Serial.begin(9600);
    BTSerial.begin(9600);//블루투스
  
 
    pinMode(5,OUTPUT);//부저 사용 핀
    
    Wire.onRequest(control); //값을 서로 다른 우노로 통신하여 보냄
    //https://increase-life.tistory.com/41  
  }



  void loop() 
  {  
//    keypad_sound();
    
    if (BTSerial.available())
    { 
      // 블루투스로 보낸 값이 있을때 실행
      // data에 저장해 Serial에 출력
      char data = BTSerial.read();
      datas = datas + data;
      Serial.write(data); 
      Serial.print(datas); //datas값을 시리얼 모니터에 출력
    }  
    
    if (Serial.available())
    {
    //시리얼을 통해 수신된 것이 있다면
      BTSerial.write(Serial.read()); // 시리얼에 있는 값을 읽어 블루투스에 전달
    }       
    
     
  }



  void control()
  {
    
    // 우노끼리 통신할 때 값 전달
    if(datas == "2"){//현관문
      Serial.print("왓어");
      Wire.write("2");
      datas = "";
    }
    
    if(datas == "6"){//현관문
      Serial.print("왓어");
      Wire.write("6");
      datas = "";
    }

    if(datas == "3"){//전등 ON
      Serial.print("왓어");
      Wire.write("3");
      datas = "";
    }
    
    if(datas == "4"){//보일러 ON
      Wire.write("4");
      datas = "";
      }
      
    if(datas == "5"){//에어컨 ON
      Wire.write("5");
      datas = "";
    }
  
    if(datas == "9"){//전등 OFF
        Wire.write("9");
        datas = "";
    }
    if(datas == "12"){//보일러 OFF
        Wire.write("0");
        datas = "";
    }
    if(datas == "15"){//에어컨 OFF
      Wire.write("1");
      datas = "";
    } 
  }


  void keypad_sound(){//키패드 사운드
    char key = keypad.getKey();
    
    if (key){
      Serial.println(key);
        if(key == pw[count]){
          count++;
          trues++;
          if(count==4)
          {
            datas = "2";
          }
          else{

            }
        }
        else{
          count++;
          }
      if(key == '#'){//값 초기화
        trues = 0;
        count = 0;
        }
        
      if(count > 4){ //비밀번호를 틀렸을때 삐삐삐삐
        delay(500);
        for(int i =0; i<10; i++){
            tone(13,589.6); delay(50); noTone(13); delay(100);
        }
  
        //값 초기화  
        trues = 0;
        count = 0;
      }
    }  
  }

/*
  void sound(){//사운드
      
      sound_on();
      
      delay(5000); 
      
      sound_off();
      count = 0;//값 초기화
      trues = 0; 
  }

  void sound_on(){//door sound on
      servo.attach(servoPin);
      servo.write(0);
      tone(13,829.6); delay(100); noTone(13); delay(100);
      tone(13,849.6); delay(100); noTone(13); delay(100);
      tone(13,869.6); delay(100); noTone(13); delay(100);
      tone(13,909.6); delay(100); noTone(13); delay(100);
      servo.detach();
    }

  
  void sound_off(){//door sound off
      servo.attach(servoPin);
      servo.write(90);
      tone(13,909.6); delay(100); noTone(13); delay(100);
      tone(13,869.6); delay(100); noTone(13); delay(100);
      tone(13,549.6); delay(100); noTone(13); delay(100);
      tone(13,529.6); delay(100); noTone(13); delay(100); 
      servo.detach(); 
    }
*/

 /*//master -> slave
 int greenLED = 13; //13번핀에 초록색 LED

  #include<Wire.h>
  #define SLAVE 4

  void setup(){
  
  pinMode(greenLED, OUTPUT); 
      
  Wire.begin();
  
  Serial.begin(9600);
  }

  void loop(){
  com();
  delay(1000);
  }
  void com(){
  Wire.requestFrom(SLAVE, 1);
  char c = Wire.read();
  
  if (c == 3){
      digitalWrite(greenLED, HIGH);
    }
  }
*/
