/* 
 
 Created by:- Rishi Tiwari
 Website:- TrickSumo.com
 Video Tutorial:- https://youtu.be/nLzC0-VaqDs
 
 Libraries used:- 

https://github.com/mobizt/Firebase-ESP8266/

*/
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>                         
//#include <FirebaseArduino.h>
#define FIREBASE_HOST "home-automation-system-fbeeb-default-rtdb.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "umxcReJXexsKcyTdHD4tv7ffQjHIKab0BcUAdZJL" //Your Firebase Database Secret goes here
#define WIFI_SSID "PTCL"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "ham03118123547"                                      //Password of your wifi network 
 

// Declare the Firebase Data object in the global scope
FirebaseData Relay1data,Relay2data,Relay3data,Relay4data,opened,closed;


#define Relay1 12 //D6
#define Relay2 14 //D5 
#define Relay3 4  //D1
#define Relay4 5 //D2

void setup() {
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  pinMode(Relay4,OUTPUT);
 
  Serial.begin(9600);                                                      // Select the same baud rate if you want to see the datas on Serial Monitor
  Serial.println("Serial communication started\n\n");  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase
  Firebase.reconnectWiFi(true);
  delay(0);


Firebase.setString(opened,"/Home_Automation/open","true");
Firebase.setString(closed,"/Home_Automation/close","false");
Firebase.getString(opened,"/Home_Automation/open");
Firebase.getString(closed,"/Home_Automation/close"); 
}


void loop() {
//Firebase.getString(opened,"/Home_Automation/open");
//Firebase.getString(closed,"/Home_Automation/close");
Firebase.getString(Relay1data, "/Home_Automation/S1");
Firebase.getString(Relay2data, "/Home_Automation/S2");
Firebase.getString(Relay3data, "/Home_Automation/S3");
Firebase.getString(Relay4data, "/Home_Automation/S4");

if (Relay1data.stringData() == opened.stringData())                            
    {
      Serial.println("Relay1 is ON ");
      digitalWrite(Relay1,HIGH);
    }
   else 
   {
    Serial.println("Relay1 is OFF");
    digitalWrite(Relay1,LOW);
  }
if (Relay2data.stringData() == opened.stringData())                             // print read data if it is integer
    {  Serial.println("Relay2 is ON");
      digitalWrite(Relay2,HIGH);  
    }
    else
    {
    Serial.println("Relay2 is OFF");
    digitalWrite(Relay2,LOW);
     }

if (Relay3data.stringData() == opened.stringData())                             // print read data if it is integer
    {
      Serial.println("Relay3 is ON");
      digitalWrite(Relay3,HIGH); 
    }
   else 
   {
    Serial.println("Relay3 is OFF");
      digitalWrite(Relay3,LOW);
  }

if (Relay4data.stringData() == opened.stringData())                             // print read data if it is integer
    {
      Serial.println("Relay4 is ON");
      digitalWrite(Relay4,HIGH); 
    }
   else 
   {
    Serial.println("Relay4 is OFF");
    digitalWrite(Relay4,LOW);
  }

 Serial.println();
 }


/* NOTE:
 *  To read value, command is ===> Firebase.getInt(firebaseData, "path"); variable = firebaseData.intData();
 *  
 *  Example                   ===>  Firebase.setInt(firebaseData, "/data", val); val = firebaseData.intData();
 */
          
