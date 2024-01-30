void WhiteLight(ColorTemperature temp) {
  CRGB color = CRGB(temp);
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
    leds[i].setRGB(leds[i].r, leds[i].g, leds[i].b).nscale8(whiteLightBrightness);
  }
}


CRGB getFireColor(int val, int hue_s) {
  // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
  return CHSV(
           hue_s + map(val, 0, 255, 0, BACKLIGHT_HUE_GAP),                    // H
           constrain(map(val, 0, 255, BACKLIGHT_MAX_SAT, BACKLIGHT_MIN_SAT), 0, 255),       // S
           constrain(map(val, 0, 255, BACKLIGHT_MIN_BRIGHT, BACKLIGHT_MAX_BRIGHT), 0, 255)  // V
         );
}

void perlin(int hue_s) {
  uint8_t c = BACKLIGHT_PERLIN_SPEED;
  if (millis() - perlin_timer > 30) {
    perlin_timer = millis();
#if TRACKING_SILENCE == 1
    if (silence_IR_flag) {
      VUAnalysis();
      c = map(Rlenght, 0, MAX_CH, BACKLIGHT_PERLIN_SPEED, BACKLIGHT_PERLIN_SPEED + 30);
    }
#endif
    counter += c;
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = getFireColor((inoise8(i * BACKLIGHT_FIRE_STEP, counter)), hue_s);
  }
}

void oneColor() {
  for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(LIGHT_COLOR, LIGHT_SAT, 255);
}

void transfusionOfColors() {
  if (millis() - color_timer > COLOR_SPEED) {
    color_timer = millis();
    if (++this_color > 255) this_color = 0;
  }
  for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(this_color, LIGHT_SAT, 255);
}

void ranningRainbow() {
  if (millis() - rainbow_timer > 30) {
    rainbow_timer = millis();
#if TRACKING_SILENCE == 1
    if (silence_IR_flag) {
      VUAnalysis();
      if (RAINBOW_PERIOD > 0) this_color += map(Rlenght, 0, MAX_CH, RAINBOW_PERIOD, RAINBOW_PERIOD + 3);
      else this_color += map(Rlenght, 0, MAX_CH, RAINBOW_PERIOD, RAINBOW_PERIOD - 3);
    }
#endif
    this_color += RAINBOW_PERIOD;

    if (this_color > 255) this_color = 0;
    if (this_color < 0) this_color = 255;
  }
  rainbow_steps = this_color;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((int)floor(rainbow_steps), 255, 255);
    rainbow_steps += RAINBOW_STEP_2;
    if (rainbow_steps > 255) rainbow_steps = 0;
    if (rainbow_steps < 0) rainbow_steps = 255;
  }
}

/*UncorrectedTemperature
        Candle
        Tungsten40W
        Tungsten100W
        Halogen
        CarbonArc
        HighNoonSun
        DirectSunlight
        OvercastSky
        ClearBlueSky
        WarmFluorescent
        StandardFluorescent
        CoolWhiteFluorescent
        FullSpectrumFluorescent
        GrowLightFluorescent
        BlackLightFluorescent
        MercuryVapor
        SodiumVapor
        MetalHalide
        HighPressureSodium*/
