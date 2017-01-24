#include "TeoState.h"

#define TIMEOUT_SPEAK 5000
#define TIME_DISTANCE 500
#define TOUCH_THRESHOLD 600
#define CALL_THRESHOLD (0.3*255)

#define MIC1_PIN A5
#define FSR_PIN1 9
#define FSR_PIN2 10
#define FSR_PIN3 11
#define FSR_PIN4 14
#define FSR_PIN5 15

uint32_t distance_to_person, distance_to_person_sum, counter;
InteractionRegion CurrentRegion = Unknown, PastRegion = Unknown;

int fsrPin[5] = {FSR_PIN1, FSR_PIN2, FSR_PIN3, FSR_PIN4, FSR_PIN5};
int lastTouch[5];
boolean isTouched; //it is true if at least one fsr has been touched

byte lastHearing;
boolean isCalled; //it is true if the mic1 has sensed

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
    refreshHearing();
    refreshTouch();
    refreshDistanceToPerson();
    checkManualCommands();
    updateInactiveTime();
    speechTimeout();
}

void checkManualCommands() {
    while(BTSerial.available() > 0) 
        listenCommand();
}
    
//==================== HEARING RELATED FUNCTIONS =========================
//it refreshes lastHearing and isCalled
void refreshHearing(){
    lastHearing = analogRead(MIC1_PIN);
    isCalled = ((lastHearing) >> 2 > CALL_THRESHOLD);
#ifdef BTDEBUG
    if isCalled
        BTSerial.println(F("Called! Hearing value: " + String(lastHearing)));
#endif

}

//==================== TOUCH RELATED FUNCTIONS =========================
//it refreshes lastTouch[] and isTouched
void refreshTouch(){
  int currentTouch[5];
  for(int i=0; i<5; i++){
    //sensing
    currentTouch[i] = analogRead(fsrPin[i]);

    //comparing to the previous sensing
    isTouched = (isTouched || (lastTouch[i]-currentTouch[i]) > TOUCH_THRESHOLD);

#ifdef BTDEBUG
    if isTouched
      BTSerial.println(F("Touched!" + "Touch value of FSR" + String(i) +": " + String(currentTouch[i])));
#endif

    //refresh
    lastTouch[i] = currentTouch[i];
  }
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