#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>


const int Ping = D7; //trigger - sends sound out to measure distance
const int Receive = D5; //Echo - Receives sound from trigger to measure travel time (microsec)
long TimeTravel;   //2 bit integer
int distance;      //1 bit integer

// ##### Wifi Connection Setup #### //
char WifiName[] = "Verizon-SM-G935V";            //SSID
char Password[] = "password";

void setup() {
  // put your setup code here, to run once:
  pinMode (Ping, OUTPUT);  
  pinMode(Receive, INPUT);    
  Serial.begin(9600);       //Begin serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Ping,LOW);    //Clear
  delayMicroseconds (2);
  digitalWrite(Ping,HIGH);    //Send out sound
  delayMicroseconds (10);       
  digitalWrite(Ping,LOW);     //Clear again
  
  TimeTravel = pulseIn (Receive,HIGH);       //Get the input of Receive
  distance = (TimeTravel*0.034)/2;          //converts time to cm
  if (distance > 0){                        // in cm
    if (distance > 10){
      Serial.println("Green - Too far");
    }
    else if (distance < 10 && distance > 5){
      Serial.println("Yellow - Getting Close");
    }
    else if (distance == 5) {
      Serial.println ("Red - Perfect");
    }
    else if (distance < 5){
      Serial.println ("Flash Green - Too close");
    }
  }
    
}
