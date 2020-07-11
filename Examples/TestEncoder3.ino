/*
This code you gonna havean increment of 10 for your potentiometer and a range from 0 to 255.


*/

#include <LibEncoder.h>


void isr();

LibEncoder encoder = LibEncoder( 2, 3, 8, isr);

void isr(){
  encoder.run();
}


void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  encoder.setIncrement(10);
  encoder.setTopRange(255);
}

void loop() {
  if( encoder.getSwitch() > 0 ){
    Serial.println("Tecla pressionada");
  }
  if ( encoder.posChange() > 0 ){
    int i = encoder.getPosition();
    MyPot.setWiper(i);
    Serial.println(i);
  }  
  delay(150);
}