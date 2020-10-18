#include <FirebaseESP32.h>  
#include <WiFi.h>              
#include "DHT.h"

#define FIREBASE_HOST "xxx.firebaseio.com"      // Project name address from firebase id
#define FIREBASE_AUTH "xxx"            //  Secret key generated from firebase

#define WIFI_SSID "Guest Wifi"                                     // Enter your wifi name
#define WIFI_PASSWORD "shuvopodder"                  //Enter your wifi password

FirebaseData firebaseData;

#define DHTPIN 23  
                                                       // Digital pin connected to DHT11
#define DHTTYPE DHT11                                                       // Initialize dht type as DHT 11
DHT dht(DHTPIN, DHTTYPE);                                                    

void setup() {

  Serial.begin(115200);

  delay(500);               

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  

  Serial.print("Connecting to ");

  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

  Serial.println();

  Serial.print("Connected to ");

  Serial.println(WIFI_SSID);

  Serial.print("IP Address is : ");

  Serial.println(WiFi.localIP());                               // Will print local IP address

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);             // connect to firebase

  Firebase.reconnectWiFi(true);//*******************
  dht.begin();                                        //Start reading dht sensor

}


void loop() {

  float h = dht.readHumidity();                                 // Reading Humidity
  float t = dht.readTemperature();                           // Read temperature as Celsius
   
  if (isnan(h) || isnan(t)) {                                                // Check if any reads failed.
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h);                                         //convert integer humidity to string humidit
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("Â°C ");
  String fireTemp = String(t);                                                     //convert integer temperature to string temperature
  delay(4000);


    //Firebase.pushString(firebaseData,"Data/Humidity", fireHumid);                                  //setup path and send readings
    //Firebase.pushString(firebaseData, "Data/Temperature", fireTemp);                                //setup path and send readings
    Firebase.setFloat(firebaseData,"test2/Humidity",h);
    Firebase.setFloat(firebaseData,"test2/Temperature",t);
    Serial.println("Successful");

}
