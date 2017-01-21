#define EXECUTING   true
#define EXIT        false


typedef boolean _talk2teoIn;


enum _talk2teoState {
    sense, verifyRules, manualExecute, chooseBehavior, behaviorExecute
};

_talk2teoState currentState = sense;
_talk2teoIn behaviorExecuting, commandReceived, commandEnded, behaviorsOn;
boolean (*behaviorToExecute)();
boolean (*commandToExecute)();


boolean Talk2TeoInit() {

    currentState = sense;
    behaviorExecuting = false;
    commandReceived = false;
    commandEnded = false;
    behaviorsOn = true;
    TeoStateInit();

}


boolean Talk2Teo() {

    switch (currentState) {
        case sense:
            talk2teo_sense();
            break;

        case verifyRules:
            talk2teo_verifyRules();
            break;

        case manualExecute:
            talk2teo_manualExecute();
            break;

        case chooseBehavior:
            talk2teo_chooseBehavior();
            break;

        case behaviorExecute:
            talk2teo_behaviorExecute();
            break;
    
    }

        return EXECUTING;
}


void talk2teo_sense() {

    refreshTeoState();
    timersRefresh();
    
    if (commandReceived) {
        if (!behaviorExecuting)
            currentState = manualExecute;
        else 
            commandReceived = false;
    }
    else if (behaviorsOn) 
      currentState = verifyRules;
    else {
      behaviorExecuting = false;
      currentState = sense;
    }
}

void talk2teo_verifyRules() {

//    not_move_when_close();      // Verify and ensure the robot does not move when the child's close.

    if (behaviorExecuting) currentState = behaviorExecute;
    else currentState = chooseBehavior;
}

void talk2teo_manualExecute() {
    
    resetInactiveTimeCounter();
    commandEnded = commandToExecute();      // This function can either be blocking or not. The machine will remain in this state anyway until finished.
    
    if (commandEnded) {
        currentState = sense;
        setCommandReceived(false);
    }
    else currentState = manualExecute;
}

void talk2teo_chooseBehavior() {
    
    currentState = behaviorExecute;
    
    if (try_look_for_the_child());
    else if (try_random_prompt());
    else {
        currentState = sense;    
    }   
}

void talk2teo_behaviorExecute() {

    resetInactiveTimeCounter();
    behaviorExecuting = true;
    if (behaviorToExecute()) 
        behaviorExecuting = false;
    currentState = sense;
}

void setCommandToExecute(boolean (*commandFunction)()) {
    commandToExecute = commandFunction;
}

void setBehaviorToExecute(boolean (*behavior)()) {
    behaviorToExecute = behavior;
}

void turnOnBehaviors(boolean on) {
    behaviorsOn = on;
}

void setCommandReceived(boolean received) {
    commandReceived = received;
}

boolean isBehaviorExecuting () {
    return behaviorExecuting;
}