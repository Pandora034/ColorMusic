void animation() {
  // согласно режиму
  switch (this_mode) {
    case 0:
      switch (backlight_mode) {
        case 0:
          switch (whiteKelvin_mode) {
            case 0:
              WhiteLight(UncorrectedTemperature);
              break;
            case 1:
              WhiteLight(Halogen);
              break;
            case 2:
              WhiteLight(Tungsten100W);
              break;
            case 3:
              WhiteLight(Tungsten40W);
              break;
            case 4:
              WhiteLight(Candle);
              break;
          }
          break;
        case 1:
          if (millis() - perlinRainbow_timer > BACKLIGHT_PERLIN_RAINBOW_SPEED) {
            perlinRainbow_timer = millis();
            perlinHue ++;
          }
          perlin(perlinHue);
          break;
        case 2:
          perlin(0);
          break;
        case 3:
          oneColor();
          break;
        case 4:
          transfusionOfColors();
          break;
        case 5:
          ranningRainbow();
          break;
      }
      break;

    case 1:
      switch (vu_mode) {
        case 0:
          VUStaticAnimation();
          break;
        case 1:
          VUAnimation(RainbowColors_p, HUE_AQUA);
          break;
        case 2:
          if (millis() - perlinRainbow_timer > BACKLIGHT_PERLIN_RAINBOW_SPEED) {
            perlinRainbow_timer = millis();
            perlinHue ++;
          }
          VUAnimation(perlinHue, HUE_AQUA);
          break;
        case 3:
          VUAnimation(0, HUE_RED); // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
          break;
        case 4:
          VUAnimation(80, HUE_GREEN);
          break;
        case 5:
          VUAnimation(40, HUE_ORANGE);
          break;
        case 6:
          VUAnimation(140, HUE_BLUE);
          break;
        case 7:
          VUAnimation(120, HUE_AQUA);
          break;
        case 8:
          VUAnimation(190, HUE_PINK);
          break;
        case 9:
          VUAnimation(160, HUE_PURPLE);
          break;
      }

      break;
    case 2:
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i < STRIPE)          leds[i] = CHSV(HIGH_COLOR, 255, thisBright[2]);
        else if (i < STRIPE * 2) leds[i] = CHSV(MID_COLOR, 255, thisBright[1]);
        else if (i < STRIPE * 3) leds[i] = CHSV(LOW_COLOR, 255, thisBright[0]);
        else if (i < STRIPE * 4) leds[i] = CHSV(MID_COLOR, 255, thisBright[1]);
        else if (i < STRIPE * 5) leds[i] = CHSV(HIGH_COLOR, 255, thisBright[2]);
      }
      break;
    case 3:
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i < NUM_LEDS / 3)          leds[i] = CHSV(HIGH_COLOR, 255, thisBright[2]);
        else if (i < NUM_LEDS * 2 / 3) leds[i] = CHSV(MID_COLOR, 255, thisBright[1]);
        else if (i < NUM_LEDS)         leds[i] = CHSV(LOW_COLOR, 255, thisBright[0]);
      }
      break;
    case 4:
      switch (freq_strobe_mode) {
        case 0:
          if (colorMusicFlash[2]) HIGHS();
          else if (colorMusicFlash[1]) MIDS();
          else if (colorMusicFlash[0]) LOWS();
          else SILENCE();
          break;
        case 1:
          if (colorMusicFlash[2]) HIGHS();
          else SILENCE();
          break;
        case 2:
          if (colorMusicFlash[1]) MIDS();
          else SILENCE();
          break;
        case 3:
          if (colorMusicFlash[0]) LOWS();
          else SILENCE();
          break;
      }
      break;
    case 5:
      if (strobe_bright > 0)
        for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(STROBE_COLOR, STROBE_SAT, strobe_bright);
      else
        for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
      break;
    case 6:
      randomColorStripe3();
      break;
    case 7:
      switch (freq_strobe_mode) {
        case 0:
          if (running_flag[2]) leds[NUM_LEDS / 2] = CHSV(HIGH_COLOR, 255, thisBright[2]);
          else if (running_flag[1]) leds[NUM_LEDS / 2] = CHSV(MID_COLOR, 255, thisBright[1]);
          else if (running_flag[0]) leds[NUM_LEDS / 2] = CHSV(LOW_COLOR, 255, thisBright[0]);
          else leds[NUM_LEDS / 2] = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
          break;
        case 1:
          if (running_flag[2]) leds[NUM_LEDS / 2] = CHSV(HIGH_COLOR, 255, thisBright[2]);
          else leds[NUM_LEDS / 2] = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
          break;
        case 2:
          if (running_flag[1]) leds[NUM_LEDS / 2] = CHSV(MID_COLOR, 255, thisBright[1]);
          else leds[NUM_LEDS / 2] = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
          break;
        case 3:
          if (running_flag[0]) leds[NUM_LEDS / 2] = CHSV(LOW_COLOR, 255, thisBright[0]);
          else leds[NUM_LEDS / 2] = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
          break;
      }
      leds[(NUM_LEDS / 2) - 1] = leds[NUM_LEDS / 2];
      if (millis() - running_timer > RUNNING_SPEED) {
        running_timer = millis();
        for (int i = 0; i < NUM_LEDS / 2 - 1; i++) {
          leds[i] = leds[i + 1];
          leds[NUM_LEDS - i - 1] = leds[i];
        }
      }
      break;
    case 8:
      byte HUEindex = HUE_START;
      for (int i = 0; i < NUM_LEDS / 2; i++) {
        byte this_bright = map(freq_f[(int)floor((NUM_LEDS / 2 - i) / freq_to_stripe)], 0, freq_max_f, 0, 255);
        this_bright = constrain(this_bright, 0, 255);
        leds[i] = CHSV(HUEindex, 255, this_bright);
        leds[NUM_LEDS - i - 1] = leds[i];
        HUEindex += HUE_STEP;
        if (HUEindex > 255) HUEindex = 0;
      }
      break;
  }
}
