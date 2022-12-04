/* REQUIRES the following Arduino libraries:
// - Lien vidéo: https://youtu.be/FJR3LrY4Vew
// - Diagram: https://youtu.be/l33WRd2h6gM
// - GPxMatrix Library: https://github.com/3tawi/GPxMatrix
// - DS1307ESP Library: https://github.com/3tawi/DS1307ESPTime
// - Adafruit_GFX Library: https://github.com/adafruit/Adafruit-GFX-Library
// - Getting Started ESP32 / ESP32S : https://www.youtube.com/watch?v=9b0Txt-yF7E
// Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects
*/
#include <GPxMatrix.h>
#include <DS1307ESPTime.h>
#include <font/fontclock.h>

DS1307ESPTime rtc;

#define P_A    32
#define P_B    17
#define P_C    33
#define P_D    16
#define P_E    5
#define P_CLK  0 
#define P_LAT  2 
#define P_OE   4

//                          R1, G1, B1, R2, G2, B2  RGB Pins
//uint8_t listrgbpins[6] = {25, 26, 27, 12, 13, 14};
//GPxMatrix matrix(P_A, P_B, P_C, P_D, P_E, P_CLK, P_LAT, P_OE, true, 64, listrgbpins);

GPxMatrix matrix(P_A, P_B, P_C, P_D, P_E, P_CLK, P_LAT, P_OE, true, 64);

#define clear()          matrix.fillScreen(0)
#define show()           matrix.swapBuffers(false)
#define WIDTH 64
#define HEIGHT 64
const byte CENTRE_X = 32;
const byte CENTRE_Y = 32;
int Tz = 1; // Time Zone
uint8_t second;
uint8_t minute;
uint8_t hour;
uint8_t NewRTCm = 60;
int co0, co1;
uint16_t MyColor[92] = { 0xF800, 0xF880, 0xF900, 0xF980, 0xFA20, 0xFAA0, 0xFB20, 0xFBA0, 0xFC40, 0xFCC0, 0xFD40, 0xFDC0,
                         0xFDC0, 0xFE60, 0xFEE0, 0xFF60, 0xFFE0, 0xEFE0, 0xDFE0, 0xCFE0, 0xBFE0, 0xAFE0, 0x9FE0, 0x8FE0,
                         0x77E0, 0x67E0, 0x57E0, 0x47E0, 0x37E0, 0x27E0, 0x17E0, 0x07E0, 0x07E2, 0x07E4, 0x07E6, 0x07E8,
                         0x07EA, 0x07EC, 0x07EE, 0x07F1, 0x07F3, 0x07F5, 0x07F7, 0x07F9, 0x07FB, 0x07FD, 0x07FF, 0x077F,
                         0x06FF, 0x067F, 0x05DF, 0x055F, 0x04DF, 0x045F, 0x03BF, 0x033F, 0x02BF, 0x023F, 0x019F, 0x011F,
                         0x009F, 0x001F, 0x101F, 0x201F, 0x301F, 0x401F, 0x501F, 0x601F, 0x701F, 0x881F, 0x981F, 0xA81F,
                         0xB81F, 0xC81F, 0xD81F, 0xE81F, 0xF81F, 0xF81D, 0xF81B, 0xF819, 0xF817, 0xF815, 0xF813, 0xF811,
                         0xF80E, 0xF80C, 0xF80A, 0xF808, 0xF806, 0xF804, 0xF802, 0xF800 };

void redtime() {
  second = rtc.getSecond();
  minute = rtc.getMinute();
  hour = rtc.getHour();
  co0 = random(0, 91);
  if (NewRTCm != minute) {
    co1 = random(0, 91);
    NewRTCm = minute;
  }
}    
void drawclockNB() {
  float radians, angle;
  int j = 0;
  matrix.setFont(&fontclock);
  for (int i = 0; i < 60; i+=5) {
    matrix.setTextColor(MyColor[(co1+i*5)%92]);
    angle =  180 - i * 6;
    radians = radians(angle);
    int x0 = CENTRE_X + 26 * sin(radians);
    int y0 = CENTRE_Y + 26 * cos(radians);
    matrix.setCursor(x0,y0);
    matrix.print(char(j));
    j++;
    if (j == 10) { j = 11;}
  }
  matrix.setFont();
}
    
void drawclockDot() {
      float radians, angle;
      for (int i = 0; i < 60; i+=5) {
        uint16_t color = MyColor[(co0+i*5)%92];
        angle =  360 - i * 6;
        radians = radians(angle);
        int x0 = CENTRE_X + 30 * sin(radians);
        int y0 = CENTRE_Y + 30 * cos(radians);
        matrix.fillCircle(x0, y0, 1, color);
     }
}
    
void drawclockBDot() {
      float radians, angle;
      matrix.ellipse(CENTRE_X, CENTRE_Y, 30, 30, MyColor[co1]);
      for (int i = 0; i < 60; i+=15) {
        uint16_t color = MyColor[(co1+i*5)%92];
        angle =  360 - i * 6;
        radians = radians(angle);
        int x0 = CENTRE_X + 30 * sin(radians);
        int y0 = CENTRE_Y + 30 * cos(radians);
        matrix.fillCircle(x0, y0, 2, color);
     }
}

void drawHMS(float angle, int x0, int y0, int w, int c0, int c1, int z1) {
      int x[3];
      int y[3];
      float radians = radians(angle);
      x[0] = x0 + w * sin(radians);
      y[0] = y0 + w * cos(radians);
      radians = radians(angle+z1);
      x[1] = x0 + 6 * sin(radians);
      y[1] = y0 + 6 * cos(radians);
      radians = radians(angle-z1);
      x[2] = x0 + 6 * sin(radians);
      y[2] = y0 + 6 * cos(radians);
      matrix.fillTriangle(x0, y0, x[0], y[0], x[1], y[1], MyColor[c0]);
      matrix.fillTriangle(x0, y0, x[0], y[0], x[2], y[2], MyColor[c0]);
      matrix.drawLine(x[0], y[0], x[1], y[1], MyColor[c1]);
      matrix.drawLine(x[0], y[0], x[2], y[2], MyColor[c1]);
}

void drawtime() {
  if (hour > 12) hour -= 12;
  float angle = 180 - (30 * hour) - (minute / 2);
  drawHMS(angle, CENTRE_X, CENTRE_Y, 17, 0, 0, 30);
  angle = 180 - (6 * minute);
  drawHMS(angle, CENTRE_X, CENTRE_Y, 25, 32, 34, 25);
  angle =  180 - (second * 6);
  drawHMS(angle, CENTRE_X, CENTRE_Y, 29, co0, co1, 20);
  matrix.fillCircle(CENTRE_X, CENTRE_Y, 2, MyColor[co1]);
  matrix.fillCircle(CENTRE_X, CENTRE_Y, 1, MyColor[co0]);
}

void updateTime()
{
  rtc.DSgetdatime(); 
  configTime(Tz * 3600, 0, "", "");
} 

void writeTime()
{
  configTime(0, 0, "", ""); 
  rtc.DSsetdatime(); 
  configTime(Tz * 3600, 0, "", "");
}

void setup() { 
  rtc.DSbegin();              
  // rtc.setTime(second, minute, hour, dayOfMonth, month, year);
  //writeTime(); // Print the time in the RTC DS1307
  updateTime();  // Get DS1307 RTC Time
  matrix.begin();
  delay(1000);
}

void loop() {
  clear();
  redtime();
  drawclockBDot();
  drawclockDot();
  drawclockNB();
  drawtime();
  show();
  delay(1000);
}
