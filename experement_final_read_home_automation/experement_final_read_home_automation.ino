/* 
 
 Created by:- Rishi Tiwari
 Website:- TrickSumo.com
 Video Tutorial:- https://youtu.be/nLzC0-VaqDs
 
 Libraries used:- 

https://github.com/mobizt/Firebase-ESP8266/

*/

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
                          
#define FIREBASE_HOST "ha-system-43995-default-rtdb.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "sSZwOmreZe10FMvvr4Ki2BcxyHpjg4qgP0QS1QQT" //Your Firebase Database Secret goes here

#define WIFI_SSID "PTCL"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "ham03118123547"                                      //Password of your wifi network 
 

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

// Declare global variable to store value
int val=0;


void setup() {

  Serial.begin(9600);                                                      // Select the same baud rate if you want to see the datas on Serial Monitor
  pinMode(16, OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(0,OUTPUT);
  
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
}

void loop() {


// Firebase Error Handling And Reading Data From Specified Path ************************************************

if (Firebase.getInt(firebaseData, "/data")) {                           // On successful Read operation, function returns 1  

    if (firebaseData.dataType() == "int") {                            // print read data if it is integer

      val = firebaseData.intData();
      if (val==1){
        digitalWrite(16, LOW);
      }
              else if(val==11){
          digitalWrite(5,LOW);
          }
          
                else if(val==111){
            digitalWrite(4, LOW);
            }

                  else if(val==1111){
              digitalWrite(0, LOW);
              }
                  else if(val==51){
                    digitalWrite(16,LOW);
                    digitalWrite(5,LOW);
                    digitalWrite(4,LOW);
                    digitalWrite(0,LOW);
                    }
              
          
      
        
        if (val==0){
          digitalWrite(16, HIGH);
        }
          else if(val==2){
            digitalWrite(5,HIGH);
            }
            else if(val==3){
              digitalWrite(4, HIGH);
              }
              else if(val==4){
                digitalWrite(0, HIGH);
                } 
                else if(val==5){
                  digitalWrite(16,HIGH);
                  digitalWrite(5,HIGH);
                  digitalWrite(4,HIGH);
                  digitalWrite(0,HIGH);
                  }
           
            
          
              
              
          
         
         
         
          
        
          
           
       
        
      Serial.println(val);
      Serial.println("\n Change value at firebase console to see changes here."); 
      delay(0);
      
    }

} else {
    Serial.println(firebaseData.errorReason());
  }
 }


/* NOTE:
 *  To read value, command is ===> Firebase.getInt(firebaseData, "path"); variable = firebaseData.intData();
 *  
 *  Example                   ===>  Firebase.setInt(firebaseData, "/data", val); val = firebaseData.intData();
 */
          
