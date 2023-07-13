#include "color.h"
#include <iostream>
#include <vector>
#include "framebuffer.h"
#include "vertex2.h"
using namespace std;

void render() {
    setClearColor(NAVY_BLUE);
    clear();

    setCurrentColor(WHITE);
    //std::vector<Vertex2> myVector = {{165, 380}, {185, 360}, {180, 330}, {207, 345}, {233, 330}, {230, 360}, {250, 380}, {220, 385}, {205, 410}, {193, 383}};
    //::vector<Vertex2> myVector = {{321, 335}, {288, 286}, {339, 251}, {374, 302}};
    std::vector<Vertex2> myVector = {{377, 249}, {411, 197}, {436, 249}};
    //std::vector<Vertex2> myVector = {{413, 177}, {448, 159}, {502, 88}, {553, 53}, {535, 36}, {676, 37}, {660, 52},
    //                                 {750, 145}, {761, 179}, {672, 192}, {659, 214}, {615, 214}, {632, 230}, {580, 230},
    //                                 {597, 215}, {552, 214}, {517, 144}, {466, 180}};

    //std::vector<Vertex2> myVector2 = {{682, 175}, {708, 120}, {735, 148}, {739, 170}};
    drawPoligon(myVector);
    fillPoligon(myVector, RED, WHITE, NAVY_BLUE);
    currentColor=WHITE;
    //drawPoligon(myVector2);
    //fillPoligon(myVector2,NAVY_BLUE, WHITE, GREEN );
    renderBuffer();
}

int main() {
    render();
    return 0;
}

