
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include "error_state.h"
#include "voice_module.h"



VR myVR(13, 12);
uint8_t records[7]; // save record
uint8_t buf[64];


ES_t voice_module_init(void){
  
  // Initialize SoftwareSerial for VR Module
  myVR.begin(9600);
  
  if(myVR.clear() != 0){
    return ES_NOT_OK;
  }

  delay(100);
  
  if(myVR.load((uint8_t)FORWARD) < 0){
    return ES_NOT_OK;
  }
  
  if(myVR.load((uint8_t)BACKWARD) < 0){
    return ES_NOT_OK;
  }
  
  if(myVR.load((uint8_t)STOP) < 0){
    return ES_NOT_OK;
  }
  
  
  if(myVR.load((uint8_t)LEFT) < 0){
    return ES_NOT_OK;
  }
  

  if(myVR.load((uint8_t)RIGHT) < 0){
    return ES_NOT_OK;
  }

  delay(500);

  return ES_OK;  
}


int  voice_module_recognize(void){
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    return buf[1];
  }
  
}
