#include "rgbled.h"

#if defined(RGB_LED_PIN) && (RGB_LED_PIN!=255) // ============================== Everything ignored if not defined ==============================

static void writeDiscreteRgb(uint8_t pin, uint8_t brightness) {
  analogWrite(pin, 255 - brightness);
}

RgbLed::RgbLed()
  : strip(NUM_RGB_LEDS, RGB_LED_PIN, RGB_LED_ORDER + NEO_KHZ800),
    flashCount(0), lastFlash(0), inited(false),
    cycle(false), lastCycle(0), cycleState(0), state(RGB_OFF),
    stationAnimationActive(false), animationStationId(0), lastStationId(0), animationHue(0),
    stationAnimationStart(0), lastAnimationChange(0) {}

void RgbLed::init() {
  strip.begin();
  strip.setBrightness(64);
  strip.show();
  #if defined(DISCRETE_RGB1_R) && defined(DISCRETE_RGB1_G) && defined(DISCRETE_RGB1_B) && \
      defined(DISCRETE_RGB2_R) && defined(DISCRETE_RGB2_G) && defined(DISCRETE_RGB2_B) && \
      defined(DISCRETE_RGB3_R) && defined(DISCRETE_RGB3_G) && defined(DISCRETE_RGB3_B)
    const uint8_t pins[] = {DISCRETE_RGB1_R, DISCRETE_RGB1_G, DISCRETE_RGB1_B,
                            DISCRETE_RGB2_R, DISCRETE_RGB2_G, DISCRETE_RGB2_B,
                            DISCRETE_RGB3_R, DISCRETE_RGB3_G, DISCRETE_RGB3_B};
    for (uint8_t pin : pins) {
      pinMode(pin, OUTPUT);
      writeDiscreteRgb(pin, 5);
    }
  #endif
  inited = true;
}

bool RgbLed::isInitialized() { return inited; }

void RgbLed::set(uint8_t r, uint8_t g, uint8_t b) {
  strip.setPixelColor(0, strip.Color(r, g, b));
  strip.show();
}

void RgbLed::playing(uint16_t stationId) {
  state = RGB_PLAYING;
  if (!cycle) set(0, 128, 0);
  if (stationId > 0) {
    if (stationId != lastStationId) {
      lastStationId = stationId;
      animationStationId = stationId;
      stationAnimationActive = true;
      stationAnimationStart = millis();
      lastAnimationChange = stationAnimationStart;
      animationHue = (uint8_t)random(256);
      setAnimationColor(animationHue);
    } else if (!stationAnimationActive) setStationColors(stationId);
  }
  else {
    stationAnimationActive = false;
    #if defined(DISCRETE_RGB1_R) && defined(DISCRETE_RGB1_G) && defined(DISCRETE_RGB1_B) && \
        defined(DISCRETE_RGB2_R) && defined(DISCRETE_RGB2_G) && defined(DISCRETE_RGB2_B) && \
        defined(DISCRETE_RGB3_R) && defined(DISCRETE_RGB3_G) && defined(DISCRETE_RGB3_B)
      const uint8_t pins[] = {DISCRETE_RGB1_R, DISCRETE_RGB1_G, DISCRETE_RGB1_B,
                              DISCRETE_RGB2_R, DISCRETE_RGB2_G, DISCRETE_RGB2_B,
                              DISCRETE_RGB3_R, DISCRETE_RGB3_G, DISCRETE_RGB3_B};
      for (uint8_t pin : pins) writeDiscreteRgb(pin, 255);
    #endif
  }
}

void RgbLed::stopped() {
  state = RGB_STOPPED;
  stationAnimationActive = false;
  if (!cycle) set(128, 0, 0);
  #if defined(DISCRETE_RGB1_R) && defined(DISCRETE_RGB1_G) && defined(DISCRETE_RGB1_B) && \
      defined(DISCRETE_RGB2_R) && defined(DISCRETE_RGB2_G) && defined(DISCRETE_RGB2_B) && \
      defined(DISCRETE_RGB3_R) && defined(DISCRETE_RGB3_G) && defined(DISCRETE_RGB3_B)
    const uint8_t pins[] = {DISCRETE_RGB1_R, DISCRETE_RGB1_G, DISCRETE_RGB1_B,
                            DISCRETE_RGB2_R, DISCRETE_RGB2_G, DISCRETE_RGB2_B,
                            DISCRETE_RGB3_R, DISCRETE_RGB3_G, DISCRETE_RGB3_B};
    for (uint8_t pin : pins) writeDiscreteRgb(pin, 5);
  #endif
}

void RgbLed::setStationColors(uint16_t stationId) {
  #if defined(DISCRETE_RGB1_R) && defined(DISCRETE_RGB1_G) && defined(DISCRETE_RGB1_B) && \
      defined(DISCRETE_RGB2_R) && defined(DISCRETE_RGB2_G) && defined(DISCRETE_RGB2_B) && \
      defined(DISCRETE_RGB3_R) && defined(DISCRETE_RGB3_G) && defined(DISCRETE_RGB3_B)
    const uint16_t stationIndex = stationId - 1;
    const uint16_t grayCode = stationIndex ^ (stationIndex >> 1);
    const uint8_t grayPosition = grayCode & 0x03;
    const uint8_t distinctLed = grayPosition == 1 ? 1 : (grayPosition == 3 ? 2 : (grayPosition == 2 ? 1 : 0));
    const uint8_t sharedColor = stationIndex % 6;
    const uint8_t distinctColor = (sharedColor + 3) % 6;
    const uint8_t red[] =   {255, 0, 0, 0, 255, 255};
    const uint8_t green[] = {0, 255, 0, 255, 0, 255};
    const uint8_t blue[] =  {0, 0, 255, 255, 255, 0};
    const uint8_t colors[] = {
      distinctLed == 0 ? distinctColor : sharedColor,
      distinctLed == 1 ? distinctColor : sharedColor,
      distinctLed == 2 ? distinctColor : sharedColor
    };
    const uint8_t redPins[] = {DISCRETE_RGB1_R, DISCRETE_RGB2_R};
    const uint8_t greenPins[] = {DISCRETE_RGB1_G, DISCRETE_RGB2_G};
    const uint8_t bluePins[] = {DISCRETE_RGB1_B, DISCRETE_RGB2_B};
    for (uint8_t led = 0; led < 2; led++) {
      writeDiscreteRgb(redPins[led], red[colors[led]]);
      writeDiscreteRgb(greenPins[led], green[colors[led]]);
      writeDiscreteRgb(bluePins[led], blue[colors[led]]);
    }
    writeDiscreteRgb(DISCRETE_RGB3_R, red[colors[2]]);
    writeDiscreteRgb(DISCRETE_RGB3_G, green[colors[2]]);
    writeDiscreteRgb(DISCRETE_RGB3_B, blue[colors[2]]);
  #else
    (void)stationId;
  #endif
}

void RgbLed::setAnimationColor(uint8_t hue) {
  #if defined(DISCRETE_RGB1_R) && defined(DISCRETE_RGB1_G) && defined(DISCRETE_RGB1_B) && \
      defined(DISCRETE_RGB2_R) && defined(DISCRETE_RGB2_G) && defined(DISCRETE_RGB2_B) && \
      defined(DISCRETE_RGB3_R) && defined(DISCRETE_RGB3_G) && defined(DISCRETE_RGB3_B)
    const uint8_t section = hue / 43;
    const uint8_t offset = (hue - section * 43) * 6;
    const uint8_t rising = offset;
    const uint8_t falling = 255 - offset;
    uint8_t red, green, blue;
    switch (section) {
      case 0: red = 255; green = rising; blue = 0; break;
      case 1: red = falling; green = 255; blue = 0; break;
      case 2: red = 0; green = 255; blue = rising; break;
      case 3: red = 0; green = falling; blue = 255; break;
      case 4: red = rising; green = 0; blue = 255; break;
      default: red = 255; green = 0; blue = falling; break;
    }
    const uint8_t redPins[] = {DISCRETE_RGB1_R, DISCRETE_RGB2_R, DISCRETE_RGB3_R};
    const uint8_t greenPins[] = {DISCRETE_RGB1_G, DISCRETE_RGB2_G, DISCRETE_RGB3_G};
    const uint8_t bluePins[] = {DISCRETE_RGB1_B, DISCRETE_RGB2_B, DISCRETE_RGB3_B};
    for (uint8_t led = 0; led < 3; led++) {
      writeDiscreteRgb(redPins[led], red);
      writeDiscreteRgb(greenPins[led], green);
      writeDiscreteRgb(bluePins[led], blue);
    }
  #else
    (void)hue;
  #endif
}

void RgbLed::trackChange() {
  // flash blue a few times then restore previous state color
  flashCount = 6;
  lastFlash = millis();
}

void RgbLed::loop() {
  if (stationAnimationActive) {
    const unsigned long now = millis();
    if (now - stationAnimationStart >= 2000UL) {
      stationAnimationActive = false;
      setStationColors(animationStationId);
    } else if (now - lastAnimationChange >= 100UL) {
      uint8_t nextHue;
      uint8_t distance;
      do {
        nextHue = (uint8_t)random(256);
        distance = (uint8_t)(nextHue - animationHue);
      } while (distance < 64 || distance > 192);
      animationHue = nextHue;
      lastAnimationChange = now;
      setAnimationColor(animationHue);
    }
  }

  // track-change flash handling
  if (flashCount > 0) {
    if (millis() - lastFlash > 150) {
      // toggle between off and blue
      if (strip.getPixelColor(0) != 0) set(0,0,0); else set(0,0,128);
      lastFlash = millis();
      flashCount--;
      // when finished, restore color to current state
      if (flashCount == 0) {
        // restore according to state unless cycle is active
        if (!cycle) {
          if (state == RGB_PLAYING) set(0,128,0);
          else if (state == RGB_STOPPED) set(128,0,0);
          else set(0,0,0);
        }
      }
    }
  }

  // non-blocking cycle (Red -> Green -> Blue)
  if (cycle) {
    if (millis() - lastCycle > 1000) {
      lastCycle = millis();
      switch (cycleState) {
        case 0: set(255,0,0); break;
        case 1: set(0,255,0); break;
        default: set(0,0,255); break;
      }
      cycleState = (cycleState + 1) % 3;
    }
  }
}

#endif // defined(RGB_LED_PIN) && (RGB_LED_PIN!=255)

RgbLed rgbled;
