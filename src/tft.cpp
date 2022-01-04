#include "tft.h"
#include "log.h"
#include "TFT_eSPI.h"
#include "Free_Fonts.h"

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

struct Bar{
    int x;
    int y;
    int width;
    int height;
};
const struct Bar bar1 = {10, 170, 115, 45};
const struct Bar bar2 = {10, 120, 115, 45};
const struct Bar bar3 = {10, 70, 115, 45};

#define RECT_RADIUS 5
enum barMode {enabled, disabled, active};

 void drawBars();
 void drawBar(Bar bar, barMode mode);

void initTFT()
 {
  tft.init();
  tft.setRotation(4);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour
  log_printf(MY_LOG_FORMAT("TFT sucessfully initialized."));
 }

 void drawHumidity(int humidity, int humidtyTooLow)
 {
  tft.setFreeFont(FSB18);
  tft.setTextColor((humidtyTooLow) ? TFT_RED : TFT_GREEN, TFT_BLACK);
  tft.setCursor(35, 45);
  tft.printf("%i %%",humidity);
 }

 void drawBars(bool humidtyTooLow, int fanlevel)
 {
    if (fanlevel == 0)
    {
     drawBar(bar1, disabled);
     drawBar(bar2, disabled);
     drawBar(bar3, disabled);
     return;
    }

    if (!humidtyTooLow) {
     drawBar(bar1, enabled);
     drawBar(bar2, enabled);
     drawBar(bar3, enabled);
    } else {
     drawBar(bar1, (fanlevel >=1) ? active : enabled);
     drawBar(bar2, (fanlevel >=2) ? active : enabled);
     drawBar(bar3, (fanlevel ==3) ? active : enabled);
    }
 }

  void drawBar(Bar bar, barMode mode)
 {
     switch (mode)
     {
       case enabled:
         tft.drawRoundRect(bar.x, bar.y, bar.width, bar.height, RECT_RADIUS, TFT_BLUE);
         break;
       case disabled:
         tft.drawRoundRect(bar.x, bar.y, bar.width, bar.height, RECT_RADIUS, TFT_DARKGREY);
         break;
       case active:
         tft.fillRoundRect(bar.x, bar.y, bar.width, bar.height, RECT_RADIUS, TFT_BLUE);
         break;
     }
 }

    void drawUI(int fanlevel, int currenthumidity, bool humidtyTooLow)
    {
        tft.fillScreen(TFT_BLACK);
        drawBars(humidtyTooLow, fanlevel);
        drawHumidity(currenthumidity, humidtyTooLow);
    }

    void drawSetpointChange(int setpoint)
    {
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_ORANGE, TFT_BLACK);

        tft.setFreeFont(FSB12);
        tft.setCursor(25, 85);
        tft.printf("Setpoint:");
        tft.setFreeFont(FSB18);
        tft.setCursor(35, 125);
        tft.printf("%i %%",setpoint);
    }