/* ------------ Library ------------- */
#include "LowPower.h"


/*------------------- Define Pin --------------------------*/
#define PIN_BoardLED    13    // LED_BUILTIN
#define PIN_Power1      9     // relay 1 >>ON1
#define PIN_Power2      6     // relay 2 >>Interface
#define PIN_Power3      5     // relay 3 >>ON2
#define PIN_EngStart    4     // relay 4 >>Start
#define PIN_SW1         8     //IO1 / remote [on]
#define PIN_SW2         7     //IO2  / remote [start]
#define wakeUpPin       2     //Use pin 2 as wake up pin

/*------------------- VARIABLE --------------------*/
int sw1state = 0;                   // Toggle state for Remote (A)
int sw2state = 0;                   // Toggle state for Remote (B)
long OnTime = 1000;                 // milliseconds of on-time
unsigned long currentMillis =0;     // start milliseconds of on-time
unsigned long LastStateMillis =0;   // for sleep


void wakeUp() //(sleep mode)
{
    // Just a handler for the pin interrupt.
}

/*----------- LED BLINK FUNCTION --------------*/
void ConnectStatus(){
  if((millis() - currentMillis > OnTime)){
    digitalWrite(PIN_BoardLED, (digitalRead(PIN_BoardLED)) ? LOW : HIGH);
    currentMillis = millis();
  }
}

/*------------ Setup function -------------*/
void setup() {
    Serial.begin(9600);               //for Serial Monitor

    pinMode(PIN_BoardLED  ,OUTPUT);    
    pinMode(PIN_Power1     ,OUTPUT);
    pinMode(PIN_Power2     ,OUTPUT);
    pinMode(PIN_Power3     ,OUTPUT);
    pinMode(PIN_EngStart  ,OUTPUT);

    pinMode(PIN_SW1       ,INPUT);
    pinMode(PIN_SW2       ,INPUT);
    pinMode(wakeUpPin, INPUT);  
    
    digitalWrite(PIN_Power1  ,LOW);  //set initial state as off
    digitalWrite(PIN_Power2  ,LOW);
    digitalWrite(PIN_Power3  ,LOW);
    digitalWrite(PIN_EngStart  ,LOW);  //set initial state as off
    digitalWrite(PIN_BoardLED, LOW);

    currentMillis = millis();
}


/*------------ Loop function -------------*/
void loop() {
   detachInterrupt(0); // Disable external pin interrupt on wake up pin.

  /*----------- PUSH REMOTE --> (A) ----------*/
  if(  sw1state == 0 && digitalRead (PIN_SW1)==HIGH ){
    Serial.println("PUSH : 0 --> 1");
    sw1state = 1;
  }
  else if(sw1state == 2 && digitalRead (PIN_SW1) == LOW){
    Serial.println("NO PUSH : 2 --> 3");
    sw1state = 3;
  }else if(sw1state == 3 && digitalRead (PIN_SW1) == HIGH){
    Serial.println("PUSH : 3 --> 4");
    sw1state = 4;
  }else if(sw1state == 5 && digitalRead (PIN_SW1) == LOW){
    Serial.println("NO PUSH : 5 --> 0");
    sw1state = 0;
  }

  switch(sw1state){
    case 1: 
      Serial.println("ON");
      digitalWrite(PIN_Power1,HIGH);
      digitalWrite(PIN_Power2,HIGH);
      delay (100);
      digitalWrite(PIN_Power2,LOW);
      delay (100);
      digitalWrite(PIN_Power2,HIGH);
      delay (100);
      digitalWrite(PIN_Power2,LOW);
      digitalWrite(PIN_Power3,HIGH);
      
      LastStateMillis = currentMillis;
      Serial.println("TRIGGER : 1 --> 2");
      sw1state = 2;
      break;
    case 4:
      Serial.println("OFF");
      digitalWrite(PIN_Power3,LOW);
      digitalWrite(PIN_Power2,HIGH);
      delay (200);
      digitalWrite(PIN_Power2,LOW);
      digitalWrite(PIN_Power1,LOW);
      delay (100);
      LastStateMillis = currentMillis;
      Serial.println("TRIGGER : 4 --> 5");
      sw1state = 5;
      break;
    
  }

  /*------------- ENGINE START REMOTE --> 'B' (MOTOR) ---------------*/
  if(digitalRead(PIN_SW2) == HIGH){
    if(sw1state == 3){
      Serial.println("PUSH START");
      digitalWrite(PIN_EngStart, HIGH);
      sw2state = 1;
    }
  }
  else if(digitalRead(PIN_SW2) == LOW && sw2state == 1){
    Serial.println("NO PUSH START");
   digitalWrite(PIN_EngStart, LOW);
   sw2state = 0;
  }

  /*------------ SLEEP MODE (LATER 60 sec) -----*/
  if(((currentMillis - LastStateMillis ) > 60000) && sw1state == 0){
    digitalWrite(PIN_BoardLED, LOW);
    Serial.println("GOOD NIGTH");
    delay(500);
    attachInterrupt(0, wakeUp, RISING);   //number 0 (for digital pin 2) or number 1 (for digital pin 3),// LOW, CHANGE,RISING ขอบขาขึ้น , FALLING ขอบขาลง
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    LastStateMillis = currentMillis;
  }
  
  ConnectStatus();

}
