
 // Часы для 2,4 TFT на красной шилде или 9325 или 9341 и UNO 
 // с температурой из DS3231

#include <Adafruit_GFX.h>
//#include <FreeDefaultFonts.h>
#include <MCUFRIEND_kbv.h> 
#include "TouchScreen.h"

//#include <Fonts/FreeMonoBoldOblique24pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
 
#include "Wire.h"
#include "RTClib.h"

RTC_DS3231 rtc;
//RTC_DS1307 rtc;
MCUFRIEND_kbv tft; 

// *** Define Touchscreen Pin
#define YP A2
#define XM A3
#define YM 8
#define XP 9

// *** Define Value of Touchscreen input
#define TS_MINX 125
#define TS_MINY 85
#define TS_MAXX 965
#define TS_MAXY 905

// *** Define Pin of LCD used
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// *** Define Name of Color
#define BLACK           0x0000      //   0,   0,   0 
#define NAVY            0x000F      //  0,   0, 128 
#define DARKGREEN       0x03E0      //   0, 128,   0 
#define DARKCYAN        0x03EF      //   0, 128, 128 
#define MAROON          0x7800      // 128,   0,   0 
#define PURPLE          0x780F      // 128,   0, 128 
#define OLIVE           0x7BE0      // 128, 128,   0 
#define LIGHTGREY       0xC618      // 192, 192, 192 
#define DARKGREY        0x7BEF      // 128, 128, 128 
#define BLUE            0x001F      //   0,   0, 255 
#define GREEN           0x07E0      //   0, 255,   0 
#define CYAN            0x07FF      //   0, 255, 255 
#define RED             0xF800      // 255,   0,   0 
#define MAGENTA         0xF81F      // 255,   0, 255 
#define YELLOW          0xFFE0      // 255, 255,   0 
#define WHITE           0xFFFF      // 255, 255, 255 
#define ORANGE          0xFD20      // 255, 165,   0 
#define GREENYELLOW     0xAFE5      // 173, 255,  47 
#define PINK            0xF81F
#define DARKDARKGREEN   0x01A0

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// ARRAY TO REPLACE SINGLE DIGITS WITH LEADING ZEROES
char leadingZero[10][4] = {"00", "01", "02", "03", "04", "05", "06", "07", "08", "09"};
char daysOfTheWeek[7][12] = {"Sunday   ", "Monday   ", "Tuesday  ", "Wednesday", "Thursday ", "Friday   ", "Saturday "};
char monthOfTheYear[12][12] = {"December ", "January  ", "February ", "Marth    ", "April    ", "May      ", "June     ", "July     ", "August   ", "September", "October  ", "November "};

const int TS_LEFT=907,TS_RT=136,TS_TOP=942,TS_BOT=139;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
 
TSPoint tp;

void setup() {
 
  Serial.begin(9600);
  rtc.begin();
     if (! rtc.begin()) {
     Serial.println("Couldn't find RTC");
     while (1);
   }
 //  if (rtc.lostPower()) {
 //   Serial.println("RTC is NOT running!");
 //   }
    // following line sets the RTC to the date & time this sketch was compiled
 //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
//  rtc.adjust(DateTime(2020, 7, 5, 18, 8, 20));
 
  tft.reset(); 
 // tft.begin(0x1289);  //Or replace it with 0x9341, 0x9328 etc..
// tft.begin(0x9325);
  tft.begin(0x9341);
  tft.setRotation(3); // 
  tft.fillScreen(BLACK); 

  }
 
  void loop(){
   
   DateTime now = rtc.now();
               
    tft.setFont(&FreeSans24pt7b);
    tft.setTextColor (GREEN, BLACK);
  //  tft.setTextColor (GREEN);
    tft.setTextSize (2);
  
       if (now.hour() > 0 && now.hour() < 10) {
          tft.setCursor(57, 155); 
        if (now.minute() ==  0 && now.second() == 0) tft.fillRect(0, 85, 110, 80, BLACK);      
          tft.print(now.hour());
  }
        else {
          tft.setCursor(0, 155);
         if (now.minute() ==  0 && now.second() == 0) tft.fillRect(0, 85, 110, 80, BLACK); 
          tft.print(now.hour());
        }   
        if (now.hour() == 0  &&  now.minute() ==  0 && now.second() == 0) {
             tft.setCursor(0, 155);
             tft.fillRect(0, 85, 110, 80, BLACK); 
             tft.fillRect(50, 2, 20, 20, BLACK); 
             tft.print(leadingZero[now.hour()]);  
        }
      
  // INSERTS THE FIRST DIVIDING COLON
  tft.setCursor(115, 150);
  tft.print(":");

  // MOVES THE CURSOR AND DRAWS THE MINUTES, LEADING ZERO, ETC
  tft.setCursor(155, 155);  
  if (now.minute() >= 0 && now.minute() < 10){
      if (now.second() ==  0) {
    tft.fillRect(155, 85, 100, 80, BLACK);}    
    tft.print(leadingZero[now.minute()]);
    
  }
  else {   
    if (now.second() ==  0) {      
   tft.fillRect(155, 85, 100, 80, BLACK);
  // delay(1000);
        } 
    tft.print(now.minute()); 
   //     delay(1000);  
    }
 
   tft.setFont(NULL);
   tft.setTextSize (3);
   tft.setTextColor (YELLOW, BLACK);
   
  // MOVES THE CURSOR AND DRAWS THE SECONDS, LEADING ZERO, ETC  
   tft.setCursor(280, 135);  
 if (now.second() >= 0 && now.second() <10){
    tft.print(leadingZero[now.second()]);
  }
  else{
   tft.print(now.second());
 }
  tft.setCursor(0, 1);
  tft.setTextSize (2);
  tft.setTextColor (MAGENTA, BLACK); 
    tft.setCursor(30, 2);
    tft.print(now.day());
      
  tft.setCursor(110, 2);
  tft.print(monthOfTheYear[now.month()]);
  tft.setCursor(240, 2);
  tft.print(now.year());
   
     tft.setCursor(100, 40);
     tft.setTextSize (3);
     tft.setTextColor (CYAN, BLACK);
     tft.print(daysOfTheWeek[now.dayOfTheWeek()]);
      
 //   tft.setTextSize (2);
 //    tft.setCursor(0, 180);    
 //    tft.setTextColor (RED, BLACK);
 //    tft.print("Temperature");
  
 //  tft.setTextSize (5);     
 //    tft.setCursor(35, 200);    
 //    tft.setTextColor (RED, BLACK);
  //   tft.print(rtc.getTemperature()-2);

 tp = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
  // adjusting the minutes -----------------------------------------
  if (tp.x > 500 && tp.y < 500) {
      int minutes1 = now.minute();
      minutes1++; 
      delay(100);
      if (minutes1 > 59) minutes1 = 0;     
      Serial.println(minutes1, DEC);
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), minutes1, 0));
 }
  // adjusting the hours -------------------------------------------
   if (tp.x < 500 && tp.y < 500) {
      int hour1 = now.hour();
      hour1++; 
      delay(100);
      if (hour1 > 23) hour1 = 0;     
      Serial.println(hour1, DEC);
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), hour1, now.minute(), now.second())); 
      tft.fillRect(0, 85, 110, 80, BLACK);      
 } 
 // adjusting the day ---------------------------------------------------
   if (tp.x > 0 && tp.x < 300 && tp.y > 600) {
      int day1 = now.day();
      day1++; 
      delay(100);
      if (day1 > 31) day1 = 0;     
      Serial.println(day1, DEC);
      rtc.adjust(DateTime(now.year(), now.month(), day1, now.hour(), now.minute(), now.second())); 
      tft.fillRect(0, 20, 60, 60, BLACK);      
  } 
  // adjusting the month ------------------------------------------------
   if (tp.x > 300 && tp.x < 700 && tp.y > 600) {
      int month1 = now.month();
      month1++; 
      delay(100);
      if (month1 > 12) month1 = 0;     
      Serial.println(month1, DEC);
      rtc.adjust(DateTime(now.year(), month1, now.day(), now.hour(), now.minute(), now.second())); 
       
  }
   // adjusting the year ------------------------------------------------
   if (tp.x > 700 && tp.y > 600) {
      int year1 = now.year();
      year1++; 
      delay(200);
      if (year1 > 2040) year1 = 2015;     
      Serial.println(year1, DEC);
      rtc.adjust(DateTime(year1, now.month(), now.day(), now.hour(), now.minute(), now.second())); 
  
   } 
  }
 }    
