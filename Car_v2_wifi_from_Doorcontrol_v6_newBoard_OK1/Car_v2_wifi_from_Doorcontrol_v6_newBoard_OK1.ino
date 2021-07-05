//////////////////////////////////////////////
//              "Door control"              //
//////////////////////////////////////////////
/*
 * 
 //------------Devices-------------
// -ESP8266_ok
// -ESP32_waiting to test

//------------Funtions-------------

**Update.v1
  [Autoconnect]
   Example for the AutoConnect library. https://github.com/Hieromon/AutoConnect 
     Document: https://hieromon.github.io/AutoConnect/ 
    1.OTAupdate_AP Web Browser    Ref: https://hieromon.github.io/AutoConnect/otaupdate.html
    2.Credential <for delete wifi setup at HOME page>
    4.Setup SoftAP wifi name &pw
    4.Ticker for WiFi status
    4.Set menu title
    4.autoReconnect
    5.<lost wifi signal reset> wifi disconnect and reset and led กระพิบ 0.1s 
   [OTA_IDE]
    3.OTA_IDE ESP8266 <OTA Port for local network>

**Update.v2
  [Wifi]
    *1 wifi information ssid, psk
    *1 WiFi signal strength RSSI (dBm)
    *1 WiFi Convesion dBm to %

  [ClearEEROM]
    *2 funtion for clear eerom that remember wifi connection, clear when start for testing
    *
  [RemoteXY]  https://remotexy.com/en/
    *3 RemoteXY app ok
**Update.v3
  [Autoconnect]
    *1 STAtimeout, timeout of autoconnect SoftAP mode,  The timeout value of the captive portal
  [MQTT]
    *2 mqtt connect and sub <ok>
    *3 mqtt connect and reconnection delay when internet ok
  [ESPreset]
    *4 Schedule Reset ESP when normal connection (1day)
**Update.v4
    *dubug wifiautoconnect after loss connection <CREDENTIAL_OFFSET 64>
**Update.v5
    *5.3 RemoteXY control OK
    *5.3 MQTT control OK
    *5.4 Logic RemoteXY with 1.LED open close  & sensor, 2.open / close button, 3.SW1 Control, 4.IR Auto close
    *5.5 Line command "open" or "close" OK
    *5.6 modify some bug such as open to close SW LED, IR LED
    *5.7 wifi% printout
**Update.v6
    *6.1 New board Pin setting

    
**Update Car_v2

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
  #define D5 16 //แก้ไขD0 เป็นD5 20200821
  #define D1 5
  #define D2 4
  #define D3 0
//  #define D4 2 //use>> LED_BUILTIN
  #define D0 14  //แก้ไขD5 เป็นD0 20200821
  #define D6 12
  #define D7 13
  #define D8 15
  #define S2 9
  #define S3 10
  #define ADC A0


  #define PIN_Power1 16 //D0 .. relay 1 >>ON1
  #define PIN_SW1 5          //D1 .. IO1 / remote [on]
  #define PIN_SW2 4          //D2 .. IO2  / remote [start]
//  #define D3 0        //D3 ..
//  #define D4 2        //D4 .. use>> LED_BUILTIN
  #define PIN_Power2 14   //D5 .. relay 2 >>Interface
  #define PIN_Power3 12          //D6 .. relay 3 >>ON2
  #define PIN_EngStart 13          //D7 .. relay 4 >>Start
//  #define D8 15          //D8 .. 
//  #define S2 9           //S2 .. 
//  #define S3 10          //S3 .. 
  #define PIN_BattV A0         //A0 ADC .. 
//  #define wakeUpPin

int A0read = 0;                   //for runTaskBatt
float BattVolt = 0;                 //for runTaskBatt
int onstate = 0;
int oldstate = 0;
int buttonPoll=0;  
int sw1state = 0;            //Toggle state for Remote (on)
int Interface = 0;           //for interface
int LastInterface = 0;           //for interface
long OnTime = 300;           // milliseconds of on-time
long OffTime = 2000;          // milliseconds of off-time

//unsigned long currentMillis =0; //for sleep
//unsigned long previousMillis = 0; //for sleep
//unsigned long LastStateMillis =0;  //for sleep

//////////////^ End ^//////////
//------------Setup-------------
void setup() {
  Serial.begin(115200);
  Serial.println();


//    pinMode(PIN_BoardLED  ,OUTPUT);    
    pinMode(PIN_Power1     ,OUTPUT);
    pinMode(PIN_Power2     ,OUTPUT);
    pinMode(PIN_Power3     ,OUTPUT);
    pinMode(PIN_EngStart  ,OUTPUT);

    pinMode(PIN_SW1       ,INPUT);
    pinMode(PIN_SW2       ,INPUT);
//    pinMode(wakeUpPin, INPUT);  
    
    digitalWrite(PIN_Power1  ,LOW);  //set initial state as off
    digitalWrite(PIN_Power2  ,LOW);
    digitalWrite(PIN_Power3  ,LOW);
    digitalWrite(PIN_EngStart  ,LOW);  //set initial state as off

    Serial.println("FRIST SETUP");
//setup//
  Serial.println("AutoConnect");
  AutoConnect_setup(); //[AutoConnect]
  Serial.println("OTA");
  OTAIDE_setup();      //[OTA_IDE]
  Serial.println("WIFI");
  Wifi_setup();        //[Wifi]
  Serial.println("Remote");
  Remotexy_setup();    //[RemoteXY]
  Serial.println("Other");
  setup_runTaskBatt(); //[RemoteXY]
//  mqtt_setup();         //[MQTT]

  //just information//
  Serial.print("ESP_ChipID:");
  Serial.println(String(ESP.getChipId(),HEX));
}


//////////////^ End ^//////////
//------------Loop-------------

void loop() {
  ESPreset_loop();     //[ESPreset]
//  ClearEEROM_setup(); //Clear remember of wifi connection for testing, < "//"for close this funtion >
  AutoConnect_loop(); //AutoConnect
  OTAIDE_loop();    //OTAIDE
  Wifi_loop();      //[Wifi]
  Remotexy_loop();  //[RemoteXY]
//  runTaskBatt();  //[RemoteXY]
//  mqtt_loop();         //[MQTT]

//  Logic_loop();


  
}

//////////////^ End ^//////////
