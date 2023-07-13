#include <vector>
#include "color.h"

// Estructura Vertex2 para almacenar coordenadas X e Y
struct Vertex2 {
    int x;
    int y;
    Vertex2(): x(0), y(0) {};
    Vertex2(int x, int y): x(x), y(y) {};
};

void point(Vertex2 punto);  // Declaración de la función punto()

extern Vertex2 centerScreen;

void linea(Vertex2 punto1, Vertex2 punto2);

void linea(Vertex2 punto1, Vertex2 punto2, int thickness);

void square(int height, int wight ,Vertex2 vertexE);

void square(int height, int wight);

void drawPoligon(const std::vector<Vertex2>& vec);

void fillPoligon(const std::vector<Vertex2>& vertices, Color fillColor);
