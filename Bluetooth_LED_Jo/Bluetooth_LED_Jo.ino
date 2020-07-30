#include <LiquidCrystal.h>
#include <Servo.h>  //서보모터 사용

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Servo servo;

  int LLED = 10; //전등
  int BLED = 12; //보일러
  int ALED = 8; //에어컨
  int a = 13;
  
  #include<Wire.h>
  #define SLAVE 4

  int servoPin = 11;

  #include <SoftwareSerial.h>
  SoftwareSerial s(5,6);
  //String datad = "h";
  String inputs ="";
  
  int count_WiFi = 0;
  int WIFI_set = 0;

  // 소프트웨어 4 SPI 사용
#define OLED_MOSI  2    // D1
#define OLED_CLK   3   // D0
#define OLED_DC    4
#define OLED_CS    7
#define OLED_RESET 9

// OLED 디스플레이 선언
//Adafruit_SSD1306 //(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

  void setup()
  {
    pinMode(LLED, OUTPUT);   
    pinMode(BLED, OUTPUT);   
    pinMode(ALED, OUTPUT);   
    s.begin(9600);

    servo.attach(servoPin);
    servo.write(90);//초기 서보모터 각도
    servo.detach();
    
    Wire.begin(); //Wire 라이브러리 초기화
    Serial.begin(9600); //직렬 통신 초기화

    // OLED 초기화                
  //.begin(SSD1306_SWITCHCAPVCC);
  //.setTextColor(WHITE);
  //.setTextSize(1);
  
  // 저전력을 위해 OLED 밝기 조정
  //.ssd1306_command(SSD1306_SETCONTRAST);
  //.ssd1306_command(0);
  
  }
  String doit = "";
  int doit_count = 1;
  String doit_check = "";
  void loop()
  {
    Wire.requestFrom(SLAVE, 1); //1 바이트 크기의 데이터 요청
    if ( s.available ( ) > 0 ) 
      {
        char a;
        String datad = "";
        String datads = "";
        //datad += s.read();
        a = s.read();
        datad += a;

        if (datad != "0" | datad != "1" | datad != "2" | datad != "3" | datad != "4" | datad != "5" | datad != "9" | datad != "12" | datad != "15")
        {
          if (datad.equals(","))
          {
            doit_count = 0;
          }
          
          if(doit_count == 1)
          {
            doit += a;
            Serial.print("doit: ");
            Serial.println(doit);
            Serial.print("count : ");
            Serial.println(doit_count);
          }
          // ex) text, 일경우 text까지 값을 읽어 doit에 저장한다.

          if(doit_count == 0)
          {
              doit_check += a; //새로운값 저장

              if (datad.equals(",")) // 새로운 값이 , 을 만나면 실행
              {
                if(!doit.Equals(doit_check)) // 기존 doit 값과 새로운 값 doit_check를 검사하여서 서로 다른값이면 실행
                {
                  doit_count = 1;
                  
                }
              }
          }
         }
          

          
         }
        else
        {
          datads += a;
          Serial.print("datad: ");
          Serial.println(datads);
          WIFI_set += 1;
          Serial.print("WIFI");
          Serial.println(WIFI_set);
          input_check(datads);
          WIFI_set = 0;
         }      
      } 

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(0,0);             // Start at top-left corner
        //.print(F(doit));
        delay(4000);
        //.//();
      
      com();                                                          
      delay(1000);

  }

  void com()//우노끼리 통신
  {
    
    String input = "";
    //시리얼 통신으로 문자를 입력받기 위한 준비
    input += (char) Wire.read();//한번에 한문자를 읽으면
   
    Serial.print("input: \n");
    Serial.print(input);   

    if (input == "2"){
      Serial.print("여기 도착했지?????");
      sound_on();
      input = "";    
    }
    else if (input == "6"){
      Serial.print("여기 도착했지?????");
      sound_off();
      input = "";    
    }     
    else{
      input_check(input);
    }
  }
  
    
  void input_check(String input){//WIFI값 받아와서 제어
    Serial.println(WIFI_set);
    Serial.println(input);
    Serial.println(count_WiFi);
    if (WIFI_set == 1 & input == "2" & count_WiFi == 0){
          Serial.print("여기 도착했어?");
          sound_on();
          input = "";
          count_WiFi++;      
    }
    else if (WIFI_set == 1 & input == "6" & count_WiFi == 1){
        sound_off();
        input = "";
        count_WiFi = 0;
      }
      
    else if (input == "3")
    {
        digitalWrite(LLED, HIGH);
        Serial.print("전등 ON \n");
          
        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(37,0);             // Start at top-left corner
        //.print(F("LIGHT"));
        //.setCursor(55,17); 
        //.print(F("ON"));
        //.//();
        delay(4000);

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(5,0);             // Start at top-left corner
        //.print("SMART HOME    IOT");
        //.//();
        

    }
  
    else if (input == "4")
    {
        digitalWrite(BLED, HIGH);
        Serial.print("보일러 ON \n");

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(32,0);             // Start at top-left corner
        //.print(F("BOILER"));
        //.setCursor(55,17); 
        //.print(F("ON"));
        //.//();
        delay(4000);

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(5,0);             // Start at top-left corner
        //.print("SMART HOME    IOT");
        //.//();

    }
  
  else if (input == "5")
    {
        digitalWrite(ALED, HIGH);
        Serial.print("에어컨 ON \n");

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(10,0);             // Start at top-left corner
        //.print(F("AIR"));

        //.setTextSize(1);
        //.setCursor(60,0);  
        //.print(F("conditioner"));

        //.setTextSize(2);
        //.setCursor(55,17); 
        //.print(F("ON"));
        //.//();
        delay(4000);

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(5,0);             // Start at top-left corner
        //.print("SMART HOME    IOT");
        //.//();

    }
  
    else if (input == "9")
    {
        digitalWrite(LLED, LOW);
        Serial.print("전등 OFF \n");

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(38,0);             // Start at top-left corner
        //.print(F("LIGHT"));
        //.setCursor(50,17); 
        //.print(F("OFF"));
        //.//();
        delay(4000);

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(5,0);             // Start at top-left corner
        //.print("SMART HOME    IOT");
        //.//();
    }
    
  
    else if (input == "0" | input == "12")
    {
        digitalWrite(BLED, LOW);
        Serial.print("보일러 OFF \n");

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(32,0);             // Start at top-left corner
        //.print(F("BOILER"));
        //.setCursor(50,17); 
        //.print(F("OFF"));
        //.//();
        delay(4000);

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(5,0);             // Start at top-left corner
        //.print("SMART HOME    IOT");
        //.//();

    }
    
    else if (input == "1" | input == "15")
    {
        digitalWrite(ALED, LOW);
        Serial.print("에어컨 OFF \n");

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(10,0);             // Start at top-left corner
        //.print(F("AIR"));

        //.setTextSize(1);
        //.setCursor(60,0);  
        //.print(F("conditioner"));

        //.setTextSize(2);
        //.setCursor(50,17); 
        //.print(F("OFF"));
        //.//();
        delay(4000);

        //.clear//();
        //.setTextSize(2);             // Normal 1:1 pixel scale
        //.setTextColor(SSD1306_WHITE);        // Draw white text
        //.setCursor(5,0);             // Start at top-left corner
        //.print("SMART HOME    IOT");
        //.//();
    }
  
      //마스터 우노
    else // node mcu에서 가져온 값
    {
        Serial.print("node mcu가 보낸값 :"); //
        Serial.println(input); //node mcu에서 전송한 할일 텍스트 출력
     }
 
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
    
