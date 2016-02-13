# SegmentDigit

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
     
```