/*
  SegmentDigit
*/

#include "Arduino.h"
#include "SegmentDigit.h"

#define SEGMENTS   7
/*
* Define which segment to display for the digits 0-9
*
*
* The segments:
* 0 => top
* 1 => left top
* 2 => right top
* 3 => middle
* 4 => left bottom
* 5 => right bottom
* 6 => bottom 
*/
const boolean digits[][SEGMENTS] = {
  {false, false, false, true, false , false, false},
  {true, true, false, true, true , false, true},
  { false, true, false, false, false, true, false},
  {false, true, false, false, true, false, false},
  {true, false, false, false,true, false,true},
  {false, false, true, false, true, false, false},
  {true, false, true, false, false, false, false},
  {false, true, false, true, true, false, true},
  {false,false,false,false,false,false,false},
  {false,false,false,false,true,false,true}
};

/*
*  Construct
*/
SegmentDigit::SegmentDigit(int screenwidth, int screenheight){
  _screen_width = screenwidth;
  _screen_height = screenheight;
  _y1 = 8;
  _x1 = 8;
}
SegmentDigit::SegmentDigit(int screenwidth, int screenheight, int width){
  _screen_width = screenwidth;
  _screen_height = screenheight;
  _y1 = 8;
  _x1 = 8;
  setWidth(width);
}

/*
*  RegisterCallback, to be implemented for the hardware, has to draw a filled rect. 
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
*/
void SegmentDigit::setCallback( void  (*drawRectCallback)(int y, int x, int w, int h, boolean del)){
	_drawRectCallback = drawRectCallback;
}

void SegmentDigit::setPosition(int y, int x){
	_y1 = y;
	_x1 = x;
	setWidth(_segment_width);
}
void SegmentDigit::setWidth(int width){
  _segment_width = width;
  _line_w =  _keep_line_w ? _line_w : _segment_width / 6;
  if (_line_w < 1 ){
  	_line_w=1;
  }
  _gap =  _keep_gap ? _gap : (_screen_width -  4 * (_segment_width+_line_w) - 2*_y1) / 3;
    
    _segment_height=_segment_width+_segment_width/3;
    _y2 = _y1+_segment_width; 
    _x2 = _x1+_segment_height;
    _x3 = _x2+_segment_height;
  
}

void SegmentDigit::setLineWidth(int width, boolean keep){
	_line_w = width;
	_keep_line_w = keep;
}
void SegmentDigit::setGap(int gap, boolean keep){
	_gap = gap;
	_keep_gap = keep;
}
void SegmentDigit::drawInt(int val, int row){
  int mdigits[4] = {0,0,0,0};
  if ( val >= 10000 ) {
    return;
  }
  int x = 3;
  while (val && x >= 0){
    mdigits[x]= val % 10;
    val  = ( val - mdigits[x] ) / 10;
    x--;
  }
  for (int i = 0; i<4; i++ ) {
    drawDigit(mdigits[i], row, i);
  }
}



void SegmentDigit::drawDigit(int digit, int row, int offset ) {
  for (int i = 0; i < 7 ; i++ ){
    drawSegment( i, row, offset, digits[digit][i]);
    //delay(10);
  }
}

void SegmentDigit::deleteAll(int row){
	for (int i=0; i < 4 ; i++){
		for (int j=0; j<7; j++){
			drawSegment(j,row,i,true);
		}
	}
}

void SegmentDigit::drawSegment( int idx, int row, int offset, boolean del){
  int rect[4];
  int dx1 = _x1;
  int dx2 = _x2;
  int dx3 = _x3;
  if (row == 1 ){
    dx1+=dx3+2*_gap;
    dx2 = dx1+_segment_height;
    dx3 = dx2+_segment_height;
  }
  int dy1 = offset == 0 ? _y1 : ( offset * (_segment_width + _line_w)) +  (offset * _gap ) +_y1;
  int dy2 = offset == 0 ? _y2+_line_w : dy1+_segment_width + _line_w;
  if (idx == 0 ) {
  	rect[0] = dy1-_line_w; 
  	rect[1] = dx1;
  	rect[2] = dy2-dy1+_line_w;
  	rect[3] =_line_w ;
  }else if (idx == 1 ) {
  	rect[0] = dy1-_line_w; 
  	rect[1] = del ? dx1+_line_w : dx1;
  	rect[2] =_line_w ;
  	rect[3] = dx2-dx1;
  }else if (idx == 2 ) {
  	rect[0] = dy2-_line_w; 
  	rect[1] = del ? dx1+_line_w : dx1 ;
  	rect[2] = _line_w;
  	rect[3] = dx2-dx1;
  }else if (idx == 3 ) {
  	rect[0] = dy1; 
  	rect[1] = dx2;
  	rect[2] =dy2-dy1 ;
  	rect[3] = _line_w;
  }else if (idx == 4 ) {
  	rect[0] = dy1-_line_w; 
  	rect[1] = dx2;
  	rect[2] = _line_w;
  	rect[3] = dx3-dx2+_line_w;
  }else if (idx == 5 ) {
  	rect[0] = dy2-_line_w; 
  	rect[1] = dx2;
  	rect[2] = _line_w;
  	rect[3] = dx3-dx2+_line_w;
  }else if (idx == 6 ) {
  	rect[0] = dy1-_line_w; 
  	rect[1] = dx3 ;
  	rect[2] =dy2-dy1 ;
  	rect[3] = _line_w;
  
  }
  
  _drawRectCallback(rect[0] ,rect[1], rect[2], rect[3], del );
}