#include <Servo.h>

Servo leServo; // on définit un objet Servo nommé leServo
int pos=0;
int pinServo=9; // variable pour stocker le pin servo moteur
// capteur magnetique
float hall;
float hall2;
void setup() {
  // SERVO MOTEUR INITIALISATION
  leServo.attach(pinServo); // on relie l'objet au pin de commande
  // leds  
  pinMode(A0,INPUT);
pinMode(A5,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
Serial.begin(9600);
}

void loop() {
TournerPoulie();
}
void TournerPoulie(){
  hall = analogRead(A0);
hall2 = analogRead(A5);
Serial.print(hall);Serial.print(" ");Serial.println(hall2);
  if (hall >= 530  ){
        leServo.write(0);
          hall = analogRead(A0);
     hall2 = analogRead(A5);
     Serial.print(180);Serial.print(hall);Serial.print(" ");Serial.println(hall2);
  }
  if(hall2 >= 530){

          leServo.write(180);
            hall = analogRead(A0);
          hall2 = analogRead(A5);
Serial.print(0);Serial.print(hall);Serial.print(" ");Serial.println(hall2);
}
}
