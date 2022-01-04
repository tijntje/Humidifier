#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

void initTFT(void);
void drawUI(int fanlevel, int currenthumidity, bool humidtyTooLow);
void drawSetpointChange(int setpoint);