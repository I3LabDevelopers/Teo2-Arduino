#include "TeoState.h"

#define TIMEOUT_SPEAK 5000
#define TIME_DISTANCE 500

uint32_t distance_to_person, distance_to_person_sum, counter;
InteractionRegion CurrentRegion = Unknown, PastRegion = Unknown;
ContactType lastTouch;
boolean isSpeaking;
unsigned long inactiveTimeStamp, inactiveTime;
long int timeStampSpeak, timeStampDistance;

/*
 This function should be call to update the current state of the Teo through its sensors. 
 Here should be added the function calls related to each sensor.
*/

void TeoStateInit() {
  
  distance_to_person_sum = 0;
  counter = 0;
  timeStampDistance = millis();
  distance_to_person = measure_distance();
  CurrentRegion = determineInteractionRegion(distance_to_person);
  PastRegion = CurrentRegion;
}

void refreshTeoState() {
    refreshDistanceToPerson();
    checkManualCommands();
    updateInactiveTime();
    speechTimeout();
}

void checkManualCommands() {
    while(BTSerial.available() > 0) 
        listenCommand();
}

//==================== DISTANCE RELATED FUNCTIONS =========================
void refreshDistanceToPerson() {

    if (millis()-timeStampDistance < TIME_DISTANCE) {
         
         distance_to_person_sum += measure_distance();
         counter++;

    }
    else {
      distance_to_person = distance_to_person_sum/counter;
      counter = 0;
      distance_to_person_sum = 0;
      timeStampDistance = millis();
      PastRegion = CurrentRegion;        
      CurrentRegion = determineInteractionRegion(distance_to_person);
    }
}

uint16_t distanceToPerson() {
    return distance_to_person;
}

uint8_t determineInteractionRegion(uint16_t _distance) {

    if (_distance < 45) return Intimate;
    if (_distance >= 45 && _distance < 100) return Personal;
    if (_distance >= 100 && _distance < 200) return Social;
    if (_distance >= 200 && _distance < 401) return Public;
    return Unknown;

}

uint8_t getCurrentRegion() {
    return CurrentRegion;
}

uint8_t getPastRegion() {
    return PastRegion;
}

//=================== INACTIVE TIME ======================================

void resetInactiveTimeCounter() {
    inactiveTimeStamp = millis();
    inactiveTime = 0;
}

void updateInactiveTime () {
    inactiveTime = millis() - inactiveTimeStamp;
}

unsigned long getInactiveTime() {
    return inactiveTime;    
}

//=================== VOICE CONTROL ======================================

void endOfSpeech() {
    isSpeaking = false;
}

void setIsSpeaking(boolean x) {
    timeStampSpeak = millis();
    isSpeaking = x;
}
boolean isTeoSpeaking() {
    return isSpeaking;
}

void speechTimeout() {
    if (millis() - timeStampSpeak > TIMEOUT_SPEAK)
      endOfSpeech(); 
}