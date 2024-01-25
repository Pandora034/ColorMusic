void VUAnimation(CRGBPalette32 palette) {
  if (millis() - rainbow_timer > 30) {
    rainbow_timer = millis();
    hue = floor((float)hue + RAINBOW_STEP);
  }
  count = 0;
  CRGB midleColor;
  for (int i = (MAX_CH - 1); i > ((MAX_CH - 1) - Rlenght); i--) {
    leds[i] = ColorFromPalette(palette, (count * index) / 2 - hue);
    count++;
  }
  count = 0;
  for (int i = (MAX_CH); i < (MAX_CH + Llenght); i++ ) {
    leds[i] = ColorFromPalette(palette, (count * index) / 2 - hue);
    count++;
  }
  
  for(int i = 0; i < NUM_LEDS - 2; i++){
    CRGB color1 = leds[i];
    CRGB color2 = leds[i + 2];
    CRGB midleColor = blend(color1, color2, 75);
    leds[i+1] = midleColor;
  }
  
  if (EMPTY_BRIGHT > 0) {
    CHSV this_dark = CHSV(EMPTY_COLOR, 255, EMPTY_BRIGHT);
    for (int i = ((MAX_CH - 1) - Rlenght); i > 0; i--)
      leds[i] = this_dark;
    for (int i = MAX_CH + Llenght; i < NUM_LEDS; i++)
      leds[i] = this_dark;
  }
}
