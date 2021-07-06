//////////////////////////////////////////////
//              "Car Engine Start"              //
//////////////////////////////////////////////
/*
 * 
 //------------Devices-------------
// -Arduino ProMini_testing

//------------Funtions-------------

**Update.v1.1
  [Car]
   * RemoteXY  https://remotexy.com/en/
   * ย้ายcode EngineStart_V7 เดิมวางโครงสร้างใหม่
   * Newboard for Promini
   * Active high relay
V1.3
  * Add pin power for 4 relay
  * new logic 

*/

//////////////^ End ^//////////
//------------Library-------------



//////////////^ End ^//////////


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
//unsigned long LastInteMillis =0;

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
    ConnectStatus();//[RemoteXY]
 
}

//////////////^ End ^//////////
