# SegmentDigit

Drawing 4 digits on (hopefully) every screen using xy coordinates. 

## Callback
A callback is essential, it has to be implemented for the hardware and has to draw a filled rect. 
### examples:
- u8g:  ( 2 color lcd )
```c++
void drawCallback(int y, int x, int w, int h, boolean del){
  u8g.setColorIndex(del ? 0 : 1 );
  u8g.drawBox(y,x,w,h);
}
```
- 
Adafruit_TFTLCD ( 16bit color tft )
```c++
void drawCallback(int y, int x, int w, int h, boolean del){
  int color = del ? bg_color : char_color;
  tft.fillRect(y, x, w, h, color);
}
```

### Synopsis:

```c++

    SegmentDigit(int screenwidth, int screenheight);
    SegmentDigit(int screenwidth, int screenheight, int width);
    void setPosition(int y, int x);
    void setWidth(int width);
    void setGap(int gap, boolean keep);
    void setLineWidth(int width, boolean keep);
     void drawSegment(int idx, int row, int offset, boolean del);
     void drawInt(int val, int row);
     void drawDigit(int digit, int row, int offset );
     void deleteAll(int row);
     
     
     void setCallback( void  (*drawRectCallback)(int y, int x, int w, int h, boolean del));
/*
*  Callback, to be implemented for the hardware, has to draw a filled rect. 
* 
* ex: 
* u8g:  ( 2 color lcd )
void drawCallback(int y, int x, int w, int h, boolean del){
  u8g.setColorIndex(del ? 0 : 1 );
  u8g.drawBox(y,x,w,h);
}

* Adafruit_TFTLCD ( 16bit color tft )
void drawCallback(int y, int x, int w, int h, boolean del){
  int color = del ? bg_color : char_color;
  tft.fillRect(y, x, w, h, color);
}


SegmentDigit segmentDigit(screen_w, screen_h);
and in setup
  
  segmentDigit.setCallback(&drawCallback);
*/
```