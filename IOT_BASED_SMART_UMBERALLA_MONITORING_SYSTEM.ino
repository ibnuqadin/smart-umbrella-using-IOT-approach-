#include <Arduino.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
int lightreadval; 
//all sensors need system
 #include<Servo.h>

//inicialize all pins
int ligthdrpin =A0;
int blue_led=12;
#define ledPin 13
 #include<Servo.h>
int servopin = 16;
Servo Myservo;
int rainval;

#define sensorPin 14
 

// Replace with your network credentials
const char* ssid = "Abdulla";
const char* password = "00001234";

// Replace with your Firebase project credentials
#define FIREBASE_HOST "https://on-off-mood-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "D9WJr5GZfRZ5Yhw8FIDwTlugKnMZQN2nYC9cD5qH"

// Replace with the path to your database table
#define DATABASE_PATH "/umbrellaContrlling/switch"

// Pin connected to the LED (switch) - Change the pin number as needed


// Initialize Firebase data object
FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
 //declare all pins
  pinMode(ledPin, OUTPUT);
    pinMode(blue_led, OUTPUT);
  Myservo.attach(servopin);
  pinMode(ligthdrpin,INPUT); 
  Myservo.attach(servopin);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
  
  // Begin Firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  // Enable auto reconnect
  Firebase.reconnectWiFi(true);
}

void loop() {
  bool switchValue;
  // Read data from Firebase Realtime Database
  if (Firebase.getBool(firebaseData, DATABASE_PATH)) {
    if (firebaseData.dataType() == "boolean") {
      bool switchValue = firebaseData.boolData();
//      Serial.print("Switch Value: ");
  
      Serial.println(switchValue);
//      // Control the LED based on the switch value
//      digitalWrite(ledPin, switchValue ? HIGH : LOW);
        lightreadval= analogRead(ligthdrpin);
rainval = digitalRead(sensorPin);
Serial.println(lightreadval);

  if (rainval == LOW || lightreadval  <=  602 || switchValue == 1){

    
      Myservo.write(-180);
      digitalWrite(ledPin,LOW);
      digitalWrite(blue_led,HIGH);
      //Myservo.write(0);
     
      }  
   
    
else  if (rainval == HIGH || switchValue == 0){
    

      Myservo.write(180);
      digitalWrite(ledPin,HIGH);
       digitalWrite(blue_led,LOW);

    }
    
//   else if(switchValue == 1){
//       Myservo.write(-180);
//      digitalWrite(ledPin,LOW);
//      digitalWrite(blue_led,HIGH);
//      }
//     
//      
//    else if(switchValue == 0){
//        
//        Myservo.write(180);
//      digitalWrite(ledPin,HIGH);
//       digitalWrite(blue_led,LOW);
//
//        }
      
      
    
  else {
      Myservo.write(180);
      digitalWrite(ledPin,HIGH);
      digitalWrite(blue_led,LOW);
      //Myservo.write(0);

    }
    }
    if(switchValue == 0){
      Serial.println("ookiyaale");
    }
  }
  else {
    // Failed to get data from Firebase
    Serial.println("Error: " + firebaseData.errorReason());
  }

  // Add some delay to avoid excessive reads
//  delay(2000);
  

//     Serial.print(switchValue);
}
