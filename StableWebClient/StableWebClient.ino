/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 modified 9 Apr 2012
 by David A. Mellis
 
 */

#include <SPI.h>
#include <Ethernet.h>


int voicePin = 7;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
//byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE0 };
byte mac[] = {0x0a, 0x00, 0x27, 0xa0, 0x00, 0x01};
byte ip[] = { 192, 168, 10, 61 };
byte dns_server[] = { 192, 168, 201, 197 };
byte gateway[] = { 192, 168, 10, 10 };
byte subnet[] = { 255, 255, 255, 0 };

IPAddress server(192,168,201,197); // Google

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  //}
  
  
  pinMode(voicePin, INPUT);
  Serial.println("serial ok");
  
  // start the Ethernet connection:
  //Ethernet.begin(mac);
  while(true) {
    if(Ethernet.begin(mac)) {
      Serial.println("Ethernet begin ok");
      break;
    }
    Serial.println(Ethernet.localIP());
   
    delay(500);
  }
  //Ethernet.begin(mac, ip, dns_server, gateway, subnet);
  //Ethernet.begin(mac, ip);
 
  Serial.println("ethernet connentcted" );
  Serial.println(Ethernet.localIP());

  // give the Ethernet shield a second to initialize:

  delay(1000);
  Serial.println("connecting...");
  
  if (client) {
    Serial.println("client ok !!!");
  } else {
    Serial.println("client bad");
  }

}




void sendData(int voice, int ir) {
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /testhtml/mr.php?v=" + String(voice) + "&b=2 HTTP/1.1");
    client.println("Host: downloads.zhiwensun.dev.anjuke.com");
    client.println();
  } else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    //for(;;)
      ;
  }
  
}




void loop()
{
  
  
  int voice = digitalRead(voicePin);
  
  Serial.print("voice :");
  Serial.println(voice);
  
  sendData(voice, 1);
  
  
  delay(10000);

  // if the server's disconnected, stop the client:
  /*
  
  */
}

