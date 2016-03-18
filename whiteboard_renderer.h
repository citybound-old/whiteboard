#ifndef WHITEBOARDDEMO_WHITEBOARD_H
#define WHITEBOARDDEMO_WHITEBOARD_H

#include "nanovg.h"
#include "roboto_regular.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "./deps/AsQuotedString/AsQuotedString.h"


const std::string whiteboardPrefix = "Whiteboard: ";
const std::string whiteboardSeparator = "Whiteboard: ----";

class whiteboard {
public:
    void init(NVGcontext* vg) {
        if (nvgCreateFontMem(vg, "sans", Roboto_Regular_ttf, Roboto_Regular_ttf_len, 0) == -1) {
            std::cout << "couldn't load font" << std::endl;
        };

        commandBuffers.emplace_back();
    }

    void draw(NVGcontext* vg, int width, int height) {
        nvgFontSize(vg, 16.0f);
        nvgFontFace(vg, "sans");
        nvgFillColor(vg, nvgRGBA(0,0,0,255));
        nvgStrokeColor(vg, nvgRGBA(0,0,0,255));
        nvgTextAlign(vg,NVG_ALIGN_RIGHT|NVG_ALIGN_TOP);

        nvgText(vg, width - 10, 10, (std::to_string(currentBuffer + 1) + "/" + std::to_string(commandBuffers.size())).c_str(), NULL);
        nvgStrokeWidth(vg, 1.0f / height);
        nvgScale(vg, height, height);

        commandBufferMutex.lock();
        std::stringstream tokens(commandBuffers[currentBuffer]);

        nvgTextAlign(vg,NVG_ALIGN_CENTER|NVG_ALIGN_MIDDLE);

        std::string command;

        while (tokens >> command) {
            if (command == "text") {
                float x;
                float y;
                tokens >> x;
                tokens >> y;

                std::string text;
                tokens >> AsQuotedString(text, '"');

                nvgText(vg, x, y, text.c_str(), NULL);
            } else if (command == "color") {
                int r, g, b, a;
                tokens >> r;
                tokens >> g;
                tokens >> b;
                tokens >> a;
                nvgFillColor(vg, nvgRGBA(r, g, b, a));
                nvgStrokeColor(vg, nvgRGBA(r, g, b, a));
            } else if (command == "dot") {
                float x;
                float y;
                tokens >> x;
                tokens >> y;
                nvgBeginPath(vg);
                nvgCircle(vg, x, y, 2);
                nvgFill(vg);
            } else if (command == "line") {
                float x1;
                float y1;
                float x2;
                float y2;
                tokens >> x1;
                tokens >> y1;
                tokens >> x2;
                tokens >> y2;
                nvgBeginPath(vg);
                nvgMoveTo(vg, x1, y1);
                nvgLineTo(vg, x2, y2);
                nvgStroke(vg);
            } else if (command == "arc") {
                float x1;
                float y1;
                float x2;
                float y2;
                float directionX;
                float directionY;

                tokens >> x1;
                tokens >> y1;
                tokens >> directionX;
                tokens >> directionY;
                tokens >> x2;
                tokens >> y2;

                float halfChordX = (x2 - x1) / 2;
                float halfChordY = (y2 - y1) / 2;

                float perpendicularDirectionX = -directionY;
                float perpendicularDirectionY = directionX;

                // three equivalent questions:
                // 1) how many times do you need to go the projection of perpendicularDirection onto the halfChord
                //    to reach the center point of the chord / endpoint of halfChord?
                // 2) how many times do you need to go perpendicularDirection
                //    from (x1, y1) to reach the center of the circle?
                // 3) what is the radius of the circle?
                //
                // we answer 3) with 1):
                //    r = |hC| / proj_hC(pD) = |hC| / ((hC · pD) / |hC|) = |hC|^2 / (hC · pD)
                float halfChordLengthSquared = halfChordX * halfChordX + halfChordY * halfChordY;
                float perpendicularDirectionProjectedOntoHalfChord = (halfChordX * perpendicularDirectionX + halfChordY * perpendicularDirectionY);
                float radius = fabsf(halfChordLengthSquared / perpendicularDirectionProjectedOntoHalfChord);

                // does direction point left or right of chord?
                bool clockwise = directionX * -halfChordY + directionY * halfChordX < 0;

                float centerX = x1 + (clockwise ? 1 : -1) * radius * perpendicularDirectionX;
                float centerY = y1 + (clockwise ? 1 : -1) * radius * perpendicularDirectionY;

                float directionProjectedOntoHalfChord = (halfChordX * directionX + halfChordY * directionY);
                float startAngle = atan2f(directionY, directionX);
                float endDirectionX = -1 * (directionX - 2 * (directionProjectedOntoHalfChord * halfChordX / halfChordLengthSquared));
                float endDirectionY = -1 * (directionY - 2 * (directionProjectedOntoHalfChord * halfChordY / halfChordLengthSquared));
                float endAngle = atan2f(endDirectionY, endDirectionX);

                float startSweepAngle = startAngle + (clockwise ? -1 : 1) * M_PI_2;
                float endSweepAngle = endAngle + (clockwise ? -1 : 1) * M_PI_2;

                nvgBeginPath(vg);
                nvgMoveTo(vg, x1, y1);
                nvgArc(vg, centerX, centerY, radius, startSweepAngle, endSweepAngle, clockwise ? NVG_CW : NVG_CCW);
                nvgStroke(vg);
            }
        }

        commandBufferMutex.unlock();
    }

    void operator << (std::istream& input) {
        std::string line;
        while (std::getline(input, line)) {
            if (std::equal(whiteboardPrefix.begin(), whiteboardPrefix.end(), line.begin())) {
                if (std::equal(whiteboardSeparator.begin(), whiteboardSeparator.end(), line.begin())) {
                    commandBufferMutex.lock();
                    commandBuffers.emplace_back();
                    commandBufferMutex.unlock();
                } else {
                    commandBufferMutex.lock();
                    commandBuffers.back() += line.substr(whiteboardPrefix.length()) + "\n";
                    commandBufferMutex.unlock();
                }
            } else {
                std::cout << line << std::endl;
            }
        }

        if (std::cin.bad()) {
            // IO error
        } else if (!std::cin.eof()) {
            // format error (not possible with getline but possible with operator>>)
        } else {
            // format error (not possible with getline but possible with operator>>)
            // or end of file (can't make the difference)
        }
    }

    void forward () {
        commandBufferMutex.lock();
        currentBuffer = std::min(currentBuffer + 1, commandBuffers.size() - 1);
        commandBufferMutex.unlock();
    }

    void backward () {
        commandBufferMutex.lock();
        currentBuffer = currentBuffer == 0ul ? 0ul : currentBuffer - 1;
        commandBufferMutex.unlock();
    }
private:
    std::vector<std::string> commandBuffers;
    unsigned long currentBuffer = 0;
    std::mutex commandBufferMutex;
};

class drawable {

};

#endif //WHITEBOARDDEMO_WHITEBOARD_H
