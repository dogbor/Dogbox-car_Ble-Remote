//////////////////////////////////////////////
//              "Car Engine Start" 
//                     DOGBOX
//////////////////////////////////////////////


//-------------------Define Pin--------------------------//
//**Pin**

  #define PIN_BoardLED    13    // LED_BUILTIN
  #define PIN_Power1      9     // relay 1 >>ON1
  #define PIN_Power2      6     // relay 2 >>Interface
  #define PIN_Power3      5     // relay 3 >>ON2
  #define PIN_EngStart    4     // relay 4 >>Start
  #define PIN_SW1         8     //IO1 / remote [on]
  #define PIN_SW2         7     //IO2  / remote [start]
//    #define D3 0           //D3
//  #define D4 2             //D4          use>> LED_BUILTIN
  #define PIN_BattV       A0     //A IN

int A0read = 0;                   //for runTaskBatt
float BattVolt = 0;                 //for runTaskBatt
int onstate = 0;
int oldstate = 0;
int buttonPoll=0;  
int sw1state = 0;            //for Remote (on) Toggle state
int Interface = 0;           //for interface
int LastInterface = 0;           //for interface
long OnTime = 300;           // milliseconds of on-time
long OffTime = 2000;          // milliseconds of off-time
unsigned long currentMillis =0;
unsigned long previousMillis = 0;
unsigned long LastStateMillis =0;

//////////////^ End ^//////////
//------------Setup-------------
void setup() {

    
    Serial.begin(9600);               //for Serial Monitor

    pinMode(PIN_BoardLED  ,OUTPUT);    
    pinMode(PIN_Power1     ,OUTPUT);
    pinMode(PIN_Power2     ,OUTPUT);
    pinMode(PIN_Power3     ,OUTPUT);
    pinMode(PIN_EngStart  ,OUTPUT);

    pinMode(PIN_SW1       ,INPUT);
    pinMode(PIN_SW2       ,INPUT);


    digitalWrite(PIN_Power1  ,LOW);  //set initial state as off
    digitalWrite(PIN_Power2  ,LOW);
    digitalWrite(PIN_Power3  ,LOW);
    digitalWrite(PIN_EngStart  ,LOW);  //set initial state as off

//________________________________________________
  //just information//
//  Serial.print("ESP_ChipID:");
//  Serial.println(String(ESP.getChipId(),HEX));
//___________________________________________________ 

//setup//
  Remotexy_setup();    //[RemoteXY]


}


//////////////^ End ^//////////
//------------Loop-------------

void loop() {

  Remotexy_loop();  //[RemoteXY]
    runTaskBatt();  //[RemoteXY]
//    ConnectStatus();//[RemoteXY]
 
}

//////////////^ End ^//////////


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
LastStateMillis = currentMillis;
  }

  if(  oldstate ==1 && RemoteXY.SW_Power==0){
   onstate = 0;
     oldstate = 0;
     LastStateMillis = currentMillis;

  }
  
///////// Remote RF on Toggle ///////////////
   if(  sw1state ==0 && digitalRead (PIN_SW1)==HIGH ){
   onstate = onstate+1;
   LastStateMillis = currentMillis;
     sw1state = 1;

  }
   if(  sw1state ==1 && digitalRead (PIN_SW1)==LOW ){
   onstate = onstate;
   LastStateMillis = currentMillis;
     sw1state = 0;

  } 

///////////  onstate  /////////////////////////
switch (onstate){
  case 1: // power on
    RemoteXY.LED_Power_g = 200;
    digitalWrite(PIN_Power1,HIGH);
    Interface = 1;
    
     if(  Interface == 1 && LastInterface == 0){
      delay (100);
      digitalWrite(PIN_Power2,HIGH);
      digitalWrite(PIN_Power3,HIGH);
      delay (80);
      digitalWrite(PIN_Power2,LOW);
      delay (100);
      digitalWrite(PIN_Power2,HIGH);
      delay (80);
      digitalWrite(PIN_Power2,LOW);
      LastInterface = 1;
         } 
    break;
    
  default: //power off
    RemoteXY.LED_Power_g = 0;
    digitalWrite(PIN_Power3,LOW);
    Interface = 0;
    if(  Interface == 0 && LastInterface == 1){  //state on
      digitalWrite(PIN_Power2,HIGH);
      delay (80);
      digitalWrite(PIN_Power1,LOW);
      delay (80);
      digitalWrite(PIN_Power2,LOW);
      LastInterface = 0;
      } 
    onstate = 0;
  break;
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
  void runTaskBatt(){
    A0read = analogRead(PIN_BattV);

    BattVolt = map(A0read, 0, 91, 0, 5000);     //mapping by serial print A0read with input A0 at 5000mV.
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
