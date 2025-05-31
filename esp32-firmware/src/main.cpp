#include <Arduino.h>
#include <keyboard.h>
#include <display.h>
#include <battery.h>


void setup(){
  Serial.begin(115200);
  
  display_init();
  keyboard_init();
}
  
void loop() {
    char key = keyboard_getKey();
    if(key != '\0') {
        Serial.println(key);
    }
}