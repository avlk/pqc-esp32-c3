#include "Arduino.h"
  
void setup() {
  // Declare la broche sur laquelle la LED est  
  // reliee comme une sortie
  pinMode(LED_BUILTIN, OUTPUT);
}
   
void loop() {
  // Passer le sortie à l'état HAUT pour allumer la LED
  digitalWrite(LED_BUILTIN, HIGH);
     
  // Attendre 1 seconde, pendant ce temps la LED reste allumee
  delay(1000);
     
  // Passer le sortie à l'état BAS pour eteindre la LED
  digitalWrite(LED_BUILTIN, LOW);    
   
  // Attendre 1 seconde, pendant ce temps la LED reste donc éteinte
  delay(1000);
}