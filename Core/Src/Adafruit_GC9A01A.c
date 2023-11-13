
#include "Adafruit_GC9A01A.h"
#include "main.h"


 uint16_t _width = GC9A01A_TFTWIDTH;
 uint16_t _height = GC9A01A_TFTHEIGHT;
extern SPI_HandleTypeDef hspi1;

#define MADCTL_MY 0x80  ///< Bottom to top
#define MADCTL_MX 0x40  ///< Right to left
#define MADCTL_MV 0x20  ///< Reverse Mode
#define MADCTL_ML 0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00 ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 ///< Blue-Green-Red pixel order
#define MADCTL_MH 0x04  ///< LCD refresh right to left


// Initialization sequence came from some early code provided by the
// manufacturer. Many of these registers are undocumented, some might
// be unnecessary, just playing along...
static const uint8_t initcmd[] = {
  GC9A01A_INREGEN2, 0,
  0xEB, 1, 0x14, // ?
  GC9A01A_INREGEN1, 0,
  GC9A01A_INREGEN2, 0,
  0xEB, 1, 0x14, // ?
  0x84, 1, 0x40, // ?
  0x85, 1, 0xFF, // ?
  0x86, 1, 0xFF, // ?
  0x87, 1, 0xFF, // ?
  0x88, 1, 0x0A, // ?
  0x89, 1, 0x21, // ?
  0x8A, 1, 0x00, // ?
  0x8B, 1, 0x80, // ?
  0x8C, 1, 0x01, // ?
  0x8D, 1, 0x01, // ?
  0x8E, 1, 0xFF, // ?
  0x8F, 1, 0xFF, // ?
  0xB6, 2, 0x00, 0x00, // ?
  GC9A01A_MADCTL, 1, MADCTL_MX | MADCTL_BGR,
  GC9A01A_COLMOD, 1, 0x05,
  0x90, 4, 0x08, 0x08, 0x08, 0x08, // ?
  0xBD, 1, 0x06, // ?
  0xBC, 1, 0x00, // ?
  0xFF, 3, 0x60, 0x01, 0x04, // ?
  GC9A01A1_POWER2, 1, 0x13,
  GC9A01A1_POWER3, 1, 0x13,
  GC9A01A1_POWER4, 1, 0x22,
  0xBE, 1, 0x11, // ?
  0xE1, 2, 0x10, 0x0E, // ?
  0xDF, 3, 0x21, 0x0c, 0x02, // ?
  GC9A01A_GAMMA1, 6, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2A,
  GC9A01A_GAMMA2, 6, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6F,
  GC9A01A_GAMMA3, 6, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2A,
  GC9A01A_GAMMA4, 6, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6F,
  0xED, 2, 0x1B, 0x0B, // ?
  0xAE, 1, 0x77, // ?
  0xCD, 1, 0x63, // ?
  // Unsure what this line (from manufacturer's boilerplate code) is
  // meant to do, but users reported issues, seems to work OK without:
  //0x70, 9, 0x07, 0x07, 0x04, 0x0E, 0x0F, 0x09, 0x07, 0x08, 0x03, // ?
  GC9A01A_FRAMERATE, 1, 0x34,
  0x62, 12, 0x18, 0x0D, 0x71, 0xED, 0x70, 0x70, // ?
            0x18, 0x0F, 0x71, 0xEF, 0x70, 0x70,
  0x63, 12, 0x18, 0x11, 0x71, 0xF1, 0x70, 0x70, // ?
            0x18, 0x13, 0x71, 0xF3, 0x70, 0x70,
  0x64, 7, 0x28, 0x29, 0xF1, 0x01, 0xF1, 0x00, 0x07, // ?
  0x66, 10, 0x3C, 0x00, 0xCD, 0x67, 0x45, 0x45, 0x10, 0x00, 0x00, 0x00, // ?
  0x67, 10, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x01, 0x54, 0x10, 0x32, 0x98, // ?
  0x74, 7, 0x10, 0x85, 0x80, 0x00, 0x00, 0x4E, 0x00, // ?
  0x98, 2, 0x3e, 0x07, // ?
  GC9A01A_TEON, 0,
  GC9A01A_INVON, 0,
  GC9A01A_SLPOUT, 0x80, // Exit sleep
  GC9A01A_DISPON, 0x80, // Display on
  0x00                  // End of list
};



#define SPI_CS_LOW() HAL_GPIO_WritePin(lcd_cs_GPIO_Port,lcd_cs_Pin,0)
#define SPI_CS_HIGH() HAL_GPIO_WritePin(lcd_cs_GPIO_Port,lcd_cs_Pin,1)


#define SPI_DC_LOW() HAL_GPIO_WritePin(lcd_dc_GPIO_Port,lcd_dc_Pin,0)
#define SPI_DC_HIGH() HAL_GPIO_WritePin(lcd_dc_GPIO_Port,lcd_dc_Pin,1)

void spiWrite(uint8_t *bytes, uint8_t nr) {
	HAL_SPI_Transmit(&hspi1, bytes, nr, 100);
}

#define SPI_WRITE16(a) spiWrite(a,2)


void sendCommand(uint8_t commandByte, uint8_t *dataBytes, uint8_t numDataBytes) {
  //SPI_BEGIN_TRANSACTION();
  //if (_cs >= 0)
    SPI_CS_LOW();


  SPI_DC_LOW();          // Command mode
  spiWrite(&commandByte,1); // Send the command byte

  SPI_DC_HIGH();
  for (int i = 0; i < numDataBytes; i++) {
       spiWrite(dataBytes,1); // Send the data bytes
      dataBytes++;

  }

  //if (_cs >= 0)
    SPI_CS_HIGH();
  //SPI_END_TRANSACTION();
}

/*!
    @brief  Initialize GC9A01A chip. Connects to the GC9A01A over SPI
            and sends initialization commands.
    @param  freq  Desired SPI clock frequency
*/
void begin(uint32_t freq) {


  if (1) {                 // If no hardware reset pin...
    sendCommand(GC9A01A_SWRESET,0,0); // Engage software reset
    HAL_Delay(150);
  }

  uint8_t cmd, x, numArgs;
  uint16_t addr = 0;
  while ((cmd = initcmd[addr++]) > 0) {
    x = initcmd[addr++];
    numArgs = x & 0x7F;
    sendCommand(cmd, &initcmd[addr], numArgs);
    addr += numArgs;
    if (x & 0x80)
    	HAL_Delay(150);
  }

  _width = GC9A01A_TFTWIDTH;
 _height = GC9A01A_TFTHEIGHT;
}

/*!
    @brief  Set origin of (0,0) and orientation of TFT display
    @param  m  The index for rotation, from 0-3 inclusive
*/
void setRotation(uint8_t m) {
  uint8_t rotation = m % 4; // can't be higher than 3
  switch (rotation) {
  case 0:
    m = (MADCTL_MX | MADCTL_BGR);
    _width = GC9A01A_TFTWIDTH;
    _height = GC9A01A_TFTHEIGHT;
    break;
  case 1:
    m = (MADCTL_MV | MADCTL_BGR);
    _width = GC9A01A_TFTHEIGHT;
    _height = GC9A01A_TFTWIDTH;
    break;
  case 2:
    m = (MADCTL_MY | MADCTL_BGR);
    _width = GC9A01A_TFTWIDTH;
    _height = GC9A01A_TFTHEIGHT;
    break;
  case 3:
    m = (MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
    _width = GC9A01A_TFTHEIGHT;
    _height = GC9A01A_TFTWIDTH;
    break;
  }

  sendCommand(GC9A01A_MADCTL, &m, 1);
}

/*!
    @brief  Enable/Disable display color inversion
    @param  invert True to invert, False to have normal color
*/
void invertDisplay(bool invert) {
  sendCommand(invert ? GC9A01A_INVON : GC9A01A_INVOFF,0,0);
}

/*!
    @brief  Set the "address window" - the rectangle we will write to RAM
            with the next chunk of SPI data. The GC9A01A will automatically
            wrap the data as each row is filled.
    @param  x1  TFT memory 'x' origin
    @param  y1  TFT memory 'y' origin
    @param  w   Width of rectangle
    @param  h   Height of rectangle
*/
void setAddrWindow(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h) {
  uint16_t x2 = (x1 + w - 1), y2 = (y1 + h - 1);
  writeCommand(GC9A01A_CASET); // Column address set
  SPI_WRITE16(x1);
  SPI_WRITE16(x2);
  writeCommand(GC9A01A_RASET); // Row address set
  SPI_WRITE16(y1);
  SPI_WRITE16(y2);
  writeCommand(GC9A01A_RAMWR); // Write to RAM
}
