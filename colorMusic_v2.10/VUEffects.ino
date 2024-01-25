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

  reducingBrightness();

  if (EMPTY_BRIGHT > 0) {
    CHSV this_dark = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
    for (int i = ((MAX_CH - 1) - Rlenght); i > 0; i--)
      leds[i] = this_dark;
    for (int i = MAX_CH + Llenght; i < NUM_LEDS; i++)
      leds[i] = this_dark;
  }
}


#define HUE_GAP 21      // заброс по hue
#define FIRE_STEP 35    // шаг огня
#define MIN_BRIGHT 30   // мин. яркость огня
#define MAX_BRIGHT 255  // макс. яркость огня
#define MIN_SAT 150     // мин. насыщенность
#define MAX_SAT 255     // макс. насыщенность

static uint32_t prevTime;
int counter = 0;

CRGB getFireColor(int val, int hue_s) {
  // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
  return CHSV(
           hue_s + map(val, 0, 255, 0, HUE_GAP),                    // H
           constrain(map(val, 0, 255, MAX_SAT, MIN_SAT), 0, 255),       // S
           constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V
         );
}

void VUAnimation(int hue_s) {
  if (millis() - rainbow_timer > 30) {
    rainbow_timer = millis();
    counter += map(RAINBOW_STEP, 0.5, 20, 5, 40);
  }

  byte c = 0;
  for (int i = (MAX_CH); i < (MAX_CH + Llenght); i++ ) {
    leds[i] = getFireColor((inoise8(i * FIRE_STEP, counter)), hue_s);
  }


  int mid = NUM_LEDS / 2;
  for (int i = 0; i < mid; i++) {
    CRGB color = leds[NUM_LEDS - i - 1];
    leds[i] = color;
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

//-----------------------------ПОНИЖЕНИЕ ЯРКОСТИ ПОСЛЕДНИХ СВЕТОДИОДОВ----------------------------
void reducingBrightness(){
  int i = MAX_CH + Llenght - 3;
  leds[i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.2);
  leds[++i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.1);
  leds[++i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.03);

  i = (MAX_CH - 1) - Rlenght + 4;
  leds[i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.2);
  leds[--i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.1);
  leds[--i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(BRIGHTNESS * 0.03);
}
//------------------------------------------------------------------------------------------------
