#include <EthernetBonjourClass.h>


// Create a UDP service for use by MDNS
UDP udp;

// Create a TCP/HTTP service for local discovery and HAP accessory handling
TCPServer server = TCPServer(80);

// Create a EthernetBonjour service for MDNS registration & discovery
EthernetBonjourClass EthernetBonjour;


void setup() {
  Particle.publish("EthernetBonjour Setup");

  String localIP = WiFi.localIP();
  Particle.publish("Announced from ", localIP );
  
  WiFi.connect();

  server.begin();

  // Initialize EthernetBonjour service with local UDP reference
  EthernetBonjour.setUDP( &udp );
  
  // Begin MDNS registration servcie with the name of the HAP accessory (will appear in Apple Home)
  EthernetBonjour.begin("particle");

  // Start MDNS registration with TCP based service, using special HAP TXT records encoded as c-string
  EthernetBonjour.addServiceRecord("particle._hap",
                                   80,
                                   MDNSServiceTCP,
                                   "\x4sf=1\x14id=3C:33:1B:21:B3:00\x6pv=1.0\x04\c#=1\x04s#=1\x4\ff=0\x04sf=1\x0Bmd=particle");

}


void loop() {

  // Process MDNS UDP traffic once per loop
  EthernetBonjour.run();
  
  // Check on TCP client status
  TCPClient client = server.available();

  if (client){
    // If available, read to the end of the TCP stream, ignore stream content in this demo
    while (client.read() != -1);

    Particle.publish("EthernetBonjour Read Client");

    client.write("HTTP/1.1 200 Ok\n\n<html><body><h1>Bonjour!</h1></body></html>\n\n");
    client.flush();
    delay(5);
    client.stop();

  }

}

