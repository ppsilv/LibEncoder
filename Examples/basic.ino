#include "LibEncoder.h"

void isr();

LibEncoder encoder = LibEncoder( 2, 3, isr);
void isr(){
  encoder.run();
}

void setup(){
  Serial.begin(9600);
  Serial.println("Start");
}

void loop(){

  if( encoder.getSwitch() > 0 ){
    Serial.println("Tecla pressionada");
  }
  if ( encoder.posChange() > 0 ){
    int i = encoder.getPosition();
    Serial.println(i);
  }
}
