#include "LibEncoder.h"

/*
	This example uses the following arduino's pins.
	encoder 
	--o DT = Pin 3
	--o SCK= Pin 2
	--o switch= Pin 8

	Remember that DT and SCK's pins should have interrupt condition.

*/


void isr();

LibEncoder encoder = LibEncoder( 2, 3, 8, isr);
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
