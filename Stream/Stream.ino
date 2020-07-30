
#include <SoftwareSerial.h>//와이파이 통신

#include "FirebaseESP8266.h" //파이어베이스 사용
#include <ESP8266WiFi.h> //와이파이 사용


//와이파이와 파이어베이스 연동
#define FIREBASE_HOST "FIREBASE_HOST" 
#define FIREBASE_AUTH "FIREBASE_AUTH" 
#define WIFI_SSID "WIFI ID" 
#define WIFI_PASSWORD "WIFI password"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJson json;

SoftwareSerial s(D6,D5); // (Rx, Tx) //와이파이 통신

void printResult(FirebaseData &data);

void setup()
{

  Serial.begin(9600);
  s.begin(9600); 
  //와이파이 연결
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

 //파이어베이스 연결
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //와이파이와 아두이노 연결 : https://www.youtube.com/watch?v=SiU-QZwik8w
  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */

  String path = "/testBucket/WIFIControl";
  

  Serial.println("------------------------------------");
  Serial.println("Get double test...");


    //Also can use Firebase.get instead of Firebase.setInt
    if (Firebase.getString(firebaseData, path))
    {
      Serial.print("WIFIControl VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();
      
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }


}

void printResult(FirebaseData &data)
{
    if (data.dataType() == "int")
        Serial.println(data.intData());
    else if (data.dataType() == "float")
        Serial.println(data.floatData(), 5);
    else if (data.dataType() == "double")
        printf("%.9lf\n", data.doubleData());
    else if (data.dataType() == "boolean")
        Serial.println(data.boolData() == 1 ? "true" : "false");
    else if (data.dataType() == "string")
    {   
        int a;
        a = data.stringData().toInt();
        s.write(a);//a.toInt()
        Serial.print("a int:");
        Serial.println(a);
        Serial.println(data.stringData());
    }
    
}

void loop()
{ 
  String path = "/testBucket/WIFIControl";//경로
  delay(5000);
  if (Firebase.getString(firebaseData, path))
    {
      Serial.print("WIFIControl VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();   
    }
  else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }

}
