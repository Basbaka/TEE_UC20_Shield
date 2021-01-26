#include "esp32_TEE_UC20.h"
#include "esp32_internet.h"
#include "esp32_tcp.h"

INTERNET net;
TCP tcp;

//SIM TRUE  internet
#define APN "internet"
#define USER ""
#define PASS ""


void debug(String data)
{
  Serial.println(data);
}
void setup() 
{
  Serial.begin(115200);
  gsm.begin(&Serial2,115200);
  gsm.Event_debug = debug;
  Serial.println(F("UC20"));
  gsm.PowerOn(); 
  while(gsm.WaitReady()){}
 
  Serial.print(F("GetOperator --> "));
  Serial.println(gsm.GetOperator());
  Serial.print(F("SignalQuality --> "));
  Serial.println(gsm.SignalQuality());
  
  Serial.println(F("Disconnect net"));
  net.DisConnect();
  Serial.println(F("Set APN and Password"));
  net.Configure(APN,USER,PASS);
  Serial.println(F("Connect net"));
  net.Connect();
  Serial.println(F("Show My IP"));
  Serial.println(net.GetIP());

  open_tcp();
  send_tcp(); 
}
void loop() 
{
   if(tcp.ReceiveAvailable())
    {
      int len = tcp.ReadBuffer();
      Serial.println(len);
      while(len)
      {
        if(gsm.available())
        {
          Serial.write(gsm.read());
          len--;
        }
      }
     Serial.println();
     Serial.println("Finish");
     while(!tcp.Close()){}
     Serial.println(F("Disconnect net"));
     net.DisConnect();
    }
  
}
void send_tcp()
{
  if(tcp.StartSend())
   {
      Serial.println("HTTP GET");
      tcp.print("GET /");
      tcp.println(" HTTP/1.1");
      tcp.println("Host: www.google.co.th");
      tcp.println("");
      tcp.println("");
      tcp.StopSend();
      Serial.println("Stop");
   } 
}
void open_tcp()
{
  Serial.println();  
  Serial.println(F("Connect Server")); 
  bool ret = tcp.Open("www.google.co.th","80");  
}
