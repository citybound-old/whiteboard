#include "minimalWhiteboardContext.h"
#include "whiteboard_renderer.h"
#include <thread>

void processInput (whiteboard_renderer* wb) {
    *wb << std::cin;
}

int main () {
    whiteboard_renderer wb;

    std::thread inputThread(&processInput, &wb);

    minimalWhiteboardContext(500, 500, &wb);

    inputThread.join();
}
