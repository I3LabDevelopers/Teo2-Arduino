MC33887 m1(9, 50, 52);//(pwm (d2), in1, in2)
MC33887 m2(10, 40, 42);//(pwd, en1, en2)
MC33887 m3(11, 30, 32);//(pwd, en1, en2)
Triskar triskar(m1, m2, m3);

const uint8_t ENABLE_MOTORS_PIN1 = 46;
const uint8_t ENABLE_MOTORS_PIN2 = 36;
const uint8_t ENABLE_MOTORS_PIN3 = 26;

boolean isTeoMoving = false;

void movementInit() {
  pinMode(9, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(ENABLE_MOTORS_PIN1, OUTPUT);
  pinMode(ENABLE_MOTORS_PIN2, OUTPUT);
  pinMode(ENABLE_MOTORS_PIN3, OUTPUT);
}

void Stop() {
  
  digitalWrite(ENABLE_MOTORS_PIN1, LOW);// disattiva motori
  digitalWrite(ENABLE_MOTORS_PIN2, LOW);
  digitalWrite(ENABLE_MOTORS_PIN3, LOW);
  triskar.run(0, 0, 0);
  triskar.stop();
  

  isTeoMoving = false;
}

//G strafe forward angularSpeed
void Go(float strafe, float forward, float angular) {

  triskar.run(strafe, forward, angular);//velocità di Spostamento laterale, velocità di avanzamento, velocità angolare
  digitalWrite(ENABLE_MOTORS_PIN1, HIGH);// disattiva motori
  digitalWrite(ENABLE_MOTORS_PIN2, HIGH);
  digitalWrite(ENABLE_MOTORS_PIN3, HIGH);

  if (strafe == 0 && forward == 0 && angular == 0)
    isTeoMoving = false;
  else{
    isTeoMoving = true;
  }
}

boolean isMoving() {
    return isTeoMoving;
}


// ======================== MANUAL COMMAND ===============================
float str,forw,ang;

void setMovementParams(float s, float f, float a) {
    str = s;
    forw = f;
    ang = a;  
}

boolean executeManualMovement() {
    Go (str,forw,ang);
    return true;
}