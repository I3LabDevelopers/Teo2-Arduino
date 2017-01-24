enum wakeupState {
  Sleeping, Awake
};
wakeupState wakeUpState = Sleeping;

boolean try_wakeup() {
  if (moodState == idle) {
    /* TO BE TESTED
    if (isTouched || isCalled)
      wakeUpState = Awake;
    else */
      wakeUpState = Sleeping;

    setBehaviorToExecute(execute_wakeup);
    return true;
  }
  else
    return false;
}

boolean execute_wakeup() {
  switch (wakeUpState) {
    case Sleeping:
      if(!isTeoSpeaking())
          speak("russata");
      break;
    case Awake:
      speak("ciao");
      setHappyMood();
      drawFace();
  }
}
