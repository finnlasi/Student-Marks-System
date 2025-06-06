#include "functions.h"

int main() {
    for (int i = 0; i < CLASS_COUNT; ++i)
        loadFromFile(i);

    while (true) {
        int classIndex = selectClass();
        menu(classIndex);
    }
    return 0;
}
