#include <Arduino.h>
#include "NeoPatterns.hpp"

// Which pin on the Arduino is connected to the NeoPixels?

void PatternHandler(NeoPatterns *aLedsPtr);

#define PIN_RADAREYE   6
#define PIN_BLUE_LED        7 
#define PIN_DISCO_LED       8

NeoPatterns radarEyePixel = NeoPatterns(20, PIN_RADAREYE, NEO_GRB + NEO_KHZ800, &PatternHandler);
NeoPatterns ring1 = NeoPatterns(&radarEyePixel, 0, 20, true, &PatternHandler);
NeoPatterns discoRing = NeoPatterns(108, PIN_DISCO_LED, NEO_GRB + NEO_KHZ800, &DiscoHandler);
 NeoPatterns ring3 = NeoPatterns(&discoRing, 0, 60, true, &DiscoHandler);
 NeoPatterns ring4 = NeoPatterns(&discoRing, 60, 48, true, &DiscoHandler);
// NeoPatterns ring5 = NeoPatterns(&allPixel, 32, 8, true, &PatternHandler);
NeoPatterns blueLED = NeoPatterns(2,PIN_BLUE_LED,NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  ring1.begin();
  blueLED.begin();
  //ring2.begin();
  ring3.begin();
  ring4.begin();
  //ring5.begin();

  ring1.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE;
  //ring2.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE;
  ring3.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE; 
  ring4.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE;
  // ring5.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE;

  delay(300); // to avoid partial patterns at power up

  ring1.ColorWipe(COLOR32_PURPLE, 50);
  blueLED.ColorWipe((0,0,128),100); //COLOR_BLUE
  //blueLED.setPixelColor(0,0,0,128);
  //ring2.ColorWipe(COLOR32_RED, 50);
  ring3.ColorWipe(COLOR32_GREEN, 50);
  ring4.ColorWipe(COLOR32_BLUE, 50);
  // ring5.ColorWipe(COLOR32_RED, 50);

//    bar24.ScannerExtended(COLOR32_BLUE, 5, 50, 1,
//            FLAG_SCANNER_EXT_ROCKET | FLAG_SCANNER_EXT_VANISH_COMPLETE | FLAG_SCANNER_EXT_START_AT_BOTH_ENDS);


  Serial.println("started");
}

void loop() {
  // put your main code here, to run repeatedly:
  ring1.update();

  //ring2.update();
  ring3.update();
  ring4.update();
  // ring5.update();

}

void DiscoHandler(NeoPatterns *aLedsPtr){
  static int8_t sState = 0;
switch   (sState){
  case 0:
      aLedsPtr->ColorWipe(COLOR32_ORANGE,10,0,0);
      break;  
  case 1:
      aLedsPtr->RainbowCycle(10, DIRECTION_UP);
      break;
  case 2:
        // switch to random
        aLedsPtr->RainbowCycle(10, DIRECTION_DOWN);
        sState = -1; // Start from beginning
        break;
    default:
        Serial.println("ERROR");
        break;      
  }
  sState ++;
}

void PatternHandler(NeoPatterns *aLedsPtr) {
      static int8_t sState = 0;

    switch (sState) {
    case 0:
        aLedsPtr->ColorWipeD(COLOR32_RED, 3000);
        break;
    case 1:
        aLedsPtr->Delay(1500);
        break;
    case 2:
        aLedsPtr->Heartbeat(COLOR32_GREEN, 80, 0);
        break;
    case 3:
        aLedsPtr->Delay(1500);
        break;
    case 4:
        aLedsPtr->RainbowCycle(10, DIRECTION_UP);
        break;
    case 5:
        aLedsPtr->RainbowCycle(10, DIRECTION_DOWN);
        break;
    case 6:
        aLedsPtr->Heartbeat(COLOR32_BLUE, 80, 6, 0);
        break;
    case 7:
        aLedsPtr->Heartbeat(COLOR32_RED, 80, 5, 0);
        break;
    case 8:
        aLedsPtr->Heartbeat(COLOR32_ORANGE, 80, 4, 1);
        break;
    case 9:
        //aLedsPtr->Fire(20, 260); // OK Fire(30, 260)is also OK
        //sState = -1; // Start from beginning
        ring1.ColorWipe(COLOR32_PURPLE, 80);
        break;
    case 10:
        // switch to random
        //initMultipleFallingStars(aLedsPtr, COLOR32_WHITE_HALF, 7, 30, 3, &allPatternsRandomHandler);
        ring1.ColorWipe(COLOR32_RED, 50);
        sState = -1; // Start from beginning
        break;
    default:
        Serial.println("ERROR");
        break;
    }

    Serial.print("PatterHandler: Pin=");
    Serial.print(aLedsPtr->getPin());
    Serial.print(" Length=");
    Serial.print(aLedsPtr->numPixels());
    Serial.print(" ActivePattern=");
    aLedsPtr->printPatternName(aLedsPtr->ActivePattern, &Serial);
    Serial.print("|");
    Serial.print(aLedsPtr->ActivePattern);
    Serial.print(" State=");
    Serial.println(sState);

    sState++;
}
