// =============== MOOD SETTERS ========================

void setIdleMood() {
#ifdef BTDEBUG
  BTSerial.println(F("Mood changing to idle..."));
#endif
  moodState = idle;
}

void setHappyMood() {
#ifdef BTDEBUG
  BTSerial.println(F("Mood changing to happy..."));
#endif
  moodState = happy;
}

void setSadMood() {
#ifdef BTDEBUG
  BTSerial.println(F("Mood changing to sad..."));
#endif
  moodState = sad;
}

void setAngryMood() {
#ifdef BTDEBUG
  BTSerial.println(F("Mood changing to angry..."));
#endif
  moodState = angry;
}

void setScaredMood() {
#ifdef BTDEBUG
  BTSerial.println(F("Mood changing to scared..."));
#endif
  moodState = scared;
}

//==================== MOOD BEHAVIORS ==================

boolean executeIdleBehavior() {
  setIdleMood();
  drawFace(); //it forces the refresh of the face led matrix
  return true;
}

enum happyMovementStates {
  happyInit, happyRotateLeft, happyRotateRight, happyRotateToInitialPosition, happyCheckMovement, happyFinish
};
happyMovementStates happyMovementState, pastHappyMovementState;

void initHappyMovement() {
  happyMovementState = happyInit;
}

boolean executeHappyBehavior() {

  switch (happyMovementState) {
    case happyInit:
      setHappyMood();
      drawFace(); //it forces the refresh of the face led matrix
      happyMovementState = happyRotateLeft;
      break;

    case happyRotateLeft:
      if (!positionCommanded()) {
        rotate(-30.0f, 5.0f);
        happyMovementState = happyCheckMovement;
        pastHappyMovementState = happyRotateLeft;
      }
      break;

    case happyRotateRight:
      if (!positionCommanded()) {
        rotate(60.0f, 5.0f);
        happyMovementState = happyCheckMovement;
        pastHappyMovementState = happyRotateRight;
      }
      break;

    case happyRotateToInitialPosition:
      if (!positionCommanded()) {
        rotate(-30.0f, 5.0f);
        happyMovementState = happyCheckMovement;
        pastHappyMovementState = happyRotateToInitialPosition;
      }
      break;

    case happyCheckMovement:
      refreshPositionControl();
      if (!positionCommanded()) {
        if (pastHappyMovementState == happyRotateLeft)
          happyMovementState = happyRotateRight;
        else if (pastHappyMovementState == happyRotateRight)
          happyMovementState = happyRotateToInitialPosition;
        else
          happyMovementState = happyFinish;
      }
      break;

    case happyFinish:
      if (!isMoving() && !isTeoSpeaking())
        BTSerial.println("end motion");
      return true;
      break;
  }

  return false;
}

enum sadMovementStates {
  sadInit, sadRotate, sadCheckMovement, sadFinish
};
sadMovementStates sadMovementState, pastSadMovementState;

void initSadMovement() {
  sadMovementState = sadInit;
}

boolean executeSadBehavior() {

  switch (sadMovementState) {
    case sadInit:
      setSadMood();
      drawFace(); //it forces the refresh of the face led matrix
      sadMovementState = sadRotate;
      break;

    case sadRotate:
      if (!positionCommanded()) {
        rotate(180.0f, 5.0f);
        sadMovementState = sadCheckMovement;
        pastSadMovementState = sadRotate;
      }
      break;

    case sadCheckMovement:
      refreshPositionControl();
      if (!positionCommanded()) {
        if (pastSadMovementState == sadRotate)
          sadMovementState = sadFinish;
      }
      break;

    case sadFinish:
      if (!isMoving() && !isTeoSpeaking())
        BTSerial.println("end motion");
      return true;
      break;
  }

  return false;
}


enum angryMovementStates {
  angryInit, angryForward, angryVibration, angryCheckMovement, angryFinish
};
angryMovementStates angryMovementState, pastAngryMovementState;

void initAngryMovement() {
  angryMovementState = angryInit;
}

boolean executeAngryBehavior() {
  static uint8_t angryVibrationCount; //it determines how many times the vibrations occur in the angry behavior movement

  switch (angryMovementState) {
    case angryInit:
      setAngryMood();
      drawFace(); //it forces the refresh of the face led matrix
      angryMovementState = angryForward;
      angryVibrationCount = 5;
      break;

    case angryForward:
      if (!positionCommanded()) {
        moveForward(0.4f, 1.0f);
        angryMovementState = angryCheckMovement;
        pastAngryMovementState = angryForward;
      }
      break;

    case angryVibration:
      if (!positionCommanded()) {
        angryVibrationCount--;  //the vibration stops when angryVibrationCount becomes equal to 0
        moveLateral(0.01f, 2.0f);
        moveLateral(-0.01f, 2.0f);
        angryMovementState = angryCheckMovement;
        pastAngryMovementState = angryVibration;
      }
      break;

    case angryCheckMovement:
      refreshPositionControl();
      if (!positionCommanded()) {
        if (pastAngryMovementState == angryForward)
          angryMovementState = angryVibration;
        else if ((pastAngryMovementState == angryVibration) && (angryVibrationCount > 0))
              angryMovementState = angryVibration;
        else
          angryMovementState = angryFinish;
      }
      break;

    case angryFinish:
      if (!isMoving() && !isTeoSpeaking())
        BTSerial.println("end motion");
      return true;
      break;
  }

  return false;
}

enum scaredMovementStates {
  scaredInit, scaredBackward, scaredVibration, scaredCheckMovement, scaredFinish
};
scaredMovementStates scaredMovementState, pastScaredMovementState;

void initScaredMovement() {
  scaredMovementState = scaredInit;
}

boolean executeScaredBehavior() {
  static uint8_t scaredVibrationCount; //it determines how many times the vibrations occur in the angry behavior movement

  switch (scaredMovementState) {
    case scaredInit:
      setScaredMood();
      drawFace(); //it forces the refresh of the face led matrix
      scaredMovementState = scaredBackward;
      scaredVibrationCount = 3;
      break;

    case scaredBackward:
      if (!positionCommanded()) {
        moveForward(-0.2f, 1.0f);
        scaredMovementState = scaredCheckMovement;
        pastScaredMovementState = scaredBackward;
      }
      break;

    case scaredVibration:
      if (!positionCommanded()) {
        scaredVibrationCount--;  //the vibration stops when scaredVibrationCount becomes equal to 0
        moveLateral(0.01f, 2.0f);
        moveLateral(-0.01f, 2.0f);
        scaredMovementState = scaredCheckMovement;
        pastScaredMovementState = scaredVibration;
      }
      break;

    case scaredCheckMovement:
      refreshPositionControl();
      if (!positionCommanded()) {
        if (pastScaredMovementState == scaredBackward)
          scaredMovementState = scaredVibration;
        else if ((pastScaredMovementState == scaredVibration) && (scaredVibrationCount > 0))
              scaredMovementState = scaredVibration;
        else
          scaredMovementState = scaredFinish;
      }
      break;

    case scaredFinish:
      if (!isMoving() && !isTeoSpeaking())
        BTSerial.println("end motion");
      return true;
      break;
  }

  return false;
}
