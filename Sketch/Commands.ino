#ifdef BTSerial
SerialCommand CommandHandler;
#else
SoftwareSerial BTSerial(RX_PIN, TX_PIN);
SerialCommand CommandHandler(BTSerial);
#endif

void setCommandToExecute (boolean (*cmd)());    // Because randomly the compiler says this function is out of scope..

//Initialization
void serialCommInit() {
  Serial.begin(9600);
  Serial.println(F("Init!"));
}

void BTCommInit() {
  BTSerial.begin(9600);
  CommandHandler.addCommand("move", moveHandler);
  CommandHandler.addCommand("idle", idleMoodHandler);
  CommandHandler.addCommand("happy", happyMoodHandler);
  CommandHandler.addCommand("sad", sadMoodHandler);
  CommandHandler.addCommand("angry", angryMoodHandler);
  CommandHandler.addCommand("scared", scaredMoodHandler);
  CommandHandler.addCommand("auto", activateBehaviors);
  CommandHandler.addCommand("endofsound", endOfSpeech);
  
  CommandHandler.addDefaultHandler(unrecognized);
#ifdef BTDEBUG
  BTSerial.println(F("Init!");
#endif
}



void ready() {
  BTSerial.println(F("ready"));
}

//Update call
void listenCommand() {
  CommandHandler.readSerial();
}

// Callbacks

void activateBehaviors () {
    char* args;
    args = CommandHandler.next();
    if (args != NULL){
        if (strcmp("on",args) == 0){
            turnOnBehaviors(true);
        }
        else if (strcmp("off",args) == 0) {
            turnOnBehaviors(false);
        }
    }
            
}

void moveHandler() {
  char* args;
  float params[3];
  uint8_t i, j;


  for (i = 0, j = 0; i < 3; i++) {
    args = CommandHandler.next();
    if (args != NULL) {
      params[i] = atof(args);
      j++;
    }
  }

  if (j == 3) {
    setMovementParams(params[0], params[1], params[2]);
    if (params[0] == 0 && params[1] == 0 && params[2] == 0) {
      executeManualMovement();
      return;  
    }
    else if (!isBehaviorExecuting()){
      setCommandReceived(true);
      setCommandToExecute(executeManualMovement);  
    }
  }

  else setCommandReceived(false);
}

void idleMoodHandler() {
     setCommandReceived(true);
     setCommandToExecute(idleBehavior);
}

void happyMoodHandler() {
     setCommandReceived(true);
     setCommandToExecute(happyBehavior);
}

void sadMoodHandler() {
     
     setCommandReceived(true);
     setCommandToExecute(sadBehavior);  
}

void angryMoodHandler() {
     setCommandReceived(true);
     setCommandToExecute(angryBehavior);  
}

void scaredMoodHandler() {
     setCommandReceived(true);
     setCommandToExecute(scaredBehavior);   
}

void unrecognized() {
#ifdef BTDEBUG
  BTSerial.println(F("Command not recognized"));
#endif
  return;
}

void speak(char* phrase) {
    BTSerial.print("say ");
    BTSerial.println(phrase);
    setIsSpeaking(true);  
}


//void serialEvent3() {
//  while (BTSerial.available() > 0)
//    listenCommand();
//}
