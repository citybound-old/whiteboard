#include "minimalWhiteboardContext.h"
#include "whiteboard_renderer.h"
#include <thread>

void processInput (whiteboard* wb) {
    *wb << std::cin;
}

int main () {
    whiteboard wb;

    std::thread inputThread(&processInput, &wb);

    minimalWhiteboardContext(800, 500, &wb);

    inputThread.join();
}
