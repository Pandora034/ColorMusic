void silence(uint8_t mode) {
  if (mode != 0) {
    last_mode = mode;
  }
  silence_IR_flag = false;
  if ((last_mode == 1) && (LsoundLevel_f <= 0.01) && (LsoundLevel_f <= 0.01)) {
    silence_flag = true;
    }
  else if ((last_mode != 1) && (thisBright[0] <= EMPTY_BRIGHT) && (thisBright[1] <= EMPTY_BRIGHT) && (thisBright[2] <= EMPTY_BRIGHT)){
    silence_flag = true;
    }
  else {
    silence_timer = millis();
    silence_flag = false;
    this_mode = last_mode;
  }

  if (silence_flag && (millis() - silence_timer > SILENCE_TIME)) {
    this_mode = 0;
  }
}
