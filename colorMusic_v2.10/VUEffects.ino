void VUAnimation(CRGBPalette16 palette, HSVHue empty_color) {
  if (millis() - rainbow_timer > 30) {
    rainbow_timer = millis();
    hue = floor((float)hue + RAINBOW_STEP);
    EMPTY_COLOR = empty_color;
  }
  count = 0;
  byte brightness = 0;
  for (int i = (MAX_CH - 1); i > ((MAX_CH - 1) - Rlenght); i--) {
    leds[i] = ColorFromPalette(palette, (count * index) / 2 - hue);  // заливка по палитре радуга
    if (i < ((MAX_CH - 1) - Rlenght + 5)) {
      leds[i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(map(brightness, 0, 3, EMPTY_BRIGHT, 15));
      brightness++;
    }
    count++;
  }
  count = 0;
  for (int i = (MAX_CH); i < (MAX_CH + Llenght); i++ ) {
    leds[i] = ColorFromPalette(palette, (count * index) / 2 - hue); // заливка по палитре радуга
    count++;
  }

  reducingBrightness();

  if (EMPTY_BRIGHT > 0) {
    CHSV this_dark = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
    for (int i = ((MAX_CH - 1) - Rlenght); i > 0; i--)
      leds[i] = this_dark;
    for (int i = MAX_CH + Llenght; i < NUM_LEDS; i++)
      leds[i] = this_dark;
  }
}


CRGB getFireColorForVU(int val, int hue_s) {
  int min_sat = map(Llenght, 0, MAX_CH, 250, 150);
  // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
  return CHSV(
           hue_s + map(val, 0, 255, 0, HUE_GAP),                    // H
           constrain(map(val, 0, 255, MAX_SAT, min_sat), 0, 255),       // S
           constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V
         );
}

//-----------------------------ШКАЛА ГРОМКОСТИ НА ШУМЕ ПЕРЛИНА----------------------------

void VUAnimation(int hue_s, HSVHue empty_color) {
  if (millis() - rainbow_timer > 30) {
    rainbow_timer = millis();
    counter += map(RAINBOW_STEP, 0.5, 20, 5, 40);
    EMPTY_COLOR = empty_color;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = getFireColorForVU((inoise8(i * FIRE_STEP, counter)), hue_s);
  }

  reducingBrightness();


  CHSV this_dark = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
  for (int i = ((MAX_CH - 1) - Rlenght); i >= 0; i--)
    leds[i] = this_dark;
  for (int i = MAX_CH + Llenght; i < NUM_LEDS; i++)
    leds[i] = this_dark;

}

//------------------------------------------------------------------------------------------------

void VUStaticAnimation() {
  count = 0;
  for (int i = (MAX_CH - 1); i > ((MAX_CH - 1) - Rlenght); i--) {
    leds[i] = ColorFromPalette(myPal, (count * index) - count );   // заливка по палитре " от зелёного к красному"
    count++;
  }
  count = 0;
  for (int i = (MAX_CH); i < (MAX_CH + Llenght); i++ ) {
    leds[i] = ColorFromPalette(myPal, (count * index) - count);   // заливка по палитре " от зелёного к красному"
    count++;
  }
  if (EMPTY_BRIGHT > 0) {
    CHSV this_dark = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
    for (int i = ((MAX_CH - 1) - Rlenght); i > 0; i--)
      leds[i] = this_dark;
    for (int i = MAX_CH + Llenght; i < NUM_LEDS; i++)
      leds[i] = this_dark;
  }
}

//-----------------------------ПОНИЖЕНИЕ ЯРКОСТИ ПОСЛЕДНИХ СВЕТОДИОДОВ----------------------------

void reducingBrightness() {
  int i = MAX_CH + Llenght - 3;
  leds[i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.2);
  leds[++i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.1);
  leds[++i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.03);

  i = (MAX_CH - 1) - Rlenght + 3;
  leds[i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.2);
  leds[--i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.1);
  leds[--i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.03);
}

//------------------------------------------------------------------------------------------------
