# EthernetBonjour

A Particle library for IP based MDNS services, for use with Apple's HomeKit.

## Background

This Particle.io library is a port of the `EthernetBonjour` service for Arduino, copyright (C) 2010 Georg Kaindl. [http://gkaindl.com](http://gkaindl.com).


## Usage

Connect Photon hardware, add the EthernetBonjour library to your project and follow this simple example:

```
// Create a UDP service for use by MDNS
UDP udp;

// Create a TCP/HTTP service for local discovery and HAP accessory handling
TCPServer server = TCPServer(80);

// Create a EthernetBonjour service for MDNS registration & discovery
EthernetBonjourClass Bonjour;


void setup() {
  Particle.publish("EthernetBonjour Setup");

  String localIP = WiFi.localIP();
  Particle.publish("Announced from ", localIP );
  
  WiFi.connect();

  server.begin();

  // Initialize EthernetBonjour service with local UDP reference
  Bonjour.setUDP( &udp );
  
  // Begin MDNS registration servcie with the name of the HAP accessory (will appear in Apple Home)
  Bonjour.begin("particle");

  // Start MDNS registration with TCP based service, using special HAP TXT records encoded as c-string
  Bonjour.addServiceRecord("particle._hap",
                                   80,
                                   MDNSServiceTCP,
                                   "\x4sf=1\x14id=3C:33:1B:21:B3:00\x6pv=1.0\x04\c#=1\x04s#=1\x4\ff=0\x04sf=1\x0Bmd=particle");

}


void loop() {

  // Process MDNS UDP traffic once per loop
  Bonjour.run();
}
```

See the [examples](examples) folder for more details.

## Documentation

More information online at GitHub [https://github.com/moflo/EthernetBonjourParticle](https://github.com/moflo/EthernetBonjourParticle)


## LICENSE
Copyright (c) 2017 @moflome, copyright (C) 2010 Georg Kaindl.

EthernetBonjour is free software: you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

EthernetBonjour is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with EthernetBonjour. If not, see
<http://www.gnu.org/licenses/>.
