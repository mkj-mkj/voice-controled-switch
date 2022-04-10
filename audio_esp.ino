#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <WiFiClient.h>
#include <FirebaseESP8266.h>

SoftwareSerial NodeMCU(13, 15);


// Set WiFi credentials
#define WIFI_SSID "tp-link 5G"
#define WIFI_PASS "a6913227"

#define FIREBASE_HOST "test-65f38-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "SyRkl42JSx2oxX43xKvfKDPZmSjiTdEFl6AqIEdK"

FirebaseData firebaseData;
void printJsonObjectContent(FirebaseData &data);

void setup() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  NodeMCU.begin(115200);
  delay(10);
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  

  // Connected to WiFi
  Serial.println();
  Serial.println("Connected!");
  Serial.print("IP address for network ");
  Serial.print(WIFI_SSID);
  Serial.print(" : ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  // put your main code here, to run repeatedly:
  String path = "/finger"; //firebase 資料庫分頁名
  FirebaseJson json;
  
  String content = "";
  char character;
  while (NodeMCU.available()) {
    character = NodeMCU.read();
    content.concat(character);
    delay(0);
  }

  if(content == "on"){
    Serial.print(content);
    Serial.println("開燈");
    content = "";
    if (Firebase.setString(firebaseData, path + "/light1" , "turn on" )){
      Serial.println("開燈PASSED");
    }
    else{
      Serial.println("開燈 FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }
  else if(content == "off"){
    Serial.print(content);
    Serial.println("關燈");
    content = "";
    if (Firebase.setString(firebaseData, path + "/light1" , "turn off" )){
      Serial.println("關燈 PASSED");
    }
    else{
      Serial.println("關燈 FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }
  delay(1000);
}


//void printJsonObjectContent(FirebaseData &data) {
//  size_t tokenCount = data.jsonObject().parse(false).getJsonObjectIteratorCount();
//  String key;
//  String value;
//  FirebaseJsonObject jsonParseResult;
//  Serial.println();
//  for (size_t i = 0; i < tokenCount; i++){
//    data.jsonObject().jsonObjectiterator(i, key, value);
//    jsonParseResult = data.jsonObject().parseResult();
//    Serial.print("KEY: ");
//    Serial.print(key);
//    Serial.print(", ");
//    Serial.print("VALUE: ");
//    Serial.print(value);
//    Serial.print(", ");
//    Serial.print("TYPE: ");
//    Serial.println(jsonParseResult.type);
//  }
//}
