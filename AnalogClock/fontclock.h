const uint8_t fontclockBitmaps[] PROGMEM =
{
  0x4F, 0x85, 0x3A, 0x4E, 0xE0, 0x59, 0x2E, 0xF1, 0xF8, 0xF0, 0xF1, 0x71, 
  0xF0, 0x99, 0xF1, 0x10, 0xF8, 0xF1, 0xF0, 0xFC, 0x3F, 0x1F, 0x80, 0xF1, 
  0x22, 0x20, 0x3C, 0x93, 0xC9, 0x3C, 0x7A, 0x5E, 0x17, 0x80, 0x13, 0x99, 
  0x44, 0xA2, 0x53, 0xB8, 0x22, 0x66, 0x22, 0x22, 0x77
};

const GFXglyph fontclockGlyphs[] PROGMEM =
{
  { 0, 7, 5, 0, -2, 0 },  // 0x30 '0'
  { 5, 3, 5, 0, -3, 0 },  // 0x31 '1'
  { 7, 4, 5, 0, -5, 0 },  // 0x32 '2'
  { 10, 4, 5, 0, -3, -1 },  // 0x33 '3'
  { 13, 4, 5, 0, -5, -2 },  // 0x34 '4'
  { 16, 4, 5, 0, -3, -3 },  // 0x35 '5'
  { 19, 5, 5, 0, -2, -4 },  // 0x36 '6'
  { 23, 4, 5, 0, 0, -3 },  // 0x37 '7'
  { 26, 6, 5, 0, 0, -2 },  // 0x38 '8'
  { 30, 5, 5, 0, 0, -1 },  // 0x39 '9'
  { 34, 9, 5, 0, 0, 0 },  // 0x3A ':'
  { 40, 8, 5, 0, 0, 0 }  // 0x3B ';'
};

const GFXfont fontclock PROGMEM =
{
  (uint8_t*) fontclockBitmaps,
  (GFXglyph*) fontclockGlyphs,
  0x30, 0x3B, 6
};

// Approx. 45 bytes
