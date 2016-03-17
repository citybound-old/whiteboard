#include "minimalWhiteboardContext.h"
#include "whiteboard.h"
#include <thread>

whiteboard wb;

void processInput () {
    wb << std::cin;
}

int main () {
    std::thread inputThread(&processInput);

    minimalWhiteboardContext(800, 400, &wb);

    inputThread.join();
}
