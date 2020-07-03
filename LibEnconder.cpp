#include "LibEncoder.h"

/*As we nothing here I put an example of usage.
 * 
 * Usage:

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
    Serial.println("key pressed");
  }
  if ( encoder.posChange() > 0 ){
    int i = encoder.getPosition();
    Serial.println(i);
  }
}

 
*/
