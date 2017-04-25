#include "uc_anto.h"
#include "uc_mqtt.h"

UCxMQTT mqtt;

void fn_null(String topic ,String msg){}
UCxANTO::anto()
{
	//rx_sub = fn_null; 
}

/*void callback_(String topic ,char *playload,unsigned char length)
{
	//playload[length]=0;
	//String str_data(playload);
	
	//UCxANTO::(*rx_sub)(topic,str_data);
}
*/
void UCxANTO :: begin(String username,String password,String name_)
{
	anto_USER = username;
	anto_PASS = password;
	anto_Thing = name_;
	//func_map(mqtt_sub);
	//mqtt.callback = callback_;
	//gsm.println(F("AT&D0"));
}

bool UCxANTO :: connectServer()
{
	
	do
	{
		gsm.debug(F("Connect Server"));
		gsm.debug(F("wait connect"));
		if(mqtt.DisconnectMQTTServer())
		{
			mqtt.ConnectMQTTServer(ANTO_SERVER ,ANTO_PORT);
		}
		delay(500);
	}
	while(!mqtt.ConnectState());
	gsm.debug(F("Server Connected"));
	unsigned char ret = mqtt.Connect(anto_Thing,anto_USER,anto_PASS);
	Serial.println(mqtt.ConnectReturnCode(ret));
		if(ret==0)
		{
			
			return(true);
		}
		return(false);
}


void UCxANTO :: pub(String channel,String msg)
{
	String dat = "channel/"+anto_USER+"/"+anto_Thing+"/"+channel;
	mqtt.Publish(dat,msg);
}
void UCxANTO :: pub(String channel,int msg)
{
	String dat = "channel/"+anto_USER+"/"+anto_Thing+"/"+channel;
	mqtt.Publish(dat,String(msg));
}
void UCxANTO :: sub(String channel)
{
	String dat = "channel/"+anto_USER+"/"+anto_Thing+"/"+channel;
	mqtt.Subscribe(dat);
}
bool UCxANTO :: loop()
{
	mqtt.MqttLoop();
	return(mqtt.ConnectState());
}

void UCxANTO :: func_map(void (*callback)(String topic ,char *playload,unsigned char length))
{
	mqtt.callback = (*callback);
}
void UCxANTO :: mqtt_sub(String topic ,char *playload,unsigned char length)
{
	
}












































