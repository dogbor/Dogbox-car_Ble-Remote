
//
//char con_ssid[32]; //Connected WIFI_SSID
//char con_psk[64];  //Connected WIFI_PASSWORD

//WiFi signal strength
  /*
 * dBm t oPercentage Code Ref: https://robojax.com/learn/arduino/?vid=robojax_ESP8266_wifi_scan
 * conversion ref: https://www.adriangranados.com/blog/dbm-to-percent-conversion
 * Written by Ahmad Shamshiri
 * 
  * with lots of research, this sources was used:
 * https://support.randomsolutions.nl/827069-Best-dBm-Values-for-Wifi 
 * This is approximate percentage calculation of RSSI
 * WiFi Signal Strength Calculation
 * Written Aug 08, 2019 at 21:45 in Ajax, Ontario, Canada
 */
 //int dBm = 0;  //  *WiFi signal strength
const int RSSI_MAX =-50;// define maximum strength of signal in dBm
const int RSSI_MIN =-100;// define minimum strength of signal in dBmx

int dBmtoPercentage(int dBm){
  int quality;
    if(dBm <= RSSI_MIN){
        quality = 0;
    }
    else if(dBm >= RSSI_MAX){  
        quality = 100;
    }
    else{
        quality = 2 * (dBm + 100);
   }
     return quality;
}//dBmtoPercentage 


//------------Setup-------------
void Wifi_setup() {
   WiFi.printDiag(Serial);
   Serial.println();
   Serial.println("Wifi Setup >> connected...yeey :)");
   
  WiFi.SSID().toCharArray(con_ssid, 32);
  WiFi.psk().toCharArray(con_psk, 64);
  
  Serial.printf("connected to %s\n", con_ssid);
  Serial.printf("Password %s\n", con_psk);


//  *WiFi signal strength
//  dBm = WiFi.RSSI();
  Serial.print("WiFi Signal Strength: ");
  Serial.print(WiFi.RSSI());
  Serial.print("dBm");
  Serial.print(" (");
  Serial.print(dBmtoPercentage(WiFi.RSSI()));//Signal strength in % 
  Serial.println("%)");


//just information
  Serial.print("local ip: ");
  Serial.println(WiFi.localIP());
}//end Wifi_setup

//////////////^ End ^//////////




void Wifi_loop(){
//  Serial.println(dBmtoPercentage(WiFi.RSSI()));
RemoteXY.WifiPerc = (dBmtoPercentage(WiFi.RSSI()));
  delay(50);
//  char WifiPerc1[11] = dBmtoPercentage(WiFi.RSSI()); //RemoteXY
//  RemoteXY.WifiPerc = WifiPerc1;
}
