/*
  SegmentDigit
*/
#ifndef SegmentDigit_h
#define SegmentDigit_h

#include "Arduino.h"


class SegmentDigit
{
  public:
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
  private:
    int _screen_width;
    int _screen_height;
    int _segment_width;
    int _segment_height;
    int _y1;
    int _y2;
    int _x1;
    int _x2;
    int _x3;
    int _gap;
    int _line_w;
    boolean _keep_line_w;
    boolean _keep_gap;
    void  (*_drawRectCallback)(int y, int x, int w, int h, boolean del);
    
};

#endif