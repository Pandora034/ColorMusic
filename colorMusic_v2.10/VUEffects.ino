void VUAnimation(CRGBPalette16 palette) {
  if (millis() - rainbow_timer > 30) {
    rainbow_timer = millis();
    hue = floor((float)hue + RAINBOW_STEP);
  }
  count = 0;
  for (int i = (MAX_CH - 1); i > ((MAX_CH - 1) - Rlenght); i--) {
    leds[i] = ColorFromPalette(palette, (count * index) / 2 - hue);  // заливка по палитре лава
    count++;
  }
  count = 0;
  for (int i = (MAX_CH); i < (MAX_CH + Llenght); i++ ) {
    leds[i] = ColorFromPalette(palette, (count * index) / 2 - hue); // заливка по палитре лава
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
