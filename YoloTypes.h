#pragma once

struct YoloOBB
{
    float x;     // center x
    float y;     // center y
    float w;     // width
    float h;     // height
    float r;     // rotation (radians)
    float conf;  // confidence
    int   cls;   // class id
};
