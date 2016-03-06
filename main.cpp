#include "minimalWhiteboardContext.h"
#include "whiteboard.h"
#include <thread>


int main () {
    whiteboard wb;

    minimalWhiteboardContext(800, 400, &wb);
}
