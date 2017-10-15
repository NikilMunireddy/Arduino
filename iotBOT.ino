#include <SoftwareSerial.h>
SoftwareSerial esp8266(2,3);
#define DEBUG true


//Define pins;  
int R1=11;
int R2=12;
int L1=9;
int L2=10;

void setup()
{
  //Define the pinmode configurations;   
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  Serial.begin(9600);
  esp8266.begin(9600);

 esp8266Data("AT+RST\r\n", 2000, DEBUG); //reset module
  esp8266Data("AT+CWMODE=1\r\n", 1000, DEBUG); //set station mode
  esp8266Data("AT+CWJAP=\"AndroidKushal\",\"abcdefgj\"\r\n", 2000, DEBUG);   //connect wifi network
  while(!esp8266.find("OK")) 
  {
    //wait for connection
  } 
  esp8266Data("AT+CIFSR\r\n", 1000, DEBUG); 
  esp8266Data("AT+CIPMUX=1\r\n", 1000, DEBUG); 
  esp8266Data("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); 

// #80  HTTP PROTOCOL
}
void loop()
{
  if (esp8266.available())  
  {
    if (esp8266.find("+IPD,")) 
    {
      String msg;
      esp8266.find("?"); 
      msg = esp8266.readStringUntil(' '); 
      String command = msg.substring(0, 3); 
      String valueStr = msg.substring(4);   
      int value = valueStr.toInt();         
      if (DEBUG) 
      {
        Serial.println(command);
        Serial.println(value);
      }
      delay(100);
      
     
      //your code goes here
      if(command.equals("BOT"))
      {
        if(value==0){
          digitalWrite(L1,LOW);
          digitalWrite(R1,LOW);
          digitalWrite(L2,LOW);
          digitalWrite(R2,LOW);
        }
          
        else if(value==1){
          digitalWrite(L1,LOW);
          digitalWrite(R1,HIGH);
          digitalWrite(L2,HIGH);
          digitalWrite(R2,LOW); 
        }
        else if(value==2){
          digitalWrite(L1,LOW);
          digitalWrite(R1,LOW);
          digitalWrite(L2,HIGH);
          digitalWrite(R2,LOW); 
        }
        else if(value==3){
          digitalWrite(L1,LOW);
          digitalWrite(R1,HIGH);
          digitalWrite(L2,LOW);
          digitalWrite(R2,LOW); 
        }
        else if(value==7){
          digitalWrite(L1,HIGH);
          digitalWrite(R1,LOW);
          digitalWrite(L2,LOW);
          digitalWrite(R2,LOW); 
        }
        else if(value==8){
          digitalWrite(L1,LOW);
          digitalWrite(R1,LOW);
          digitalWrite(L2,LOW);
          digitalWrite(R2,HIGH); 
        }
        else if(value==4){
          digitalWrite(L1,HIGH);
          digitalWrite(R1,LOW);
          digitalWrite(L2,LOW);
          digitalWrite(R2,HIGH); 
        }
      
      }
    }
  }
}


String esp8266Data(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }
    if (debug)
    {
      Serial.print(response);
    }
    return response;
}
