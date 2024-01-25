void VUAnimation(CRGBPalette16 palette) {
  if (millis() - rainbow_timer > 30) {
    rainbow_timer = millis();
    hue = floor((float)hue + RAINBOW_STEP);
  }
  count = 0;
  byte brightness = 0;
  for (int i = (MAX_CH - 1); i > ((MAX_CH - 1) - Rlenght); i--) {
    leds[i] = ColorFromPalette(palette, (count * index) / 2 - hue);  // заливка по палитре радуга
    if (i < ((MAX_CH - 1) - Rlenght + 5)) {
      leds[i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(map(brightness, 0, 3, EMPTY_BRIGHT, 15));
      brightness++;
      //leds[i] = CRGB::White;
    }
    count++;
  }
  count = 0;
  for (int i = (MAX_CH); i < (MAX_CH + Llenght); i++ ) {
    leds[i] = ColorFromPalette(palette, (count * index) / 2 - hue); // заливка по палитре радуга
    count++;
  }

  for (int i = 0; i < NUM_LEDS - 1; i++) {
    CRGB color1 = leds[i];
    CRGB color2 = leds[i + 1];
    //CRGB midleColor = blend(color1, color2, 50);
    leds[i] = blend(color1, color2, 25);
    leds[i + 1] = blend(color1, color2, 75);
  }

  if (EMPTY_BRIGHT > 0) {
    CHSV this_dark = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
    for (int i = ((MAX_CH - 1) - Rlenght); i > 0; i--)
      leds[i] = this_dark;
    for (int i = MAX_CH + Llenght; i < NUM_LEDS; i++)
      leds[i] = this_dark;
  }
}


#define HUE_GAP 20      // заброс по hue
#define FIRE_STEP 50    // шаг огня
#define HUE_S 0     // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define MIN_BRIGHT 70   // мин. яркость огня
#define MAX_BRIGHT 255  // макс. яркость огня
#define MIN_SAT 150     // мин. насыщенность
#define MAX_SAT 255     // макс. насыщенность

static uint32_t prevTime;
int counter = 0;

CRGB getFireColor(int val) {
  // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
  return CHSV(
           HUE_S + map(val, 0, 255, 0, HUE_GAP),                    // H
           constrain(map(val, 0, 255, MAX_SAT, MIN_SAT), 0, 255),       // S
           constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V
         );
}

void VUAnimation() {
  if (millis() - rainbow_timer > 30) {
    rainbow_timer = millis();
    counter += 20;
  }
  
  for (int i = (MAX_CH); i < (MAX_CH + Llenght); i++ ) {
    leds[i] = getFireColor((inoise8(i * FIRE_STEP, counter)));
  }
  
  if (EMPTY_BRIGHT > 0) {
    CHSV this_dark = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
    for (int i = ((MAX_CH - 1) - Rlenght); i > 0; i--)
      leds[i] = this_dark;
    for (int i = MAX_CH + Llenght; i < NUM_LEDS; i++)
      leds[i] = this_dark;
  }
}
