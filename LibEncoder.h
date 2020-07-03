#ifndef __LIBENCODER_H__
#define __LIBENCODER_H__
#include <Arduino.h>

void isr ();
typedef void FUNC();

class LibEncoder {
public:
    LibEncoder( int8_t pin_a, int8_t pin_b,FUNC *ptr) : PinA ( pin_a), PinB( pin_b ) {
        // Rotary pulses are INPUTs
        pinMode(PinA, INPUT);
        pinMode(PinB, INPUT);
      
        //pinMode(PinA, INPUT_PULLUP);
        //pinMode(PinB, INPUT_PULLUP);
      
        // Switch is floating so use the in-built PULLUP so we don't need a resistor
        pinMode(PinSW, INPUT_PULLUP);
      
        // Attach the routine to service the interrupts
        attachInterrupt(digitalPinToInterrupt(PinA), ptr, LOW);
    };

     void run(){
      static unsigned long lastInterruptTime = 0;
      unsigned long interruptTime = millis();
    
      // If interrupts come faster than 5ms, assume it's a bounce and ignore
      if (interruptTime - lastInterruptTime > 5) {
        if (digitalRead(PinB) == LOW)
        {
          virtualPosition-- ; // Could be -5 or -10
        }
        else {
          virtualPosition++ ; // Could be +5 or +10
        }
    
        // Restrict value from 0 to +100
        //virtualPosition = min(100, max(0, virtualPosition));
    
    
      }
      // Keep track of when we were here last (no more than every 5ms)
      lastInterruptTime = interruptTime;
    
    }

    int getSwitch(){  
        // Is someone pressing the rotary switch?
        if ((!digitalRead(PinSW))) {
          virtualPosition = 50;
          while (!digitalRead(PinSW))
            delay(10);
            //Serial.println("Reset");
          return 1;
        }
        return 0;
    }
    int posChange(){
      if (virtualPosition != lastCount) {
        return 1;
      }
      return 0;
    }
    int getPosition(){
        // If the current rotary switch position has changed then update everything
        if (virtualPosition != lastCount) {
        
          // Write out to serial monitor the value and direction
         // Serial.print(virtualPosition > lastCount ? "Up  :" : "Down:");
         // Serial.println(virtualPosition);
        
          // Keep track of this new value
          lastCount = virtualPosition ;
        }
        return virtualPosition;
    }
  private:
    // Used for generating interrupts using CLK signal
    int PinA = 2;
    
    // Used for reading DT signal
    int PinB = 3;
    
    // Used for the push button switch
    int PinSW = 8;
    
    // Keep track of last rotary value
    int lastCount = 50;
    
    // Updated by the ISR (Interrupt Service Routine)
    volatile int virtualPosition = 50;

};


#endif