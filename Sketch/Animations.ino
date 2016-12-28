//Animation states in happy mood
enum HappyAnimationStateEnum {
  happyCenter = 0,
  happyLeft = 1,
  happyRight = 2,
  happyClosed = 3
};
HappyAnimationStateEnum happyAnimationState = happyCenter;

//Animation states in sad mood
enum SadAnimationStateEnum {
  sadCenter = 0,
  sadLeft = 1,
  sadRight = 2,
  sadClosed = 3
};
SadAnimationStateEnum sadAnimationState = sadCenter;

//Animation states in angry mood
enum AngryAnimationStateEnum {
  angryCenter = 0,
  angryLeft = 1,
  angryRight = 2,
  angryClosed = 3
};
AngryAnimationStateEnum angryAnimationState = angryCenter;

//Animation states in scared mood
enum ScaredAnimationStateEnum {
  scaredCenter = 0,
  scaredLeft = 1,
  scaredRight = 2,
  scaredClosed = 3
};
ScaredAnimationStateEnum scaredAnimationState = scaredCenter;


//It draws the eyes randomly choosing between center, right or left side
void animateEyes() {
#ifdef BTDEBUG
  BTSerial.println("Eyes animation...");
#endif
  switch (moodState) {
    case happy:
#ifdef BTDEBUG
      BTSerial.println("Happy eyes animation...");
#endif
      happyAnimationState = (rand() % 3); //random happyCenter/happyLeft/happyRight
      break;

    case sad:
#ifdef BTDEBUG
      BTSerial.println("Sad eyes animation...");
#endif
      sadAnimationState = (rand() % 3); //random sadCenter/sadLeft/sadRight
      break;

    case angry:
#ifdef BTDEBUG
      BTSerial.println("Angry eyes animation...");
#endif
      angryAnimationState = (rand() % 3); //random angryCenter/angryLeft/angryRight
      break;

    case scared:
#ifdef BTDEBUG
      BTSerial.println("Scared eyes animation...");
#endif
      scaredAnimationState = (rand() % 3); //random scaredCenter/scaredLeft/scaredRight
      break;
  }

  drawFace();
}

//It draws the eyelashes randomly choosing between closed and open
void animateEyelashes() {
#ifdef BTDEBUG
  BTSerial.println("Eyelashes animation...");
#endif
  switch (moodState) {
    case happy:
#ifdef BTDEBUG
      BTSerial.println("Happy eyelashes animation...");
#endif
      //random blink/no blink (3/0)
      if (((rand() % 2) * 3) == happyClosed) {
        HappyAnimationStateEnum lastHappyAnimationState = happyAnimationState;
        happyAnimationState = happyClosed;
        //blink
        for (int i = 0; i < 10; i++) {
          drawFace();
        }
        //the eyelashes return to the previous state
        happyAnimationState = lastHappyAnimationState;
      }
      break;

    case sad:
#ifdef BTDEBUG
      BTSerial.println("Sad eyelashes animation...");
#endif
      //random blink/no blink (3/0)
      if (((rand() % 2) * 3) == sadClosed) {
        SadAnimationStateEnum lastSadAnimationState = sadAnimationState;
        sadAnimationState = sadClosed;
        //blink
        for (int i = 0; i < 10; i++) {
          drawFace();
        }
        //the eyelashes return to the previous state
        sadAnimationState = lastSadAnimationState;
      }
      break;

    case angry:
#ifdef BTDEBUG
      BTSerial.println("Angry eyelashes animation...");
#endif
      //random blink/no blink (3/0)
      if (((rand() % 2) * 3) == angryClosed) {
        AngryAnimationStateEnum lastAngryAnimationState = angryAnimationState;
        angryAnimationState = angryClosed;
        //blink
        for (int i = 0; i < 10; i++) {
          drawFace();
        }
        //the eyelashes return to the previous state
        angryAnimationState = lastAngryAnimationState;
      }
      break;

    case scared:
#ifdef BTDEBUG
      BTSerial.println("Scared eyelashes animation...");
#endif
      //random blink/no blink (3/0)
      if (((rand() % 2) * 3) == scaredClosed) {
        ScaredAnimationStateEnum lastScaredAnimationState = scaredAnimationState;
        scaredAnimationState = scaredClosed;
        //blink
        for (int i = 0; i < 10; i++) {
          drawFace();
        }
        //the eyelashes return to the previous state
        scaredAnimationState = lastScaredAnimationState;
      }
      break;
  }

  drawFace();
}

void animateIdleStrips() {
  if (moodState == idle) {
#ifdef BTDEBUG
    BTSerial.println("Fixed strips animation...");
#endif
    drawFixedStrips();
  }
}

void animateHappyStrips() {
  if (moodState == happy) {
#ifdef BTDEBUG
    BTSerial.println("Strips animation...");
#endif
    if (isTeoMoving == true) {
      drawFixedStrips();
    }
    else {
      drawBreathingStrips();
    }
  }
}

void animateSadStrips() {
  if (moodState == sad) {
#ifdef BTDEBUG
    BTSerial.println("Strips animation...");
#endif
    if (isTeoMoving == true) {
      drawFixedStrips();
    }
    else {
      drawBreathingStrips();
    }
  }
}

void animateAngryStrips() {
  if (moodState == angry) {
#ifdef BTDEBUG
    BTSerial.println("Strips animation...");
#endif
    if (isTeoMoving == true) {
      drawFixedStrips();
    }
    else {
      drawBreathingStrips();
    }
  }
}

void animateScaredStrips() {
  if (moodState == scared) {
#ifdef BTDEBUG
    BTSerial.println("Strips animation...");
#endif
    if (isTeoMoving == true) {
      drawFixedStrips();
    }
    else {
      drawBreathingStrips();
    }
  }
}
