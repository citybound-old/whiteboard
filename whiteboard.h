#ifndef WHITEBOARDDEMO_WHITEBOARD_H
#define WHITEBOARDDEMO_WHITEBOARD_H

#include "nanovg.h"
#include "roboto_regular.h"

void drawLabel(struct NVGcontext* vg, const char* text, float x, float y, float w, float h)
{
    NVG_NOTUSED(w);

    nvgFontSize(vg, 16.0f);
    nvgFontFace(vg, "sans");
    nvgFillColor(vg, nvgRGBA(0,0,0,128) );

    nvgTextAlign(vg,NVG_ALIGN_CENTER|NVG_ALIGN_MIDDLE);
    nvgText(vg, x,y+h*0.5f,text, NULL);
}


class whiteboard {
public:
    void init(NVGcontext* vg) {
        if (nvgCreateFontMem(vg, "sans", Roboto_Regular_ttf, Roboto_Regular_ttf_len, 0) == -1) {
            std::cout << "couldn't load font" << std::endl;
        };
    }

    void draw(NVGcontext* vg, int width, int height) {
        drawLabel(vg, "Whiteboard!", width/2, height/4, 30, 30);
    }
};

#endif //WHITEBOARDDEMO_WHITEBOARD_H
