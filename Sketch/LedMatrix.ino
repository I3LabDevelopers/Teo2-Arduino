Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_COLUMNS, MATRIX_ROWS, MATRIX_PIN, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ZIGZAG + NEO_MATRIX_ROWS, NEO_GRB + NEO_KHZ800);

void matrixInit() {
  matrix.begin();
  matrix.setBrightness(10);
}

void drawFace() {
  //Switch of the matrix
  matrix.fillScreen(0);

  setEyelashes();
  setEyes();
  setMouth();

  //Switch on the matrix
  matrix.show();
}

//Switch on the eyelashes leds
static void setEyelashes() {
  switch (moodState) {
    case happy:

      switch (happyAnimationState) {

        case happyCenter:
          for (uint8_t i = 0; i < 32; i++) {
            matrix.drawPixel(happyCenterEyelashes[i][0], happyCenterEyelashes[i][1], matrix.Color(GREEN));
          }
          break;

        case happyLeft:
          for (uint8_t i = 0; i < 32; i++) {
            matrix.drawPixel(happyLeftEyelashes[i][0], happyLeftEyelashes[i][1], matrix.Color(GREEN));
          }
          break;

        case happyRight:
          for (uint8_t i = 0; i < 32; i++) {
            matrix.drawPixel(happyRightEyelashes[i][0], happyRightEyelashes[i][1], matrix.Color(GREEN));
          }
          break;

        case happyClosed:
          for (uint8_t i = 0; i < 36; i++) {
            matrix.drawPixel(happyClosedEyelashes[i][0], happyClosedEyelashes[i][1], matrix.Color(GREEN));
          }
      }
      break;

    case sad:
      switch (sadAnimationState) {

        case sadCenter:
          for (uint8_t i = 0; i < 30; i++) {
            matrix.drawPixel(sadCenterEyelashes[i][0], sadCenterEyelashes[i][1], matrix.Color(PURPLE));
          }
          break;

        case sadLeft:
          for (uint8_t i = 0; i < 30; i++) {
            matrix.drawPixel(sadLeftEyelashes[i][0], sadLeftEyelashes[i][1], matrix.Color(PURPLE));
          }
          break;

        case sadRight:
          for (uint8_t i = 0; i < 30; i++) {
            matrix.drawPixel(sadRightEyelashes[i][0], sadRightEyelashes[i][1], matrix.Color(PURPLE));
          }
          break;

        case sadClosed:
          for (uint8_t i = 0; i < 34; i++) {
            matrix.drawPixel(sadClosedEyelashes[i][0], sadClosedEyelashes[i][1], matrix.Color(PURPLE));
          }
      }
      break;

    case angry:

      switch (angryAnimationState) {

        case angryCenter:
          for (uint8_t i = 0; i < 24; i++) {
            matrix.drawPixel(angryCenterEyelashes[i][0], angryCenterEyelashes[i][1], matrix.Color(RED));
          }
          break;

        case angryLeft:
          for (uint8_t i = 0; i < 24; i++) {
            matrix.drawPixel(angryLeftEyelashes[i][0], angryLeftEyelashes[i][1], matrix.Color(RED));
          }
          break;

        case angryRight:
          for (uint8_t i = 0; i < 24; i++) {
            matrix.drawPixel(angryRightEyelashes[i][0], angryRightEyelashes[i][1], matrix.Color(RED));
          }
          break;

        case angryClosed:
          for (uint8_t i = 0; i < 28; i++) {
            matrix.drawPixel(angryClosedEyelashes[i][0], angryClosedEyelashes[i][1], matrix.Color(RED));
          }
      }
      break;

    case scared:

      switch (scaredAnimationState) {

        case scaredCenter:
          for (uint8_t i = 0; i < 32; i++) {
            matrix.drawPixel(scaredCenterEyelashes[i][0], scaredCenterEyelashes[i][1], matrix.Color(BLUE));
          }
          break;

        case scaredLeft:
          for (uint8_t i = 0; i < 32; i++) {
            matrix.drawPixel(scaredLeftEyelashes[i][0], scaredLeftEyelashes[i][1], matrix.Color(BLUE));
          }
          break;

        case scaredRight:
          for (uint8_t i = 0; i < 32; i++) {
            matrix.drawPixel(scaredRightEyelashes[i][0], scaredRightEyelashes[i][1], matrix.Color(BLUE));
          }
          break;

        case scaredClosed:
          for (uint8_t i = 0; i < 36; i++) {
            matrix.drawPixel(scaredClosedEyelashes[i][0], scaredClosedEyelashes[i][1], matrix.Color(BLUE));
          }
      }
      break;

    default:  //idle
      for (uint8_t i = 0; i < 28; i++) {
        matrix.drawPixel(idleEyelashes[i][0], idleEyelashes[i][1], matrix.Color(YELLOW));
      }
  }
}

//Switch on the eyes pupils leds
static void setEyes() {
  switch (moodState) {
    case happy:

      switch (happyAnimationState) {

        case happyCenter:
          for (uint8_t i = 0; i < 6; i++) {
            matrix.drawPixel(happyCenterEyes[i][0], happyCenterEyes[i][1], matrix.Color(YELLOW));
          }
          break;

        case happyLeft:
          for (uint8_t i = 0; i < 6; i++) {
            matrix.drawPixel(happyLeftEyes[i][0], happyLeftEyes[i][1], matrix.Color(YELLOW));
          }
          break;

        case happyRight:
          for (uint8_t i = 0; i < 6; i++) {
            matrix.drawPixel(happyRightEyes[i][0], happyRightEyes[i][1], matrix.Color(YELLOW));
          }
          break;
      }
      break;

    case sad:

      switch (sadAnimationState) {

        case sadCenter:
          for (uint8_t i = 0; i < 6; i++) {
            matrix.drawPixel(sadCenterEyes[i][0], sadCenterEyes[i][1], matrix.Color(YELLOW));
          }
          break;

        case sadLeft:
          for (uint8_t i = 0; i < 6; i++) {
            matrix.drawPixel(sadLeftEyes[i][0], sadLeftEyes[i][1], matrix.Color(YELLOW));
          }
          break;

        case sadRight:
          for (uint8_t i = 0; i < 6; i++) {
            matrix.drawPixel(sadRightEyes[i][0], sadRightEyes[i][1], matrix.Color(YELLOW));
          }
          break;
      }
      break;

    case angry:

      switch (angryAnimationState) {

        case angryCenter:
          for (uint8_t i = 0; i < 6; i++) {
            matrix.drawPixel(angryCenterEyes[i][0], angryCenterEyes[i][1], matrix.Color(YELLOW));
          }
          break;

        case angryLeft:
          for (uint8_t i = 0; i < 6; i++) {
            matrix.drawPixel(angryLeftEyes[i][0], angryLeftEyes[i][1], matrix.Color(YELLOW));
          }
          break;

        case angryRight:
          for (uint8_t i = 0; i < 6; i++) {
            matrix.drawPixel(angryRightEyes[i][0], angryRightEyes[i][1], matrix.Color(YELLOW));
          }
          break;
      }
      break;

    case scared:
      switch (scaredAnimationState) {

        case scaredCenter:
          for (uint8_t i = 0; i < 4; i++) {
            matrix.drawPixel(scaredCenterEyes[i][0], scaredCenterEyes[i][1], matrix.Color(YELLOW));
          }
          break;

        case scaredLeft:
          for (uint8_t i = 0; i < 4; i++) {
            matrix.drawPixel(scaredLeftEyes[i][0], scaredLeftEyes[i][1], matrix.Color(YELLOW));
          }
          break;

        case scaredRight:
          for (uint8_t i = 0; i < 4; i++) {
            matrix.drawPixel(scaredRightEyes[i][0], scaredRightEyes[i][1], matrix.Color(YELLOW));
          }
          break;
      }
  }
}

//Switch on the mouth leds
static void setMouth() {
  switch (moodState) {
    case happy:
      switch (happyAnimationState) {

        case happyCenter:
          for (uint8_t i = 0; i < 10; i++) {
            matrix.drawPixel(happyCenterMouth[i][0], happyCenterMouth[i][1], matrix.Color(GREEN));
          }
          break;

        case happyLeft:
          for (uint8_t i = 0; i < 10; i++) {
            matrix.drawPixel(happyLeftMouth[i][0], happyLeftMouth[i][1], matrix.Color(GREEN));
          }
          break;

        case happyRight:
          for (uint8_t i = 0; i < 10; i++) {
            matrix.drawPixel(happyRightMouth[i][0], happyRightMouth[i][1], matrix.Color(GREEN));
          }
          break;

        case happyClosed:
          for (uint8_t i = 0; i < 10; i++) {
            matrix.drawPixel(happyClosedMouth[i][0], happyClosedMouth[i][1], matrix.Color(GREEN));
          }
      }
      break;

    case sad:

      switch (sadAnimationState) {

        case sadCenter:
          for (uint8_t i = 0; i < 10; i++) {
            matrix.drawPixel(sadCenterMouth[i][0], sadCenterMouth[i][1], matrix.Color(PURPLE));
          }
          break;

        case sadLeft:
          for (uint8_t i = 0; i < 10; i++) {
            matrix.drawPixel(sadLeftMouth[i][0], sadLeftMouth[i][1], matrix.Color(PURPLE));
          }
          break;

        case sadRight:
          for (uint8_t i = 0; i < 10; i++) {
            matrix.drawPixel(sadRightMouth[i][0], sadRightMouth[i][1], matrix.Color(PURPLE));
          }
          break;

        case sadClosed:
          for (uint8_t i = 0; i < 10; i++) {
            matrix.drawPixel(sadClosedMouth[i][0], sadClosedMouth[i][1], matrix.Color(PURPLE));
          }
      }
      break;

    case angry:

      switch (angryAnimationState) {

        case angryCenter:
          for (uint8_t i = 0; i < 8; i++) {
            matrix.drawPixel(angryCenterMouth[i][0], angryCenterMouth[i][1], matrix.Color(RED));
          }
          break;

        case angryLeft:
          for (uint8_t i = 0; i < 8; i++) {
            matrix.drawPixel(angryLeftMouth[i][0], angryLeftMouth[i][1], matrix.Color(RED));
          }
          break;

        case angryRight:
          for (uint8_t i = 0; i < 8; i++) {
            matrix.drawPixel(angryRightMouth[i][0], angryRightMouth[i][1], matrix.Color(RED));
          }
          break;

        case angryClosed:
          for (uint8_t i = 0; i < 8; i++) {
            matrix.drawPixel(angryClosedMouth[i][0], angryClosedMouth[i][1], matrix.Color(RED));
          }
      }
      break;

    case scared:
      switch (scaredAnimationState) {

        case scaredCenter:
          for (uint8_t i = 0; i < 16; i++) {
            matrix.drawPixel(scaredCenterMouth[i][0], scaredCenterMouth[i][1], matrix.Color(BLUE));
          }
          break;

        case scaredLeft:
          for (uint8_t i = 0; i < 16; i++) {
            matrix.drawPixel(scaredLeftMouth[i][0], scaredLeftMouth[i][1], matrix.Color(BLUE));
          }
          break;

        case scaredRight:
          for (uint8_t i = 0; i < 16; i++) {
            matrix.drawPixel(scaredRightMouth[i][0], scaredRightMouth[i][1], matrix.Color(BLUE));
          }
          break;

        case scaredClosed:
          for (uint8_t i = 0; i < 16; i++) {
            matrix.drawPixel(scaredClosedMouth[i][0], scaredClosedMouth[i][1], matrix.Color(BLUE));
          }
      }
      break;

    default:  //idle
      for (uint8_t i = 0; i < 8; i++) {
        matrix.drawPixel(idleMouth[i][0], idleMouth[i][1], matrix.Color(YELLOW));
      }
  }
}
