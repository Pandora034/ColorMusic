void randomColorStripe3() {
  for (byte i = 0; i < 3; i++) {
    if (thisBright[i] <= EMPTY_BRIGHT + 25) freq_color[i] = random8();
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < NUM_LEDS / 3)          leds[i] = CHSV(freq_color[2], 255, map(thisBright[2], EMPTY_BRIGHT, 255, 0, 255));
    else if (i < NUM_LEDS * 2 / 3) leds[i] = CHSV(freq_color[1], 255, map(thisBright[1], EMPTY_BRIGHT, 255, 0, 255));
    else if (i < NUM_LEDS)         leds[i] = CHSV(freq_color[0], 255, map(thisBright[0], EMPTY_BRIGHT, 255, 0, 255));
  }
}

void randomColorStripe5() {
  for (byte i = 0; i < 3; i++) {
    if (thisBright[i] <= EMPTY_BRIGHT + 25) freq_color[i] = random8();
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < STRIPE)          leds[i] = CHSV(freq_color[2], 255, map(thisBright[2], EMPTY_BRIGHT, 255, 0, 255));
    else if (i < STRIPE * 2) leds[i] = CHSV(freq_color[1], 255, map(thisBright[1], EMPTY_BRIGHT, 255, 0, 255));
    else if (i < STRIPE * 3) leds[i] = CHSV(freq_color[0], 255, map(thisBright[0], EMPTY_BRIGHT, 255, 0, 255));
    else if (i < STRIPE * 4) leds[i] = CHSV(freq_color[1], 255, map(thisBright[1], EMPTY_BRIGHT, 255, 0, 255));
    else if (i < STRIPE * 5) leds[i] = CHSV(freq_color[2], 255, map(thisBright[2], EMPTY_BRIGHT, 255, 0, 255));
  }
}

void randomColorStripeMod5() {
  for (byte i = 0; i < 3; i++) {
    if (thisBright[i] <= EMPTY_BRIGHT + 25) freq_color[i] = random8();
  }

  for (int segment = 0; segment < 5; segment++) {
    uint8_t segmentStart = segment * STRIPE;
    uint8_t segmentCenter = segmentStart + (STRIPE / 2);
    uint8_t brightnessMax = 255;
    uint8_t brightnessMin = 5;

    for (int i = segmentStart; i < segmentStart + STRIPE; i++)
    {
      uint8_t brightness = brightnessMin + (brightnessMax - brightnessMin) * abs(i - segmentCenter) / (STRIPE / 2);
      if (i < STRIPE)          leds[i] = CHSV(freq_color[2], 255, map(thisBright[2], EMPTY_BRIGHT, 255, 0, 255));
      else if (i < STRIPE * 2) leds[i] = CHSV(freq_color[1], 255, map(thisBright[1], EMPTY_BRIGHT, 255, 0, 255));
      else if (i < STRIPE * 3) leds[i] = CHSV(freq_color[0], 255, map(thisBright[0], EMPTY_BRIGHT, 255, 0, 255));
      else if (i < STRIPE * 4) leds[i] = CHSV(freq_color[1], 255, map(thisBright[1], EMPTY_BRIGHT, 255, 0, 255));
      else if (i < STRIPE * 5) leds[i] = CHSV(freq_color[2], 255, map(thisBright[2], EMPTY_BRIGHT, 255, 0, 255));
      leds[i].nscale8(brightness);
    }
  }
}
