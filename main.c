#include <iostream>

#include <Fonts/FreeSerif9pt7b.h>
#include <SSD1306.h>

using namespace std;

#define SSD1306_WHITE 0xFF
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };
void  testdrawline();      // Draw many lines
void  testdrawRect();      // Draw rectangles (outlines)
void  testfillrect();      // Draw rectangles (filled)
void  testdrawcircle();    // Draw circles (outlines)
void  testfillcircle();    // Draw circles (filled)
void  testdrawroundrect(); // Draw rounded rectangles (outlines)
void  testfillroundrect(); // Draw rounded rectangles (filled)
void  testdrawtriangle();  // Draw triangles (outlines)
void  testfilltriangle();  // Draw triangles (filled)
void  testdrawchar();      // Draw characters of the default font
void  testdrawstyles();    // Draw 'stylized' characters
void  testscrolltext();    // Draw scrolling text
void  testdrawbitmap();    // Draw a small bitmap image
SSD1306 OledCanvas(128,64);
int main()
{
    OledCanvas.setFont(&FreeSerif9pt7b);
    OledCanvas.puts((uint8_t*)&"Hello World!",12);
    OledCanvas.puts((uint8_t*)&"\nSalixus",8);
	OledCanvas.puts((uint8_t*)&"\nSalih Palamut",14);
    OledCanvas.Display();
	sleep(5);
	
	  testdrawbitmap();    // Draw a small bitmap image
	
testdrawline();      // Draw many lines

  testdrawRect();      // Draw rectangles (outlines)


  /*testfillrect();      // Draw rectangles (filled)

  testdrawcircle();    // Draw circles (outlines)

  testfillcircle();    // Draw circles (filled)

  testdrawroundrect(); // Draw rounded rectangles (outlines)

  testfillroundrect(); // Draw rounded rectangles (filled)

  testdrawtriangle();  // Draw triangles (outlines)

  testfilltriangle();  // Draw triangles (filled)

  testdrawchar();      // Draw characters of the default font

  testdrawstyles();    // Draw 'stylized' characters

  testscrolltext();    // Draw scrolling text



  // Invert and restore display, pausing in-between
  OledCanvas.invertDisplay(true);
  sleep(1000);
  OledCanvas.invertDisplay(false);
  sleep(1000);

  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT);

   */

    return 0;
}

void testdrawline() {
  int16_t i;

 OledCanvas.clearDisplay(); // Clear display buffer

  for(i=0; i<OledCanvas.width(); i+=4) {
    OledCanvas.drawLine(0, 0, i, OledCanvas.height()-1, SSD1306_WHITE);
    OledCanvas.Display(); // Update screen with each newly-drawn line
    sleep(0.5);
  }
  for(i=0; i<OledCanvas.height(); i+=4) {
    OledCanvas.drawLine(0, 0, OledCanvas.width()-1, i, SSD1306_WHITE);
    OledCanvas.Display();
    sleep(.5);
  }
  sleep(5);

  OledCanvas.clearDisplay();

  for(i=0; i<OledCanvas.width(); i+=4) {
    OledCanvas.drawLine(0, OledCanvas.height()-1, i, 0, SSD1306_WHITE);
    OledCanvas.Display();
    sleep(0.5);
  }
  for(i=OledCanvas.height()-1; i>=0; i-=4) {
    OledCanvas.drawLine(0, OledCanvas.height()-1, OledCanvas.width()-1, i, SSD1306_WHITE);
    OledCanvas.Display();
    sleep(0.5);
  }
  sleep(5);

  OledCanvas.clearDisplay();

  for(i=OledCanvas.width()-1; i>=0; i-=4) {
    OledCanvas.drawLine(OledCanvas.width()-1, OledCanvas.height()-1, i, 0, SSD1306_WHITE);
    OledCanvas.Display();
    sleep(0.5);
  }
  for(i=OledCanvas.height()-1; i>=0; i-=4) {
    OledCanvas.drawLine(OledCanvas.width()-1, OledCanvas.height()-1, 0, i, SSD1306_WHITE);
    OledCanvas.Display();
    sleep(0.5);
  }
  sleep(5);

  OledCanvas.clearDisplay();

  for(i=0; i<OledCanvas.height(); i+=4) {
    OledCanvas.drawLine(OledCanvas.width()-1, 0, 0, i, SSD1306_WHITE);
    OledCanvas.Display();
    sleep(0.5);
  }
  for(i=0; i<OledCanvas.width(); i+=4) {
    OledCanvas.drawLine(OledCanvas.width()-1, 0, i, OledCanvas.height()-1, SSD1306_WHITE);
    OledCanvas.Display();
    sleep(0.5);
  }

  sleep(5); // Pause for 2 seconds
}

void testdrawRect(void) {
  OledCanvas.clearDisplay();

  for(int16_t i=0; i<OledCanvas.height()/2; i+=2) {
    OledCanvas.drawRect(i, i, OledCanvas.width()-2*i, OledCanvas.height()-2*i, SSD1306_WHITE);
    OledCanvas.Display(); // Update screen with each newly-drawn rectangle
    sleep(0.5);
  }

  sleep(5);
}

void testdrawbitmap(void) {
  OledCanvas.clearDisplay();

  OledCanvas.drawBitmap(
    (OledCanvas.width()  - LOGO_WIDTH ) / 2,
    (OledCanvas.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  OledCanvas.Display();
  sleep(1000);
}

/*
void testfillrect(void) {
  OledCanvas.clearDisplay();

  for(int16_t i=0; i<OledCanvas.height()/2; i+=3) {
    // The INVERSE color is used so rectangles alternate white/black
    OledCanvas.fillRect(i, i, OledCanvas.width()-i*2, OledCanvas.height()-i*2, SSD1306_INVERSE);
    OledCanvas.Display(); // Update screen with each newly-drawn rectangle
    sleep(1);
  }

  sleep(2000);
}

void testdrawcircle(void) {
  OledCanvas.clearDisplay();

  for(int16_t i=0; i<max(OledCanvas.width(),OledCanvas.height())/2; i+=2) {
    OledCanvas.DrawCircle(OledCanvas.width()/2, OledCanvas.height()/2, i, SSD1306_WHITE);
    OledCanvas.Display();
    sleep(1);
  }

  sleep(2000);
}

void testfillcircle(void) {
  OledCanvas.clearDisplay();

  for(int16_t i=max(OledCanvas.width(),OledCanvas.height())/2; i>0; i-=3) {
    // The INVERSE color is used so circles alternate white/black
    OledCanvas.fillCircle(OledCanvas.width() / 2, OledCanvas.height() / 2, i, SSD1306_INVERSE);
    OledCanvas.Display(); // Update screen with each newly-drawn circle
    sleep(1);
  }

  sleep(2000);
}

void testdrawroundrect(void) {
  OledCanvas.clearDisplay();

  for(int16_t i=0; i<OledCanvas.height()/2-2; i+=2) {
    OledCanvas.DrawRoundRect(i, i, OledCanvas.width()-2*i, OledCanvas.height()-2*i,
      OledCanvas.height()/4, SSD1306_WHITE);
    OledCanvas.Display();
    sleep(1);
  }

  sleep(2000);
}

void testfillroundrect(void) {
  OledCanvas.clearDisplay();

  for(int16_t i=0; i<OledCanvas.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/black
    OledCanvas.fillRoundRect(i, i, OledCanvas.width()-2*i, OledCanvas.height()-2*i,
      OledCanvas.height()/4, SSD1306_INVERSE);
    OledCanvas.Display();
    sleep(1);
  }

  sleep(2000);
}

void testdrawtriangle(void) {
  OledCanvas.clearDisplay();

  for(int16_t i=0; i<max(OledCanvas.width(),OledCanvas.height())/2; i+=5) {
    OledCanvas.DrawTriangle(
      OledCanvas.width()/2  , OledCanvas.height()/2-i,
      OledCanvas.width()/2-i, OledCanvas.height()/2+i,
      OledCanvas.width()/2+i, OledCanvas.height()/2+i, SSD1306_WHITE);
    OledCanvas.Display();
    sleep(1);
  }

  sleep(2000);
}

void testfilltriangle(void) {
  OledCanvas.clearDisplay();

  for(int16_t i=max(OledCanvas.width(),OledCanvas.height())/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    OledCanvas.fillTriangle(
      OledCanvas.width()/2  , OledCanvas.height()/2-i,
      OledCanvas.width()/2-i, OledCanvas.height()/2+i,
      OledCanvas.width()/2+i, OledCanvas.height()/2+i, SSD1306_INVERSE);
    OledCanvas.Display();
    sleep(1);
  }

  sleep(2000);
}

void testdrawchar(void) {
  OledCanvas.clearDisplay();

  OledCanvas.setTextSize(1);      // Normal 1:1 pixel scale
  OledCanvas.setTextColor(SSD1306_WHITE); // Draw white text
  OledCanvas.setCursor(0, 0);     // Start at top-left corner
  OledCanvas.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the OledCanvas. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') OledCanvas.write(' ');
    else          OledCanvas.write(i);
  }

  OledCanvas.Display();
  sleep(2000);
}

void testdrawstyles(void) {
  OledCanvas.clearDisplay();

  OledCanvas.setTextSize(1);             // Normal 1:1 pixel scale
  OledCanvas.setTextColor(SSD1306_WHITE);        // Draw white text
  OledCanvas.setCursor(0,0);             // Start at top-left corner
  OledCanvas.println(F("Hello, world!"));

  OledCanvas.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  OledCanvas.println(3.141592);

  OledCanvas.setTextSize(2);             // Draw 2X-scale text
  OledCanvas.setTextColor(SSD1306_WHITE);
  OledCanvas.print(F("0x")); OledCanvas.println(0xDEADBEEF, HEX);

  OledCanvas.Display();
  sleep(2000);
}

void testscrolltext(void) {
  OledCanvas.clearDisplay();

  OledCanvas.setTextSize(2); // Draw 2X-scale text
  OledCanvas.setTextColor(SSD1306_WHITE);
  OledCanvas.setCursor(10, 0);
  OledCanvas.println(F("scroll"));
  OledCanvas.Display();      // Show initial text
  sleep(100);

  // Scroll in various directions, pausing in-between:
  OledCanvas.startscrollright(0x00, 0x0F);
  sleep(2000);
  OledCanvas.stopscroll();
  sleep(1000);
  OledCanvas.startscrollleft(0x00, 0x0F);
  sleep(2000);
  OledCanvas.stopscroll();
  sleep(1000);
  OledCanvas.startscrolldiagright(0x00, 0x07);
  sleep(2000);
  OledCanvas.startscrolldiagleft(0x00, 0x07);
  sleep(2000);
  OledCanvas.stopscroll();
  sleep(1000);
}



#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, OledCanvas.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...
    OledCanvas.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      OledCanvas.DrawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    OledCanvas.Display(); // Show the display buffer on the screen
    sleep(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= OledCanvas.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, OledCanvas.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}*/