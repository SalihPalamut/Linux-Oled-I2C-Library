#include "SSD1306.h"
/**************************************************************************/
/*!
   @brief    Instatiate a GFX context for graphics! Can only be done by a
   superclass
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
SSD1306::SSD1306(int16_t w, int16_t h):GFXcanvas1(w,h)
{
SSD1306_SLAVE_ADDR=0x3C;
SSD1306_MAX_SEG=w;
SSD1306_MAX_LINE=(h/8)-1;
SSD1306_LineNum=0;
SSD1306_CursorPos=0;
SSD1306_devicePath = (char*)"/dev/i2c-0";
 DisplayInit();
}
/*
SSD1306::SSD1306(int16_t w, int16_t h,uint8_t addr){
SSD1306(w,h);
SSD1306_SLAVE_ADDR=addr;
DisplayInit();
}
SSD1306::SSD1306(int16_t w, int16_t h,uint8_t addr,char * i2c){
SSD1306(w,h);
	SSD1306_SLAVE_ADDR=addr;
SSD1306_devicePath = i2c;
DisplayInit();
}*/

  void SSD1306::SetI2CAddr(uint8_t addr){
  SSD1306_SLAVE_ADDR=addr;
  }
	void SSD1306::SetI2CPath(char * i2c){
  SSD1306_devicePath = i2c;
  }



void SSD1306::SetCursor( uint8_t lineNo, uint8_t cursorPos )
{
  /* Move the Cursor to specified position only if it is in range */
  if((lineNo <= SSD1306_MAX_LINE) && (cursorPos < SSD1306_MAX_SEG))
  {
	  
    
uint8_t buf[7]={
		Oled_Cmd_Command,
0x21,              // cmd for the column start and end address
cursorPos,         // column start addr
(uint8_t)((int)(SSD1306_MAX_SEG) - 1), // column end addr
0x22,              // cmd for the page start and end address
lineNo,            // page start addr
SSD1306_MAX_LINE  // page end addr
};
writeI2C(buf, 7);
	SSD1306_LineNum   = lineNo;             // Save the specified line number
    SSD1306_CursorPos = cursorPos;          // Save the specified cursor position
  }
}

void  SSD1306::GoToNextLine( void )
{
  /*
  ** Increment the current line number.
  ** roll it back to first line, if it exceeds the limit. 
  */
  SSD1306_LineNum++;
  SSD1306_LineNum = (SSD1306_LineNum & SSD1306_MAX_LINE);

  SetCursor(SSD1306_LineNum,0); /* Finally move it to next line */
}

/*
** This function is specific to the SSD_1306 OLED.
** This function inverts the display.
**
**  Arguments:
**      need_to_invert   -> true  - invert display
**                          false - normal display        
** 
*/
void SSD1306::InvertDisplay(bool need_to_invert)
{
	uint8_t buf[]={
		Oled_Cmd_Command,
		(uint8_t)(need_to_invert?
		0xA7// Invert the display
		:
	0xA6// Normal display
 )
	};
writeI2C(buf, 2);
}

/*
** This function is specific to the SSD_1306 OLED.
** This function sets the brightness of  the display.
**
**  Arguments:
**      brightnessValue   -> true  - invert display  
** 
*/
void SSD1306::SetBrightness(uint8_t brightnessValue)
{
	uint8_t buf[]={
		Oled_Cmd_Command,
	0x81,// Contrast command
	brightnessValue// Contrast value (default value = 0x7F)
	};
	 writeI2C(buf, 3);
}

/*
** This function is specific to the SSD_1306 OLED.
** This function Scrolls the data right/left in horizontally.
**
**  Arguments:
**      is_left_scroll   -> true  - left horizontal scroll
                            false - right horizontal scroll
        start_line_no    -> Start address of the line to scroll 
        end_line_no      -> End address of the line to scroll                 
** 
*/
void SSD1306::StartScrollHorizontal( bool is_left_scroll,
                                           uint8_t start_line_no,
                                           uint8_t end_line_no
                                         )
{
	
	uint8_t buf[9]={
  Oled_Cmd_Command,
  (uint8_t)(is_left_scroll?
  0x27// left horizontal scroll
  :0x26 // right horizontal scroll
  ),
  0x00,            // Dummy byte (dont change)
  start_line_no,   // Start page address
  0x00,            // 5 frames interval
  end_line_no,     // End page address
  0x00,            // Dummy byte (dont change)
  0xFF,            // Dummy byte (dont change)
	0x2F};            // activate scroll
   writeI2C(buf, 9);
}

/*
** This function is specific to the SSD_1306 OLED.
** This function Scrolls the data in vertically and right/left horizontally(Diagonally).
**
**  Arguments:
**      is_vertical_left_scroll   -> true  - vertical and left horizontal scroll
**                                   false - vertical and right horizontal scroll
**      start_line_no             -> Start address of the line to scroll 
**      end_line_no               -> End address of the line to scroll 
**      vertical_area             -> Area for vertical scroll (0-63)
**      rows                      -> Number of rows to scroll vertically             
** 
*/
void SSD1306::StartScrollVerticalHorizontal( bool is_vertical_left_scroll,
                                                   uint8_t start_line_no,
                                                   uint8_t end_line_no,
                                                   uint8_t vertical_area,
                                                   uint8_t rows
                                                 )
{
  	uint8_t buf[11]={
  Oled_Cmd_Command,
  
 0xA3,            // Set Vertical Scroll Area
 0x00,            // Check datasheet
 vertical_area,   // area for vertical scroll
  
(uint8_t)(is_vertical_left_scroll?
  
    
 0x2A// vertical and left horizontal scroll
 :
  0x29// vertical and right horizontal scroll 
  ),
 
0x00,            // Dummy byte (dont change)
start_line_no,   // Start page address
0x00,            // 5 frames interval
end_line_no,     // End page address
rows,            // Vertical scrolling offset
	0x2F};            // activate scroll
	 writeI2C(buf, 11);
}
 
 /*
** This function Fills the complete OLED with this data byte.
**
**  Arguments:
**      data  -> Data to be filled in the OLED
** 
*/
void SSD1306::Fill(unsigned char data)
{
  unsigned int total  = 128 * 8;  // 8 pages x 128 segments x 8 bits of data
  total++;
  uint8_t *buf=(uint8_t *)malloc(total);
  buf[0]=Oled_Cmd_Data;//Send Oled Data
  memset(buf+1,data,total-1);
  //Fill the Display
  writeI2C(buf, total);
  free(buf);
  buf=NULL;
}

/*
** This function sends the commands that need to used to Initialize the OLED.
**
**  Arguments:
**      none
** 
*/
int SSD1306::DisplayInit(void)
{
	
  /*
  ** Commands to initialize the SSD_1306 OLED Display
  */
  uint8_t ssd1306_init[]={
Oled_Cmd_Command, //Send Oled Command
0xAE, // Entire Display OFF
0xD5, // Set Display Clock Divide Ratio and Oscillator Frequency
0x80, // Default Setting for Display Clock Divide Ratio and Oscillator Frequency that is recommended
0xA8, // Set Multiplex Ratio
0x3F, // 64 COM lines
0xD3, // Set display offset
0x00, // 0 offset
0x40, // Set first line as the start line of the display
0x8D, // Charge pump
0x14, // Enable charge dump during display on
0x20, // Set memory addressing mode
0x00, // Horizontal addressing mode
0xA1, // Set segment remap with column address 127 mapped to segment 0
0xC8, // Set com output scan direction, scan from com63 to com 0
0xDA, // Set com pins hardware configuration
0x12, // Alternative com pin configuration, disable com left/right remap
0x81, // Set contrast control
0x80, // Set Contrast to 128
0xD9, // Set pre-charge period
0xF1, // Phase 1 period of 15 DCLK, Phase 2 period of 1 DCLK
0xDB, // Set Vcomh deselect level
0x20, // Vcomh deselect level ~ 0.77 Vcc
0xA4, // Entire display ON, resume to RAM content display
0xA6, // Set Display in Normal Mode, 1 = ON, 0 = OFF
0x2E, // Deactivate scroll
0xAF}; // Display ON in normal mode
  writeI2C(ssd1306_init, 27);
  //Clear the display
  Fill(0x00);
  //Set cursor 0x0
  SetCursor(0,0); 
  
  return 0;
}

void SSD1306::clearDisplay(){

fillScreen(0);
  //Clear the display
  Fill(0x00);
  //Set cursor 0x0
  SetCursor(0,0); 
  setCursor(0,0);
}

void SSD1306::writeI2C(unsigned char* data, int bytes) {
	if(!SSD1306_devicePath)return;

    int i2cHandle;

    if ((i2cHandle = open(SSD1306_devicePath, O_RDWR)) < 0) {
        printf("error opening I2C %s\n",SSD1306_devicePath);
    }
    else {
        if (ioctl(i2cHandle, I2C_SLAVE, SSD1306_SLAVE_ADDR) < 0) {
            printf("Error at ioctl\n");
        }
        else {
            write(i2cHandle, data, bytes);
        }
            
        // Close the i2c device bus
        close(*SSD1306_devicePath);
    }
}


void SSD1306::Display(){
	uint32_t total=getCanvasSize();
  uint8_t *buf=(uint8_t *)malloc(total+1);
  buf[0]=Oled_Cmd_Data;//Send Oled Data
  memcpy(buf+1,getBuffer(),total);
  //Fill the Display
  writeI2C(buf, total);
  free(buf);
  buf=NULL;
}