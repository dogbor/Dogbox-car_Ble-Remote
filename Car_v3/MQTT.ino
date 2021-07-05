////////////////MQTT///////////////////////

long MQTTConnectiondelay = 10000; //set delay time for MQTT connection serial print
unsigned long last_time2 = 0;

#include <PubSubClient.h>

#define MQTT_SERVER   "grouse.rmq.cloudamqp.com"  //"tailor.cloudmqtt.com"  //"swap.haupcar.com" 
#define MQTT_PORT    1883                  //12372                     // 8883
#define MQTT_USERNAME "mtyxzbba:mtyxzbba"                   //"admin"
#define MQTT_PASSWORD "U1q5CHj04esOup2NRxX3l_tE369gbR6D"                   //"haupcar2019"
#define MQTT_NAME     "ESPdogBoX02"

#define topicSubName  "/ESP32" //"Hydro/Control"  //smartALL/4287/20200511door1
#define topicPubName "smartALL/TEST/2020"

WiFiClient client;
PubSubClient mqtt(client);

String MQTTMessage = "";
int num =0;
  void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String topic_str = topic, payload_str = (char*)payload;
  Serial.println("[" + topic_str + "]: " + payload_str);
//  Serial.print("Sub Message: ");
//  Serial.println(payload_str);

///////////json input///////////
  MQTTMessage = payload_str;
}


void mqtt_setup() {
// Serial.begin(115200);
// WiFi.mode(WIFI_STA); 
// while (!Serial) ; 
//  delay(250);
//  Serial.println("WIFI_STA_NAME"); 

  Serial.println("WIFI Connecting");
//  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);    //เชื่อมต่อ wifi
 while (num<20) {
  delay(500);
  Serial.print(".");
  num++;
 }
 if (WiFi.status() == WL_CONNECTED) {
  Serial.print("\n WiFi Connected. \n");
 }else{
     Serial.print("\n WIFI Connect fail. ");   
  }
 mqtt.setServer(MQTT_SERVER, MQTT_PORT);
 mqtt.setCallback(callback);
}

void mqtt_loop() {
  if (mqtt.connected() == false) { 
    
//    Serial.print("MQTT connection... "); 
    if (mqtt.connect(MQTT_NAME, MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("MQTT Connected");
     mqtt.subscribe(topicSubName);
    }else{
      if ( millis() - last_time2 > MQTTConnectiondelay){
      Serial.println("Waiting for MQTT connection");
      last_time2 = millis();
     }
//   Serial.println("Waiting for MQTT connection"); //instead of above code^^
   delay(500);                                            ////////////////////////////delay////////////////////////////
  }
 }


  /////////////Publish Message///////
  /* 
 Serial.print("\n Publish message: ");
  if (mqtt.publish("test","Fuck Coach") == true)       //ส่งข้อความ "Arduino Test MQTT" ใน Topic = "TEST/MQTT"
  { 
   Serial.println("Success sending");     
  }
 */

  else{
    mqtt.loop();
  }
//  logic_MQTT();
  
}

//-------------------Logic MQTT--------------------------/// MQTTtoggle == 0 &&
/*
int MQTTtoggle =0;
void logic_MQTT() {
    if(  MQTTMessage == "open" ){
           if(digitalRead(D7)==HIGH){       //ถ้าประตูปิด
            ToggleD5delay = millis();
            ToggleD5 = true;
            mqtt.publish(topicPubName,"ControlRes: open");//clear mqtt and send status
           }
       
       MQTTMessage = "";
//      Serial.println("mqtt : open");
//      MQTTtoggle = 1;
    }
   
   if(  MQTTMessage == "close" ){
           if(digitalRead(D6)==HIGH){       //ถ้าประตูเปิด
            ToggleD5delay = millis();
            ToggleD5 = true;
            mqtt.publish(topicPubName,"ControlRes: close");//clear mqtt and send status
           }
       
       MQTTMessage = "";
//      Serial.println("mqtt : close");
//      MQTTtoggle = 0;
   }
}//end of logic mqtt loop
*/

//-------------------MQTT Connection Status--------------------------/// 
//
//unsigned long OnTime = 50000;           // milliseconds of on-time
//unsigned long previousMillis = 0;
//  
//  
//void ConnectStatus(){
//  unsigned long currentMillis = millis();
//  
//  if(currentMillis - previousMillis >= OnTime){
//    mqtt.publish(topicPubName,"status");
//    previousMillis = currentMillis;  // Remember the time
//    Serial.println("MQTT Status : <OK>");
//  }
//}
