////////////////REMOTEXY///////////////////////
/*  
    To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.5.1 or later version;
     - for iOS 1.4.1 or later version;

*/


#define REMOTEXY_MODE__HARDSERIAL
#include <RemoteXY.h>

/////////////// RemoteXY configurate  //////////////////////////
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =  //project: Engine Start_V2
 { 255,2,0,7,0,15,1,10,28,5,
  2,0,9,50,22,11,0,2,26,31,
  31,224,185,128,224,184,155,224,184,180,
  224,184,148,0,224,184,155,224,184,180,
  224,184,148,0,1,0,38,46,19,19,
  0,2,31,224,184,170,224,184,149,224,
  184,178,224,184,163,224,185,140,224,184,
  151,0,65,20,43,31,7,7,0,129,
  0,12,21,44,4,0,35,224,184,163,
  224,184,176,224,184,154,224,184,154,224,
  185,132,224,184,159,32,32,32,32,32,
  32,32,32,32,224,185,128,224,184,132,
  224,184,163,224,184,183,224,185,136,224,
  184,173,224,184,135,224,184,162,224,184,
  153,224,184,149,224,185,140,0,65,22,
  15,31,7,7,0,68,17,5,76,55,
  19,0,8,36,131,1,4,1,55,6,
  1,26,16,68,79,71,66,79,88,0,
  129,0,41,8,19,2,0,26,80,111,
  119,101,114,101,100,32,98,121,32,100,
  111,103,66,111,88,0,129,0,5,73,
  19,2,0,26,224,185,129,224,184,163,
  224,184,135,224,184,148,224,184,177,224,
  184,153,224,185,129,224,184,154,224,184,
  149,224,185,128,224,184,149,224,184,173,
  224,184,163,224,184,181,224,185,136,32,
  40,224,185,130,224,184,167,224,184,165,
  224,184,149,224,185,140,41,0 };
    
struct {
    
  uint8_t SW_Power; // =1 if switch ON and =0 if OFF 
  uint8_t BU_EngStart; // =1 if button pressed, else =0 
  uint8_t LED_Engine_r; // =0..255 LED Red brightness 
  uint8_t LED_Power_r;
  uint8_t LED_Power_g;
  float onlineGraph_1;

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)




void Remotexy_setup() {
//remotexy

#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600
#define REMOTEXY_ACCESS_PASSWORD "1234"

//Serial.println("RemoteXY setup : <OK> ");

  RemoteXY_Init (); 

}

void Remotexy_loop() {
  RemoteXY_Handler ();
  
//เงื่อนไข รับค่าจากรีโมท และ แอป
  if(  oldstate ==0 && RemoteXY.SW_Power==1 && state==0){
    state = state+1;
    oldstate = 1;
  }
    if(  oldstate ==0 && RemoteXY.SW_Power==1 && state==1){
    state = state;
    oldstate = 1;
  }
  if(  oldstate ==1 && RemoteXY.SW_Power==0 && state==1){
   state = state+1;
     oldstate = 0;
  }
  if(  oldstate ==1 && RemoteXY.SW_Power==0 && state==0){
   state = state;
     oldstate = 0;
  }
////////////////////////
 
  if(  sw1state ==0 && digitalRead (PIN_SW1)==HIGH ){
   state = state+1;
     sw1state = 1;
  }
   if(  sw1state ==1 && digitalRead (PIN_SW1)==LOW ){
   state = state;
     sw1state = 0;
  } 

////////////////////////////////////
switch (state){
  case 1:
    digitalWrite(PIN_Power,HIGH);
        digitalWrite(PIN_Power2,HIGH);
    RemoteXY.LED_Power_g = 200;
    break;
  default:
      digitalWrite(PIN_Power,LOW);
            digitalWrite(PIN_Power2,LOW);
      RemoteXY.LED_Power_g = 0;
    state = 0;
  break;
}
//    RemoteXY.LED_Power_g = (digitalRead(PIN_PowerON)==HIGH)? 0:200 ; //LED for Power



//     Serial.print("Power >> oldstate: ");
//     Serial.print(oldstate);
//     Serial.print(", __state(Pin_Power): ");
//     Serial.print(state);                   //pin power
//     Serial.print(", __LED_Power_g: ");
//     Serial.println(RemoteXY.LED_Power_g);     //LED Power value


//Engine Start button
   digitalWrite(PIN_EngStart,(RemoteXY.BU_EngStart==1 || (digitalRead(PIN_SW2)==HIGH))?HIGH:LOW) ;


////Run another loop /// 
   

    delay (100);
  }

//////////////////////////runTaskBatt/////////////////////////////////
  //อ่าน V แบต
  void runTaskBatt(){
    A0read = analogRead(PIN_BattV);

    BattVolt = map(A0read, 0, 1023, 0, 18200);     //(input befor divider) Batt 0-15000mV (18810 for 4.7 kOmh and 1 kOmh)
    BattVolt = (BattVolt/1000);
    if(BattVolt >= 13){                         //mV   // 0.8v greater than actual
      RemoteXY.LED_Engine_r = 200;
    }else{
      RemoteXY.LED_Engine_r = 0;
    }
     RemoteXY.onlineGraph_1=BattVolt;
//     Serial.print("A0read: ");
//     Serial.print(A0read); 
//     Serial.print("BattVolt: ");
//     Serial.print(BattVolt); 
//     Serial.println(" V."); 
  }
  
//////////////////////////End/////////////////////////////////

////////////////////////// ConnectStatus/////////////////////////////////
  //LED Status
  void ConnectStatus(){
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();
  
  if((RemoteXY.LED_Power_r == 200) && (currentMillis - previousMillis >= OnTime)){
    RemoteXY.LED_Power_r = 0;  // Turn it off
    digitalWrite(PIN_BoardLED,LOW);
    previousMillis = currentMillis;  // Remember the time
  }
  else if ((RemoteXY.LED_Power_r == 0) && (currentMillis - previousMillis >= OffTime)){
    RemoteXY.LED_Power_r = 200;  // turn it on
    digitalWrite(PIN_BoardLED,HIGH);
    previousMillis = currentMillis;   // Remember the time
  }
//     Serial.print("LED Status:"); 
//     Serial.println(RemoteXY.LED_Power_r); 
}
