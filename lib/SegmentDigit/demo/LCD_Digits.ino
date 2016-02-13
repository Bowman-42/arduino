#include <SegmentDigit.h>
#include "U8glib.h"

SegmentDigit segmentDigit(128,64);
U8GLIB_ST7920_128X64_4X u8g(13,11,10);

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void drawCallback(int y, int x, int w, int h, boolean del){
  u8g.setColorIndex(del ? 0 : 1 );
  //if (! del ) {
   u8g.drawBox(y,x,w,h);
  //}
}

void setup() {  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // put your setup code here, to run once:
  segmentDigit.setWidth(8);
  //segmentDigit.setLineWidth(3,true);
  segmentDigit.setGap(5,true);
  
  segmentDigit.setCallback(&drawCallback);
  
#if defined(ARDUINO)
  pinMode(13, OUTPUT);           
  digitalWrite(13, HIGH);  
#endif

}

void draw(int k){
  
  //u8g_prepare();
  segmentDigit.setPosition(5,5);
  segmentDigit.setWidth(12);
  segmentDigit.drawInt(k,0);
  segmentDigit.setWidth(3);
  segmentDigit.setPosition(90,34);
  segmentDigit.drawInt(1357+k,0);
  segmentDigit.setPosition(90,44);
  segmentDigit.drawInt(7654-k,0);
  segmentDigit.setPosition(90,54);
  segmentDigit.drawInt(10009-k,0);
}  

void loop() {
  
  for (int k = 1000; k < 10000 ; k++ ) {
  u8g.firstPage();  
  do {
    

      draw(k);
  } while( u8g.nextPage() );
  // put your main code here, to run repeatedly:
  
    delay(200);
  }
}
