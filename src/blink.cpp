/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 


#include <Arduino.h>
#include <stdint.h>

#include "../lib/Ethernet/Ethernet.h"
#include "webserver.h"

/*
 * MAC Address
 */
static uint8_t mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x87, 0xFE };

/* CHANGE THIS TO MATCH YOUR HOST NETWORK.  Most home networks are in
 * the 192.168.0.XXX or 192.168.1.XXX subrange.  Pick an address
 * that's not in use and isn't going to be automatically allocated by
 * DHCP from your router. */
static uint8_t ip[] = { 192, 168, 88, 210 };

/* This creates an instance of the webserver.  By specifying a prefix
 * of "", all pages will be at the root of the server. */
#define PREFIX ""
WebServer webserver(PREFIX, 80);

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 12;
/* commands are functions that get called by the webserver framework
 * they can read any posted data from client, and they output to the
 * server to send data back to the web browser. */

void helloCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  /* this line sends the standard "we're all OK" headers back to the
     browser */
  server.httpSuccess();

  /* if we're handling a GET or POST, we can output our data here.
     For a HEAD request, we just stop after outputting headers. */
  if (type != WebServer::HEAD)
  {
    /* this defines some HTML text in read-only memory aka PROGMEM.
     * This is needed to avoid having the string copied to our limited
     * amount of RAM. */
    P(helloMsg) = "<h1>Hello, World!</h1>";

    /* this is a special form of print that outputs from PROGMEM */
    server.printP(helloMsg);
  }
}


// the setup routine runs once when you press reset:
void setup() {

	  /* initialize the Ethernet adapter */
	  Ethernet.begin(mac, ip);

	  /* setup our default command that will be run when the user accesses
	   * the root page on the server */
	  webserver.setDefaultCommand(&helloCmd);

	  /* run the same command if you try to load /index.html, a common
	   * default page name */
	  webserver.addCommand("index.html", &helloCmd);

	  /* start the webserver */
	  webserver.begin();

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
	  char buff[64];
	  int len = 64;

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(300);               // wait for a second


  /* process incoming connections one at a time forever */
  webserver.processConnection(buff, &len);
}

int main(void)
{
	init();

	setup();

	for (;;)
		loop();

	return 0;
}
