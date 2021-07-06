//////////////////////////////////////////////
//              "Car Engine Start"              //
//////////////////////////////////////////////
/*
 * 
 //------------Devices-------------
// -ESP32

//------------Funtions-------------

**Update.v1.1
  [Car]
   * RemoteXY  https://remotexy.com/en/
   * ย้ายcode EngineStart_V7 เดิมวางโครงสร้างใหม่
   * Newboard for ESP32
   * Active high relay

*/

//////////////^ End ^//////////
//------------Library-------------



//////////////^ End ^//////////


//-------------------Define Pin--------------------------//
//**Pin**

  #define PIN_BoardLED    2    // LED_BUILTIN
//  #define PIN_Power2      9     //D0 OUT /relay 1
  #define PIN_Power       19     //D5 OUT /relay 2
  #define PIN_EngStart    18     //D6 OUT /relay 3
//  #define PIN_4         4     //D7 OUT / relay 4
//#define PIN_D8          3     //D8 OUT
  #define PIN_SW1         21     //D1 IN / remote on
  #define PIN_SW2         22     //D2 IN / remote start
//    #define D3 0           //D3
//  #define D4 2             //D4          use>> LED_BUILTIN
  #define PIN_BattV       32     //A IN

int A0read = 0;                   //for runTaskBatt
float BattVolt = 0;                 //for runTaskBatt
int state = 0;
int oldstate = 0;
int buttonPoll=0;  
int sw1state = 0; //for digitalout
long OnTime = 300;           // milliseconds of on-time
long OffTime = 2000;          // milliseconds of off-time
unsigned long previousMillis = 0;

//////////////^ End ^//////////
//------------Setup-------------
void setup() {

    
    Serial.begin(9600);               //for Serial Monitor

    pinMode(PIN_BoardLED  ,OUTPUT);    
    pinMode(PIN_Power     ,OUTPUT);
    pinMode(PIN_EngStart  ,OUTPUT);

    pinMode(PIN_SW1       ,INPUT);
    pinMode(PIN_SW2       ,INPUT);


    digitalWrite(PIN_Power  ,LOW);  //set initial state as off
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
