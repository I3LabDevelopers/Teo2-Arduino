/*
    This file contains the methods related to the 'Look for the
    child' automatic behavior.
*/



enum lookForTheChildStates {
    CheckTime,Init, MoveLeft, MoveRight, CheckMovement, Finish
};
    
lookForTheChildStates state, past_state;
long int timeCheck;
boolean childLeft = false;

//Returns true if the conditions are set to execute behavior.
boolean try_look_for_the_child() {
        InteractionRegion current = getCurrentRegion();
        InteractionRegion past = getPastRegion();
        
        if (past <= Social && current > Social) {
            setBehaviorToExecute(execute_look_for_the_child);
            state = CheckTime;
            timeCheck = millis();
            childLeft = true;
            return true;    
        }

        if (past >= Social && current < Social && childLeft) {
            setBehaviorToExecute(execute_child_returns);
            timeCheck = millis();
            state = CheckTime;
            return true;
        }
        
        return false;
    }

// Returns true when is done executing the behavior
boolean execute_look_for_the_child() {

    switch (state) {

        case CheckTime:
            if (millis() - timeCheck < 5000) {
                if (getCurrentRegion() < Social) {
                    setHappyMood();
                    return true;
                  } 
            }
            else 
              state = Init;
          break;

        case Init:
            setSadMood();
            drawFace();
            state = MoveLeft;
            break;
            
        case MoveLeft:
            if (!positionCommanded()) {
                rotate(60,3);
                state = CheckMovement;
                past_state = MoveLeft;
            }
            break;
            
        case MoveRight:
            if (!positionCommanded()) {
                rotate(-120,3);
                speak("dove sei");
                state = CheckMovement;
                past_state = MoveRight;
            }
            break;

        case CheckMovement:
            refreshPositionControl();
            if (!positionCommanded()) {
                    if (past_state == MoveLeft)
                        state = MoveRight;
                     else {  
                        state = Finish;
                     }
                }
             break;
         case Finish:
            if (!isMoving() && !isTeoSpeaking())
                return true;
            break;
    }

    if (getCurrentRegion() < Social) {
       stop_position_control();
       setHappyMood();
       return true;  
    }

    return false;
}

boolean execute_child_returns () {
        childLeft = false;
        switch (state) {
            case CheckTime:
               if (millis() - timeCheck < 2000) {
                  if (getCurrentRegion() > Social) {
                        setHappyMood();
                        return true;
                      } 
                  }
                else 
                  state = Init;
                break;

            case Init:
                setHappyMood();
                state = MoveLeft;
                break;
                
            case MoveLeft:
                if (!positionCommanded()) {
                    moveLateral(0.1,2);
                    speak("giochi");
                    state = CheckMovement;
                    past_state = MoveLeft;
                }
                break;

            case MoveRight:
                if (!positionCommanded()) {
                    moveLateral(-0.1,2);
                    state = CheckMovement;
                    past_state = MoveRight;
                }
                break;
            
            case CheckMovement:
                refreshPositionControl();
                if (!positionCommanded()) {
                     if (past_state == MoveLeft)
                        state = MoveRight;
                     else      
                       state = Finish;
                 }
                 break;
             case Finish:
                if (!isMoving() && !isTeoSpeaking())
                    return true;
                break;
        }

        return false;        
    }