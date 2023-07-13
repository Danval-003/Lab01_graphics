#include "Color.h"
#include <iostream>
#include <vector>
#include "framebuffer.h"
#include "vertex2.h"
using namespace std;

void render() {
    setClearColor(NAVY_BLUE);
    clear();

    setCurrentColor(WHITE);
    std::vector<Vertex2> myVector = {{165, 380}, {185, 360}, {180, 330}, {207, 345}, {233, 330}, {230, 360}, {250, 380}, {220, 385}, {205, 410}, {193, 383}};
    //std::vector<Vertex2> myVector = {{321, 335}, {288, 286}, {339, 251}, {374, 302}};
    //std::vector<Vertex2> myVector = {{377, 249}, {411, 197}, {436, 249}};

    drawPoligon(myVector);
    fillPoligon(myVector, YELLOW);
    renderBuffer();
}

int main() {
    render();
    return 0;
}

