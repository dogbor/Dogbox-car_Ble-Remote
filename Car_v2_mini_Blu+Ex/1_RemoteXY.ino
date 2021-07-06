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
   { 255,6,0,7,0,13,1,10,28,5,
  131,0,0,1,63,5,1,26,1,84,
  101,101,77,111,116,111,80,97,114,116,
  0,2,0,9,53,18,20,2,2,26,
  31,31,79,78,0,79,70,70,0,1,
  2,35,52,18,22,2,2,31,83,116,
  97,114,116,0,65,20,41,34,7,7,
  2,129,0,9,25,44,4,2,24,224,
  184,163,224,184,176,224,184,154,224,184,
  154,224,185,132,224,184,159,32,32,32,
  32,32,32,32,32,32,224,185,128,224,
  184,132,224,184,163,224,184,183,224,185,
  136,224,184,173,224,184,135,224,184,162,
  224,184,153,224,184,149,224,185,140,0,
  65,22,13,34,7,7,2,68,17,6,
  66,51,21,3,8,36,129,0,50,3,
  10,2,0,93,98,121,32,68,111,103,
  66,111,88,0,2,0,7,31,18,12,
  3,2,26,31,31,79,78,0,79,70,
  70,0,1,1,29,31,12,12,3,2,
  31,49,48,0,1,1,44,31,12,12,
  3,2,31,49,49,0,1,1,7,49,
  48,11,3,2,31,49,50,0,131,1,
  1,7,30,9,2,1,31,72,111,109,
  101,0,131,0,33,7,29,9,3,1,
  31,65,100,118,97,110,99,101,0,129,
  0,16,48,33,6,1,17,87,69,76,
  67,79,77,69,33,0 };
    
struct {
        // input variables
  uint8_t SW_Power; // =1 if switch ON and =0 if OFF 
  uint8_t BU_EngStart; // =1 if button pressed, else =0 
  uint8_t switch_13; // =1 if switch ON and =0 if OFF 
  uint8_t button_10; // =1 if button pressed, else =0 
  uint8_t button_11; // =1 if button pressed, else =0 
  uint8_t button_12; // =1 if button pressed, else =0 

    // output variables
  uint8_t LED_Engine_r; // =0..255 LED Red brightness 
  uint8_t LED_Power_r; // =0..255 LED Red brightness 
  uint8_t LED_Power_g; // =0..255 LED Green brightness 
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
      LastStateMillis = currentMillis;    // for not go to sleep mode
     if(  Interface == 1 && LastInterface == 0){
      delay (100);
      digitalWrite(PIN_Power2,HIGH);
      digitalWrite(PIN_Power3,HIGH);
      delay (100);
      digitalWrite(PIN_Power2,LOW);
      delay (100);
      digitalWrite(PIN_Power2,HIGH);
      delay (100);
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
      delay (200);
      digitalWrite(PIN_Power1,LOW);
      digitalWrite(PIN_Power2,LOW);
      onstate = 0;
      delay (100);
      LastInterface = 0;

      } 
    onstate = 0;
  break;
}

//////////////////sleep mode//////////////////

if(((currentMillis - LastStateMillis )>= 60000) ){

     attachInterrupt(0, wakeUp, LOW) ;   //number 0 (for digital pin 2) or number 1 (for digital pin 3),// LOW, CHANGE,RISING ขอบขาขึ้น , FALLING ขอบขาลง
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
//  detachInterrupt(0); // Disable external pin interrupt on wake up pin.
LastStateMillis = currentMillis;
}

///////////////// Run Engine Start Pin /////////////////////////

   if(RemoteXY.BU_EngStart==1 || (digitalRead(PIN_SW2)==HIGH)){
    digitalWrite(PIN_EngStart, (onstate == 1 && Interface == 1) ? HIGH : LOW);
   }else if((digitalRead(PIN_SW2)==LOW)){
    digitalWrite(PIN_EngStart, LOW);
   }


    delay (50);
  }

//////////////////////////runTaskBatt/////////////////////////////////
  //อ่าน V แบต
  
const int numReadings = 40;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup_runTaskBatt() {

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

  void runTaskBatt(){
// subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(PIN_BattV);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;


   
    BattVolt = map(average, 0, 240, 0, 13000);     //mapping by serial print A0 read with serialprint A0=240 at 13V.
    BattVolt = (BattVolt/1000);

    if(BattVolt >= 13){                         //mV   // 0.8v greater than actual
      RemoteXY.LED_Engine_r = 200;
    }else{
      RemoteXY.LED_Engine_r = 0;
    }
     RemoteXY.onlineGraph_1=BattVolt;
     Serial.print("A0read: ");
     Serial.print(average); 
     Serial.print("BattVolt: ");
     Serial.print(BattVolt); 
     Serial.println(" V."); 
  }



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

///////////////////////////////////////////////////
//void button12(){
//  int count=3;
//  int i =0;
////  Serial.println(RemoteXY.button_12);
////  Serial.println("count "+count);
//  
//  while(i<count){
//    i=i+1;
//    Serial.println(i);
//    digitalWrite(PIN_button_12,HIGH);
//    delay(1000);
//    digitalWrite(PIN_button_12,LOW);
//    delay(1000);
//  }
//  
//}

void button10to13(){
//  RemoteXY_Handler ();
//  digitalWrite(PIN_SW_POWER, (RemoteXY.SW_Power==0)?LOW:HIGH);
//  digitalWrite(PIN_BU_ENGSTART, (RemoteXY.BU_EngStart==0)?LOW:HIGH);
  digitalWrite(PIN_button_10, (RemoteXY.button_10==0)?LOW:HIGH);
  digitalWrite(PIN_button_11, (RemoteXY.button_11==0)?LOW:HIGH);
  
//  if (RemoteXY.button_12==1){
////    Serial.println("before condition");
//    RemoteXY.button_12=0;
//    button12();
////    Serial.println("after condition");
//  }
  
//  digitalWrite(PIN_switch_13, (RemoteXY.switch_13==0)?LOW:HIGH);
}
