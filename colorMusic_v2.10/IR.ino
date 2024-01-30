#if REMOTE_TYPE != 0
void remoteTick() {
  if (IRLremote.available())  {
    auto data = IRLremote.read();
    IRdata = data.command;
    ir_flag = true;
  }
  if (ir_flag) { // если данные пришли
    eeprom_timer = millis();
    eeprom_flag = true;
    switch (IRdata) {
      // режимы
      case BUTT_1:
        this_mode = 0;
        silence_IR_flag = true; //переключаем режим, отключаем отслеживания тишины (костыль)
        break;
      case BUTT_2: this_mode = 1; silence_timer = millis(); //переключаем режим, сбрасываем таймер отслеживания тишины для отключения отслеживания тишины (костыль)
        break;
      case BUTT_3: this_mode = 2; silence_timer = millis();
        break;
      case BUTT_4: this_mode = 3; silence_timer = millis();
        break;
      case BUTT_5: this_mode = 4; silence_timer = millis();
        break;
      case BUTT_6: this_mode = 5;
        break;
      case BUTT_7: this_mode = 6;
        break;
      case BUTT_8: this_mode = 7; silence_timer = millis();
        break;
      case BUTT_9: this_mode = 8; silence_timer = millis();
        break;
      case BUTT_0: fullLowPass();
        break;
      case BUTT_STAR: ONstate = !ONstate; FastLED.clear(); FastLED.show(); updateEEPROM();
        break;
      case BUTT_HASH:
        switch (this_mode) {
          case 0: if (++backlight_mode > 5) backlight_mode = 0;
            break;
          case 1: if (++vu_mode > 9) vu_mode = 0;
            break;
          case 4:
          case 7: if (++freq_strobe_mode > 3) freq_strobe_mode = 0;
            break;
          case 6:
            break;
        }
        break;
      case BUTT_OK: digitalWrite(MLED_PIN, settings_mode ^ MLED_ON); settings_mode = !settings_mode;
        break;
      case BUTT_UP:
        if (settings_mode) {
          // ВВЕРХ общие настройки
          EMPTY_BRIGHT = smartIncr(EMPTY_BRIGHT, 5, 0, 255);
        } else {
          switch (this_mode) {
            case 0:
              switch (backlight_mode) {
                case 0: if (++whiteKelvin_mode > 4) whiteKelvin_mode = 0;
                  break;
                case 1: BACKLIGHT_PERLIN_SPEED = smartIncr(BACKLIGHT_PERLIN_SPEED, 2, 1, 50);
                  break;
                case 2: BACKLIGHT_PERLIN_SPEED = smartIncr(BACKLIGHT_PERLIN_SPEED, 2, 1, 50);
                  break;
                case 3: LIGHT_SAT = smartIncr(LIGHT_SAT, 20, 0, 255);
                  break;
                case 4: LIGHT_SAT = smartIncr(LIGHT_SAT, 20, 0, 255);
                  break;
                case 5: RAINBOW_STEP_2 = smartIncrFloat(RAINBOW_STEP_2, 0.5, 0.5, 10);
                  break;
              }
              break;
            case 1: RAINBOW_STEP = smartIncrFloat(RAINBOW_STEP, 0.5, 0.5, 20);
              break;
            case 2:
            case 3:
            case 4: MAX_COEF_FREQ = smartIncrFloat(MAX_COEF_FREQ, 0.1, 0, 5);
              break;
            case 5: STROBE_PERIOD = smartIncr(STROBE_PERIOD, 20, 1, 1000);
              break;
            case 6:
            case 7: MAX_COEF_FREQ = smartIncrFloat(MAX_COEF_FREQ, 0.1, 0.0, 10);
              break;
            case 8: HUE_START = smartIncr(HUE_START, 10, 0, 255);
              break;
          }
        }
        break;
      case BUTT_DOWN:
        if (settings_mode) {
          // ВНИЗ общие настройки
          EMPTY_BRIGHT = smartIncr(EMPTY_BRIGHT, -5, 0, 255);
        } else {
          switch (this_mode) {
            case 0:
              switch (backlight_mode) {
                case 0:
                case 1: BACKLIGHT_PERLIN_SPEED = smartIncr(BACKLIGHT_PERLIN_SPEED, -2, 1, 50);
                  break;
                case 2: BACKLIGHT_PERLIN_SPEED = smartIncr(BACKLIGHT_PERLIN_SPEED, -2, 1, 50);
                  break;
                case 3: LIGHT_SAT = smartIncr(LIGHT_SAT, -20, 0, 255);
                  break;
                case 4: LIGHT_SAT = smartIncr(LIGHT_SAT, -20, 0, 255);
                  break;
                case 5: RAINBOW_STEP_2 = smartIncrFloat(RAINBOW_STEP_2, -0.5, 0.5, 10);
              }
              break;
            case 1: RAINBOW_STEP = smartIncrFloat(RAINBOW_STEP, -0.5, 0.5, 20);
              break;
            case 2:
            case 3:
            case 4: MAX_COEF_FREQ = smartIncrFloat(MAX_COEF_FREQ, -0.1, 0, 5);
              break;
            case 5: STROBE_PERIOD = smartIncr(STROBE_PERIOD, -20, 1, 1000);
              break;
            case 6:
            case 7: MAX_COEF_FREQ = smartIncrFloat(MAX_COEF_FREQ, -0.1, 0.0, 10);
              break;
            case 8: HUE_START = smartIncr(HUE_START, -10, 0, 255);
              break;
          }
        }
        break;
      case BUTT_LEFT:
        if (settings_mode) {
          // ВЛЕВО общие настройки
          BRIGHTNESS = smartIncr(BRIGHTNESS, -20, 0, 255);
          FastLED.setBrightness(BRIGHTNESS);
        } else {
          switch (this_mode) {
            case 0:
              switch (backlight_mode) {
                case 0: whiteLightBrightness = smartIncr(whiteLightBrightness, -20, 10, 250);
                  break;
                case 1: BACKLIGHT_PERLIN_RAINBOW_SPEED = smartIncr(BACKLIGHT_PERLIN_RAINBOW_SPEED, -50, 1, 1500);
                  break;
                case 2: BACKLIGHT_FIRE_STEP = smartIncr(BACKLIGHT_FIRE_STEP, -10, 1, 100);
                  break;
                case 3: LIGHT_COLOR = smartIncr(LIGHT_COLOR, -10, 0, 255);
                  break;
                case 4: COLOR_SPEED = smartIncr(COLOR_SPEED, -10, 0, 255);
                  break;
                case 5: RAINBOW_PERIOD = smartIncr(RAINBOW_PERIOD, -1, -20, 20);
                  break;
              }
              break;
            case 1: SMOOTH = smartIncrFloat(SMOOTH, -0.05, 0.05, 1);
              break;
            case 2:
            case 3:
            case 4: SMOOTH_FREQ = smartIncrFloat(SMOOTH_FREQ, -0.05, 0.05, 1);
              break;
            case 5: STROBE_SMOOTH = smartIncr(STROBE_SMOOTH, -20, 0, 255);
              break;
            case 6:
            case 7: RUNNING_SPEED = smartIncr(RUNNING_SPEED, -10, 1, 255);
              break;
            case 8: HUE_STEP = smartIncr(HUE_STEP, -1, 1, 255);
              break;
          }
        }
        break;
      case BUTT_RIGHT:
        if (settings_mode) {
          // ВПРАВО общие настройки
          BRIGHTNESS = smartIncr(BRIGHTNESS, 20, 0, 255);
          FastLED.setBrightness(BRIGHTNESS);
        } else {
          switch (this_mode) {
            case 0:
              switch (backlight_mode) {
                case 0: whiteLightBrightness = smartIncr(whiteLightBrightness, 20, 10, 250);
                  break;
                case 1: BACKLIGHT_PERLIN_RAINBOW_SPEED = smartIncr(BACKLIGHT_PERLIN_RAINBOW_SPEED, 50, 1, 1500);
                  break;
                case 2: BACKLIGHT_FIRE_STEP = smartIncr(BACKLIGHT_FIRE_STEP, 10, 1, 100);
                  break;
                case 3: LIGHT_COLOR = smartIncr(LIGHT_COLOR, 10, 0, 255);
                  break;
                case 4: COLOR_SPEED = smartIncr(COLOR_SPEED, 10, 0, 255);
                  break;
                case 5: RAINBOW_PERIOD = smartIncr(RAINBOW_PERIOD, 1, -20, 20);
                  break;
              }
              break;
            case 1: SMOOTH = smartIncrFloat(SMOOTH, 0.05, 0.05, 1);
              break;
            case 2:
            case 3:
            case 4: SMOOTH_FREQ = smartIncrFloat(SMOOTH_FREQ, 0.05, 0.05, 1);
              break;
            case 5: STROBE_SMOOTH = smartIncr(STROBE_SMOOTH, 20, 0, 255);
              break;
            case 6:
            case 7: RUNNING_SPEED = smartIncr(RUNNING_SPEED, 10, 1, 255);
              break;
            case 8: HUE_STEP = smartIncr(HUE_STEP, 1, 1, 255);
              break;
          }
        }
        break;
      default: eeprom_flag = false;   // если не распознали кнопку, не обновляем настройки!
        break;
    }
    ir_flag = false;
  }
}
#endif
