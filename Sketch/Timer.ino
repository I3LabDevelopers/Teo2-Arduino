// ==================== TIMER INIT ======================
Timer timer;

void timersInit() {
  timer.every(3000, animateEyes);
  timer.every(4000, animateEyelashes);
  timer.every(4000, animateIdleStrips);
  timer.every(4000, animateHappyStrips);
  timer.every(1000, animateSadStrips);
  timer.every(500, animateAngryStrips);
  timer.every(500, animateScaredStrips);
  timer.every(2000, ready);
}

void timersRefresh() {
  timer.update();
}
