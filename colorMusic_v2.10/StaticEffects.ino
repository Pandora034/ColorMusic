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
   if (millis() - perlin_timer > 30) {
    perlin_timer = millis();
    counter += BACKLIGHT_PERLIN_SPEED;
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = getFireColor((inoise8(i * FIRE_STEP, counter)), hue_s);
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
