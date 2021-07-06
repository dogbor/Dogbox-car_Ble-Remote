////////////////REMOTEXY///////////////////////
/*  
    To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.5.1 or later version;
     - for iOS 1.4.1 or later version;

##project: 1 DoorControl_V2.2
*cloud server
*NodeMCU V3
*/


#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <RemoteXY.h>

/////////////// RemoteXY configurate  //////////////////////////
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,3,0,7,0,4,1,10,5,5,
  65,23,40,24,5,5,0,65,23,20,
  24,5,5,0,131,3,9,4,47,7,
  1,27,31,68,111,111,114,32,67,111,
  110,116,114,111,108,0,129,0,39,18,
  7,5,0,16,224,184,155,224,184,180,
  224,184,148,0,2,0,16,67,32,15,
  0,2,26,31,31,67,76,79,83,69,
  0,79,80,69,78,0,1,0,16,46,
  11,11,0,2,16,224,185,128,224,184,
  155,224,184,180,224,184,148,47,224,184,
  155,224,184,180,224,184,148,0,1,0,
  37,46,11,11,0,2,16,65,117,116,
  111,0,129,0,19,18,9,5,0,16,
  224,185,128,224,184,155,224,184,180,224,
  184,148,0,129,0,13,40,13,4,0,
  16,84,111,103,103,108,101,0,129,0,
  30,41,28,3,0,16,79,112,101,110,
  32,62,32,65,117,116,111,32,67,108,
  111,115,101,0,129,0,25,97,35,2,
  0,26,100,111,111,114,32,99,111,110,
  116,114,111,108,32,118,50,46,50,95,
  80,111,119,101,114,101,100,32,98,121,
  32,100,111,103,66,111,88,0,129,0,
  40,94,10,2,0,26,87,105,70,105,
  32,83,105,103,110,97,108,0,66,128,
  51,92,9,4,0,13,26 };
    
struct {
    // input variables
  uint8_t SW1; // =1 if switch ON and =0 if OFF     //Open or close
  uint8_t BUT1; // =1 if button pressed, else =0    //Open/close
  uint8_t BUT2; // =1 if button pressed, else =0    //Auto

    // output variables
  uint8_t led_c_r; // =0..255 LED Red brightness 
  uint8_t led_c_g; // =0..255 LED Green brightness 
  uint8_t led_c_b; // =0..255 LED Blue brightness 
  uint8_t led_o_r; // =0..255 LED Red brightness 
  uint8_t led_o_g; // =0..255 LED Green brightness 
  uint8_t led_o_b; // =0..255 LED Blue brightness 
  int8_t WifiPerc; // =0..100 level position 
    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)




void Remotexy_setup() {
//remotexy
#define REMOTEXY_WIFI_SSID (con_ssid) //animalclinic_2.4G
#define REMOTEXY_WIFI_PASSWORD (con_psk) //49855151
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "2c49a4f6c1bb995e3d7cee0287188dbd" //-- Project: DoorControl_V1_testing --
#define REMOTEXY_ACCESS_PASSWORD "4938"  //set passwoard
Serial.println("RemoteXY setup : <OK> ");

  RemoteXY_Init (); 

}

void Remotexy_loop() {
  RemoteXY_Handler ();

//    RemoteXY.WifiPerc = (dBmtoPercentage(WiFi.RSSI()));
//  Serial.println("RemoteXY_loop");

//  RemoteXY.WifiPerc = WifiPerc1 ;
  
//  if (RemoteXY.BUT1==1 ) {
//    digitalWrite(D5,LOW);
//    delay(500);
//  }
//  if (RemoteXY.BUT1==0 ) {
//    digitalWrite(D5,HIGH);   
//  }



  
//digitalWrite(BUT1,(RemoteXY.BUT1==1 )?LOW:HIGH) ;

////-------------------Button RemoteXY--------------------------// 
//  if(  state==0 && RemoteXY.b_move==1){
//    state = 1;
//        drivestate = true;
//    startedWaiting = millis();
//    mqtt.publish(topicPubName,"move");
//    Serial.println("RemoteXY:MOVE");
//     sw1state = 1;
//  }
//   if(  state ==1 && RemoteXY.b_stop==1 ){
//      state = 0;
//      mqtt.publish(topicPubName,"stop");
//      Serial.println("RemoteXY:STOP");
//      sw1state = 0;
//  }
////-------------------End Button RemoteXY--------------------------// 
//
//if(state==1){
//      RemoteXY.led_1_r = 0;
//    RemoteXY.led_1_g = 200;
//}
//
//if(state==0){
//        RemoteXY.led_1_g = 0;
//      RemoteXY.led_1_r = 200;
//}



}
