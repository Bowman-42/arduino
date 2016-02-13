#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <SegmentDigit.h>


#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin



#define  BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

uint16_t char_color = BLACK;
uint16_t bg_color = WHITE;

SegmentDigit segmentDigit(320,240);
void drawCallback(int y, int x, int w, int h, boolean del){
  int color = del ? bg_color : char_color;
  tft.fillRect(y, x, w, h, color);
}

void setup() {
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(bg_color);
  
  segmentDigit.setCallback(&drawCallback);

}


void demo(){
  
  for ( int w = 10; w < 40 ; w += 2 ){
    Serial.println(w);
    if (bg_color==BLACK){
      bg_color=WHITE;
      char_color=BLACK;
    }else{
      char_color = WHITE;
      bg_color = BLACK;
    }
  segmentDigit.setGap(w/2,true);
  tft.fillScreen(bg_color);
  segmentDigit.setWidth(w);
    int y_off = ( w + w/2 -1 ) * 5;
    int x_off = ( w ) * 4;
    for (int k = 1000; k < 1010 ; k++ ) {
      for ( int i = 5; i < 320-y_off; i+=y_off){
        for ( int j = 5; j < 250 - x_off; j+=x_off){
          int d = 7*i+8*j+k;
//            char_color=GREEN;
//          if ( d > 2500) {
//            char_color=RED;
//          }else if ( d > 2000) {
//            char_color=YELLOW;
//          }else if ( d > 1500) {
//            char_color=WHITE;
//          }
          segmentDigit.setPosition(i,j);
          segmentDigit.drawInt(d,0);
        }
      }
      delay(200);
    }
    
  }
}
void loop() {
  demo();


}
