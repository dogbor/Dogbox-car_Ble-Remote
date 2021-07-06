//////////////////////////////////////////////
//              "Car Engine Start"              //
//////////////////////////////////////////////
/*
 * 
 //------------Devices-------------
// -ESP8266_testing
// -ESP32_waiting to test

//------------Funtions-------------

**Update.v1.1
  [Car]
   * RemoteXY  https://remotexy.com/en/
   * ย้ายcode EngineStart_V7 เดิมวางโครงสร้างใหม่
   * Newboard for ESP8266
   * Active high relay

*/

//////////////^ End ^//////////
//------------Library-------------
//Autoconnect
#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
typedef ESP8266WebServer  WiFiWebServer;
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#include <WebServer.h>
typedef WebServer WiFiWebServer;
#endif

#include <PageBuilder.h> //this apply for Credential


char con_ssid[32]; //Connected WIFI_SSID
char con_psk[64];  //Connected WIFI_PASSWORD
//////////////^ End ^//////////


//-------------------Define Pin--------------------------//
//**Pin**

  #define PIN_BoardLED    2    // LED_BUILTIN
//  #define PIN_Power2      16     //D0 OUT /relay 1
  #define PIN_Power       12     //D5 OUT /relay 2
  #define PIN_EngStart    13     //D6 OUT /relay 3
//  #define PIN_4         13     //D7 OUT / relay 4
//#define PIN_D8          15     //D8 OUT
  #define PIN_SW1         5     //D1 IN / remote on
  #define PIN_SW2         4     //D2 IN / remote start
//    #define D3 0           //D3
//  #define D4 2             //D4          use>> LED_BUILTIN
  #define PIN_BattV       A0     //A IN

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
