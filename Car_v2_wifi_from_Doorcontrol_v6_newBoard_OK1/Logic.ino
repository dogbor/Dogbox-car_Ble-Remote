/*  uint8_t SW1; // =1 if switch ON and =0 if OFF 
  uint8_t BUT1; // =1 if button pressed, else =0 
  uint8_t BUT2; // =1 if button pressed, else =0 

    // output variables
  uint8_t led_c_r; // =0..255 LED Red brightness 
  uint8_t led_c_g; // =0..255 LED Green brightness 
  uint8_t led_o_r; // =0..255 LED Red brightness 
  uint8_t led_o_g; // =0..255 LED Green brightness 
  char WifiPerc[11];  // string UTF8 end zero 
*/
/*
int Delay = 1200; //Button toggle for delay
unsigned long ToggleD5delay =0;
bool ToggleD5 = false;
int SW1toggle =0;
int BUT1toggle =0;
int BUT2toggle =0;
int IRtoggle =0;
int case_auto =0; //
int autotoggle=0;
//RemoteXY.SW1=0;

void ToggleD5_loop(){
   if (ToggleD5==true){
      RemoteXY.led_c_g = 200;
      RemoteXY.led_o_g = 200;
      digitalWrite(D5,HIGH); 
//      Serial.println("ToggleD5==true");
      
      if( millis() > ToggleD5delay + Delay ) {
        digitalWrite(D5,LOW);
        RemoteXY.led_c_g = 0;
        RemoteXY.led_o_g = 0;
        ToggleD5=false; 
//        Serial.println("ToggleD5==false");
      }

   }
}

void Logic_loop() {
  ToggleD5_loop();

//////////////////////// LED open close  & sensor//////////
      RemoteXY.led_o_r = (digitalRead(D6)==HIGH)? 200:0 ; //LED open
      RemoteXY.led_c_r = (digitalRead(D7)==HIGH)? 200:0 ; //LED close

///////////////////////////open / close button ///////////////////

  if (RemoteXY.BUT1==1 && BUT1toggle == 0){
    ToggleD5delay = millis();
    ToggleD5 = true;
    BUT1toggle = 1;
  }

  if (RemoteXY.BUT1==0 && BUT1toggle == 1){
    BUT1toggle = 0;
  }
//     digitalWrite(D5,(RemoteXY.BUT1==1)?HIGH:LOW) ;  //output control signal
//     RemoteXY.led_o_g = (RemoteXY.BUT1==1)? 150:0 ;
//     RemoteXY.led_c_g = (RemoteXY.BUT1==1)? 150:0 ;

     
////////////////////////SW1 Control/////////////
  if (RemoteXY.SW1==1 && SW1toggle == 0) {         //SW to close
    if ( digitalRead(D6)== HIGH){    //ถ้าประตูเปิดอยู่ 
      ToggleD5delay = millis();
      ToggleD5 = true;
      SW1toggle = 1 ;
    }
  }
  if (RemoteXY.SW1==0 && SW1toggle == 1) {         //SW to open
    if ( digitalRead(D7)== HIGH){           //ถ้าประตูปิดอยู่
      ToggleD5delay = millis();
      ToggleD5 = true;
      SW1toggle = 0 ;
    }
  }
//////////////////SW1 response////////////
if (digitalRead(D6)==HIGH){ //open sensor active
  RemoteXY.SW1=0;           //SWopen
  SW1toggle =0;
}
if (digitalRead(D7)==HIGH){  //close sensor active
  RemoteXY.SW1=1;           //SWclose
  SW1toggle =1;
}

////////////////IR reset///////////
if (analogRead(ADC)<100){
  IRtoggle = 0;  //IR 
}
////////////////BUT2 reset///////////
if (RemoteXY.BUT2==0){
  BUT2toggle = 0;  //IR 
}
///////////////IR Auto close///////////
  if (RemoteXY.BUT2==1 && BUT2toggle == 0){
      RemoteXY.led_o_b = 200;
      RemoteXY.led_c_b = 200;
      if(digitalRead(D7)==HIGH){       //ถ้าประตูปิด
        ToggleD5delay = millis();
        ToggleD5 = true;
        case_auto = 1;
        }
            
      if (digitalRead(D6)==HIGH){      //ถ้าประตูเปิด
        case_auto = 1;
        }

      if(digitalRead(D6)&& digitalRead(D7) == LOW ){    //ถ้าประตูไม่เปิด ไม่ปิด
        ToggleD5delay = millis();
        ToggleD5 = true;
        case_auto = 1;
        
      }
  }

  switch (case_auto){
    case 1:    // รอ IR แล้ว tog
        if (analogRead(ADC)>=100 || autotoggle==1){  //IR 
          if(analogRead(ADC)<100){
            delay(3000);
            ToggleD5delay = millis();
            ToggleD5 = true;
            case_auto=0;
            autotoggle=0;
          }
          autotoggle=1;
        }
     break;
    default:
      case_auto=0;
      autotoggle=0;
      RemoteXY.led_o_b = 0;
      RemoteXY.led_c_b = 0;
    break;
  }

}//end logic loop

*/


//-------------------Logic--------------------------//
//void openOrclose() {
//  if (digitalRead(D7) == LOW){
//    Serial.println("D1 LOW");
////    digitalWrite(D5,LOW);
//delay(200);
//  }
//  if (digitalRead(D7) == HIGH){
//    Serial.println("D1 HIGH");
////    digitalWrite(D5,HIGH);
//delay(200);
//  }
//
//}
//-------------------RemoteXY Control--------------------------// 
//int BUT1toggle =0;

//void logic_RemoteXY() {
//
//}
//-------------------MQTT linebot--------------------------// 

//int MQTTtoggle =0;
//void logic_MQTT() {
//    if( MQTTtoggle == 0 && MQTTMessage == "Open" ){
//      
//      mqtt.publish(topicPubName,"Control: Open");
//      Serial.println("mqtt : Open");
//      MQTTtoggle = 1;
//    }
//   
//   if( MQTTtoggle ==1 && MQTTMessage == "Close" ){
//      
//      mqtt.publish(topicPubName,"Control: Close");
//      Serial.println("mqtt : Close");
//      MQTTtoggle = 0;
//   }
//
//}


//-------------------Funtion--------------------------//
