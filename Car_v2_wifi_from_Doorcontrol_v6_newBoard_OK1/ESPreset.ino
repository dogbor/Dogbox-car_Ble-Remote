
//Schedule Reset

long scheduleReset = 86400000; //set delay time for MQTT connection serial print <86400000ms = 1 day>
//unsigned long last_time3 = 0;

void ESPreset_loop() {
//    Serial.print(last_time);
//    Serial.print(" Count:");
//    Serial.print (millis() - last_time );
//    delay(200);
//    Serial.println("  Waiting for WiFi connection...");
//    flipper.attach(0.1, flip); // flip the pin every 0.1s

    
    if ( millis() > scheduleReset){
      ESP.reset();
    }
    
//    else {                              //else funtion for test
//      Serial.print("ResetCount:");
//      Serial.println(millis());
//    }
    
}
