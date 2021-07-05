/*
  OTAUpdate.ino, Example for the AutoConnect library.
  https://github.com/Hieromon/AutoConnect
 */


#include <AutoConnect.h> //OTAupdate //Credential
#include <AutoConnectCredential.h> //Credential

const unsigned long STAtimeout = 60000; //[ms] เวลาปล่อย AP

//OTAupdate web browser
WiFiWebServer server;
AutoConnect portal(server);
AutoConnectConfig config ("dogBoX", "12345678", STAtimeout); //(const char* ap, const char* password, const unsigned long timeout) Setup SoftAP wifi pw, The timeout value of the captive portal in [ms] 

//Define Credential 
String viewCredential(PageArgument&);
String delCredential(PageArgument&);
#define CREDENTIAL_OFFSET 64
//#define CREDENTIAL_OFFSET 64

//wifi disconnect and reset and led กระพิบ 0.1s
#include <Ticker.h> 
Ticker flipper;
void flip() {
  int state = digitalRead(LED_BUILTIN);  // get the current state of GPIO1 pin
  digitalWrite(LED_BUILTIN, !state);     // set pin to the opposite state
}


//------------Credential -------------  
/**
 *  An HTML for the operation page.
 *  In PageBuilder, the token {{SSID}} contained in an HTML template below is
 *  replaced by the actual SSID due to the action of the token handler's
 * 'viewCredential' function.
 *  The number of the entry to be deleted is passed to the function in the
 *  POST method.
 */
static const char PROGMEM html[] = R"*lit(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=1">
  <style>
  html {
  font-family:Helvetica,Arial,sans-serif;
  -ms-text-size-adjust:100%;
  -webkit-text-size-adjust:100%;
  }
  .menu > a:link {
    position: absolute;
    display: inline-block;
    right: 12px;
    padding: 0 6px;
    text-decoration: none;
  }
  </style>
</head>
<body>
<div class="menu">{{AUTOCONNECT_MENU}}</div>
<form action="/del" method="POST">
  <ol>
  {{SSID}}
  </ol>
  <p>Enter deleting entry:</p>
  <input type="number" min="1" name="num">
  <input type="submit">
</form>
</body>
</html>
)*lit";

static const char PROGMEM autoconnectMenu[] = { AUTOCONNECT_LINK(BAR_24) };

// URL path as '/'
PageElement elmList(html,
  {{ "SSID", viewCredential },
   { "AUTOCONNECT_MENU", [](PageArgument& args) {
                            return String(FPSTR(autoconnectMenu));} }
  });
PageBuilder rootPage("/", { elmList });

// URL path as '/del'
PageElement elmDel("{{DEL}}", {{ "DEL", delCredential }});
PageBuilder delPage("/del", { elmDel });

// Retrieve the credential entries from EEPROM, Build the SSID line
// with the <li> tag.
String viewCredential(PageArgument& args) {
  AutoConnectCredential  ac(CREDENTIAL_OFFSET);
  station_config_t  entry;
  String content = "";
  uint8_t  count = ac.entries();          // Get number of entries.

  for (int8_t i = 0; i < count; i++) {    // Loads all entries.
    ac.load(i, &entry);
    // Build a SSID line of an HTML.
    content += String("<li>") + String((char *)entry.ssid) + String("</li>");
  }

  // Returns the '<li>SSID</li>' container.
  return content;
}

// Delete a credential entry, the entry to be deleted is passed in the
// request parameter 'num'.
String delCredential(PageArgument& args) {
  AutoConnectCredential  ac(CREDENTIAL_OFFSET);
  if (args.hasArg("num")) {
    int8_t  e = args.arg("num").toInt();
    Serial.printf("Request deletion #%d\n", e);
    if (e > 0) {
      station_config_t  entry;

      // If the input number is valid, delete that entry.
      int8_t  de = ac.load(e - 1, &entry);  // A base of entry num is 0.
      if (de > 0) {
        Serial.printf("Delete for %s ", (char *)entry.ssid);
        Serial.printf("%s\n", ac.del((char *)entry.ssid) ? "completed" : "failed");

        // Returns the redirect response. The page is reloaded and its contents
        // are updated to the state after deletion. It returns 302 response
        // from inside this token handler.
        server.sendHeader("Location", String("http://") + server.client().localIP().toString() + String("/"));
        server.send(302, "text/plain", "");
        server.client().flush();
        server.client().stop();

        // Cancel automatic submission by PageBuilder.
        delPage.cancel();
      }
    }
  }
  return "";
}
//////////////^ Credential End ^//////////

////////////////setup/////////////
void AutoConnect_setup() {
//  delay(1000);


//Ticker for WiFi status
config.ticker = true;
config.tickerPort = 2;  //LED Built in

config.tickerOn = HIGH;
// Set menu title
  config.title = "dogBoX";
// Enable saved past credential by autoReconnect option,
  // even once it is disconnected.
  config.autoReconnect = true;


//Credential setup//
  rootPage.insert(server);    // Instead of server.on("/", ...);
  delPage.insert(server);     // Instead of server.on("/del", ...);

  // Set an address of the credential area.
//  AutoConnectConfig config; //remove here 
  config.boundaryOffset = CREDENTIAL_OFFSET;
//  portal.config(config);

//////////////^ End ^//////////
//------------OTAupdate web browser -------------  
  //-Responder of root page and apply page handled directly from WebServer class.
  server.on("/", []() {
    String content = R"(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
Place the root page with the sketch application.&ensp;
__AC_LINK__
</body>
</html>
    )";
    content.replace("__AC_LINK__", String(AUTOCONNECT_LINK(COG_16)));
    server.send(200, "text/html", content);
  });

  config.ota = AC_OTA_BUILTIN;
//////////////^ End ^//////////
  // Start
  portal.config(config);
  portal.begin();
  Serial.println("WiFi connected: " + WiFi.localIP().toString()); //Credential
  
} //end autconnect setup

//for delay reset after disconnect
unsigned long resetdelay = 100;           //ระยะเวลาที่ต้องการรอ ms //ลดเหลือ 1000
unsigned long last_time = 0;                //ประกาศตัวแปรเป็น global เพื่อเก็บค่าไว้ไม่ให้ reset จากการวนloop

void AutoConnect_loop() {
  portal.handleClient();

  
//wifi disconnect and reset and led กระพิบ 0.1s
   while (WiFi.status() != WL_CONNECTED){
    Serial.print(last_time);
    Serial.print(" Count:");
    Serial.print (millis() - last_time );
    delay(200);
    Serial.println("  Waiting for WiFi connection...");
    flipper.attach(0.1, flip); // flip the pin every 0.1s
    if ( millis() - last_time > resetdelay){
      break; 
//      ESP.reset();
    }
  }//end while
   last_time = millis();
   flipper.detach();
   Serial.println("Out off while loop: AutoConnect Wifi");
   digitalWrite(LED_BUILTIN, LOW);
     
}
