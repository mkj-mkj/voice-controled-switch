#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <FirebaseESP8266.h>
#include <Servo.h>

Servo myservo;

int pos = 90;
String content;

// 設定網路基地台SSID跟密碼
const char* ssid      = "tp-link 5G";
const char* password  = "a6913227";

#define FIREBASE_HOST "test-65f38-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "SyRkl42JSx2oxX43xKvfKDPZmSjiTdEFl6AqIEdK"

FirebaseData firebaseData;
void printJsonObjectContent(FirebaseData &data);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
  myservo.attach(2);
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting To: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // 等待連線，並從 Console顯示 IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  Firebase.enableClassicRequest(firebaseData, true);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  String path = "/finger";
  FirebaseJson json;
  
  
  
  if (Firebase.getString(firebaseData, path + "/light1"))
  {
    Serial.println(firebaseData.stringData());
    content = firebaseData.stringData();

    Serial.println("------------------------------------");
    Serial.println();
    if(content=="turn on")
    {
      Serial.println(content);
      for(pos = 90; pos <= 150; pos += 1){
        myservo.write(pos);
      }
      delay(500);
      while(pos > 90){
        pos -= 1;
        myservo.write(pos);
        delay(15);
      }
      if (Firebase.setString(firebaseData, path + "/light1" , "0" )){
      Serial.println("0PASSED");
      }
      else{
      Serial.println("0 FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
      }
    }
    
    else if(content=="turn off")
    {
      Serial.println(content);
      for(pos = 90; pos >= 30; pos -= 1){
        myservo.write(pos);
      }
      delay(500);
      while(pos <= 90){
        pos += 1;
        myservo.write(pos);
        delay(15);
      }
      if (Firebase.setString(firebaseData, path + "/light1" , "0" )){
        Serial.println("0PASSED");
      }
      else{
        Serial.println("0 FAILED");
        Serial.println("REASON: " + firebaseData.errorReason());
        Serial.println("------------------------------------");
        Serial.println();
      }
     }

  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
  delay(2000);
}
