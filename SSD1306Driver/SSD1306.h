#ifndef _SSD1306_H_
#define _SSD1306_H_
#include "../Linux-Oled-GFX-Library/Linux_GFX.h"
//#include <Linux_GFX.h>
#include <unistd.h>//Needed for I2C port
#include <fcntl.h>//Needed for I2C port
#include <sys/ioctl.h>//Needed for I2C port
#include <linux/i2c-dev.h>//Needed for I2C port
#include <string.h>
/*
  ** First byte is always control byte. Data is followed after that.
  **
  ** There are two types of data in SSD_1306 OLED.
  ** 1. Command
  ** 2. Data
  **
  ** Control byte decides that the next byte is, command or data.
  **
  ** -------------------------------------------------------                        
  ** |              Control byte's | 6th bit  |   7th bit  |
  ** |-----------------------------|----------|------------|    
  ** |   Command                   |   0      |     0      |
  ** |-----------------------------|----------|------------|
  ** |   data                      |   1      |     0      |
  ** |-----------------------------|----------|------------|
  ** 
  ** Please refer the datasheet for more information. 
  **    
  */ 
 #define Oled_Cmd_Command 0x00
 #define Oled_Cmd_Data 0x40

class SSD1306 : public GFXcanvas1
{

public:
	SSD1306(int16_t w, int16_t h); // Constructor
 /*SSD1306(int16_t w, int16_t h,uint8_t addr);
 SSD1306(int16_t w, int16_t h,uint8_t addr,char * i2c);*/
  void SetI2CAddr(uint8_t addr);
	void SetI2CPath(char * i2c);
	void SetCursor( uint8_t lineNo, uint8_t cursorPos );
	void GoToNextLine( void );
	void InvertDisplay(bool need_to_invert);
	void SetBrightness(uint8_t brightnessValue);
	void StartScrollHorizontal( bool is_left_scroll,
                                           uint8_t start_line_no,
                                           uint8_t end_line_no
                                         );
void StartScrollVerticalHorizontal( bool is_vertical_left_scroll,
                                                   uint8_t start_line_no,
                                                   uint8_t end_line_no,
                                                   uint8_t vertical_area,
                                                   uint8_t rows
                                                );
void clearDisplay(void); 
void Fill(unsigned char data);
void Display(void);
 int DisplayInit(void);
	protected:
uint8_t	SSD1306_SLAVE_ADDR;
uint8_t	SSD1306_MAX_SEG;
uint8_t	SSD1306_MAX_LINE;
 uint8_t SSD1306_LineNum;
 uint8_t SSD1306_CursorPos;
 char *SSD1306_devicePath;

 void writeI2C(unsigned char* data, int bytes);
};


#endif // _SSD1306_H_
