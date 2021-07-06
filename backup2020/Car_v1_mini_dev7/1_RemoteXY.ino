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
  currentMillis = millis();
//เงื่อนไข รับค่าจากรีโมท และ แอป

///////// RemoteXY on  ///////////////
  if(  oldstate ==0 && RemoteXY.SW_Power==1){
    onstate = 1;
    oldstate = 1;
LastStateMillis = currentMillis; //sleep mode
  }

  if(  oldstate ==1 && RemoteXY.SW_Power==0){
   onstate = 0;
     oldstate = 0;
     LastStateMillis = currentMillis;//sleep mode

  }
  
///////// Remote RF on Toggle ///////////////
   if(  sw1state ==0 && digitalRead (PIN_SW1)==HIGH ){
   onstate = onstate+1;
   LastStateMillis = currentMillis;//sleep mode
  Seatopen = 1;
     sw1state = 1;

  }
   if(  sw1state ==1 && digitalRead (PIN_SW1)==LOW ){
   onstate = onstate;
   LastStateMillis = currentMillis;//sleep mode
     Seatopen = 0;
     sw1state = 0;

  } 

///////////  onstate  /////////////////////////
switch (onstate){
  case 1: // power on
    RemoteXY.LED_Power_g = 200;
    digitalWrite(PIN_Power1,HIGH);
    Interface = 1;
      LastStateMillis = currentMillis;    // for not go to sleep mode
     if(  Interface == 1 && LastInterface == 0){
      delay (100);
    //  digitalWrite(PIN_Power2,HIGH);
      digitalWrite(PIN_Power3,HIGH);
//      delay (100);
//      digitalWrite(PIN_Power2,LOW);
//      delay (100);
//      digitalWrite(PIN_Power2,HIGH);
//      delay (100);
//      digitalWrite(PIN_Power2,LOW);
      LastInterface = 1;

         } 
    break;
    
  default: //power off
    RemoteXY.LED_Power_g = 0;
    digitalWrite(PIN_Power3,LOW);
    Interface = 0;
    if(  Interface == 0 && LastInterface == 1){  //state on
//      digitalWrite(PIN_Power2,HIGH);
      delay (200);
      digitalWrite(PIN_Power1,LOW);
//      digitalWrite(PIN_Power2,LOW);
      onstate = 0;
      delay (100);
      LastInterface = 0;

      } 
    onstate = 0;
  break;
}


///////////  Seatopen  /////////////////////////
switch (Seatopen){
  case 1: 
     delay(1200);
   if (digitalRead (PIN_SW1)==HIGH){
    digitalWrite(PIN_Power2,HIGH);
    }
   
    break;
    
  default: 
  digitalWrite(PIN_Power2,LOW);
  break;
}
//////////////////sleep mode//////////////////

if(((currentMillis - LastStateMillis )>= 60000) ){

     attachInterrupt(0, wakeUp, RISING) ;   //number 0 (for digital pin 2) or number 1 (for digital pin 3),// LOW, CHANGE,RISING ขอบขาขึ้น , FALLING ขอบขาลง
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
//  detachInterrupt(0); // Disable external pin interrupt on wake up pin.
LastStateMillis = currentMillis;
}

///////////////// Run Engine Start Pin /////////////////////////
   digitalWrite(PIN_EngStart,(RemoteXY.BU_EngStart==1 || (digitalRead(PIN_SW2)==HIGH))?HIGH:LOW) ;

//    RemoteXY.LED_Power_g = (digitalRead(PIN_PowerON)==HIGH)? 0:200 ; //LED for Power



//     Serial.print("Power >> oldstate: ");
//     Serial.print(oldstate);
//     Serial.print(", __state(Pin_Power): ");
//     Serial.print(onstate);                   //pin power
//     Serial.print(", __LED_Power_g: ");
//     Serial.println(RemoteXY.LED_Power_g);     //LED Power value


    delay (50);
  }

//////////////////////////runTaskBatt/////////////////////////////////
  //อ่าน V แบต
/* 
  #define WINDOW_SIZE 50
  int INDEX = 0;
int VALUE = 0;
int SUM = 0;
int READINGS[WINDOW_SIZE];
int AVERAGED = 0;

  void runTaskBatt(){
    SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
    A0read = analogRead(PIN_BattV);
    BattVolt = map(A0read, 0, 240, 0, 13000);     //mapping by serial print A0 read with serialprint A0=240 at 13V.

    
//  VALUE = analogRead(IN_PIN);        // Read the next sensor value
  READINGS[INDEX] = BattVolt;           // Add the newest reading to the window
  SUM = SUM + BattVolt;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result
  BattVolt = AVERAGED;
    BattVolt = (BattVolt/1000);

    if(BattVolt >= 13){                         //mV   // 0.8v greater than actual
      RemoteXY.LED_Engine_r = 200;
    }else{
      RemoteXY.LED_Engine_r = 0;
    }
     RemoteXY.onlineGraph_1=BattVolt;
     Serial.print("A0read: ");
     Serial.print(A0read); 
     Serial.print("BattVolt: ");
     Serial.print(BattVolt); 
     Serial.println(" V."); 
  }


*/
//////////////////////////End/////////////////////////////////

////////////////////////// ConnectStatus/////////////////////////////////
  //LED Status
  void ConnectStatus(){
  // check to see if it's time to change the state of the LED

  
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


///////////////////////////
