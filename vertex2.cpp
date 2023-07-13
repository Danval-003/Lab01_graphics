#include "vertex2.h"
#include "framebuffer.h"
#include <cmath>
#include <vector>

Vertex2 centerScreen(static_cast<int>(pantallaAncho/2), static_cast<int>(pantallaAlto/2));

// Función para pintar un punto en la pantalla en las coordenadas especificadas
void point(Vertex2 punto) {
    if (punto.x >= 0 && punto.x < pantallaAncho && punto.y >= 0 && punto.y < pantallaAlto) {
        framebuffer[punto.y][punto.x] = currentColor;
    }
}

void linea(Vertex2 punto1, Vertex2 punto2) {
    int x0 = punto1.x;
    int y0 = punto1.y;
    int x1 = punto2.x;
    int y1 = punto2.y;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        point({x0, y0}); // Dibujar el punto en las coordenadas actuales

        if (x0 == x1 && y0 == y1) {
            break; // Se ha llegado al punto final, se termina el bucle
        }

        int err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void linea(Vertex2 punto1, Vertex2 punto2, int thickness) {
    int x0 = punto1.x;
    int y0 = punto1.y;
    int x1 = punto2.x;
    int y1 = punto2.y;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        for (int i = -thickness / 2; i <= thickness / 2; i++) {
            for (int j = -thickness / 2; j <= thickness / 2; j++) {
                point({x0 + i, y0 + j}); // Dibujar el punto en las coordenadas actuales
            }
        }

        if (x0 == x1 && y0 == y1) {
            break; // Se ha llegado al punto final, se termina el bucle
        }

        int err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}


void square(int height, int wight ,Vertex2 vertexE){
    for(int i = wight; i>0;i--){
        point(vertexE);
        vertexE.x++;
    }
    for(int i = height; i>0;i--){
        point(vertexE);
        vertexE.y++;
    }
    for(int i = wight; i>0;i--){
        point(vertexE);
        vertexE.x--;
    }
    for(int i = height; i>0;i--){
        point(vertexE);
        vertexE.y--;
    }
};

void square(int height, int wight){
    Vertex2 vertexE(centerScreen.x,centerScreen.y);
    for(int i = wight; i>0;i--){
        point(vertexE);
        vertexE.x++;
    }
    for(int i = height; i>0;i--){
        point(vertexE);
        vertexE.y++;
    }
    for(int i = wight; i>0;i--){
        point(vertexE);
        vertexE.x--;
    }
    for(int i = height; i>0;i--){
        point(vertexE);
        vertexE.y--;
    }
};


void drawPoligon(const std::vector<Vertex2>& vec) {
    size_t tamano = vec.size();
    for (size_t i = 0; i < tamano; i++) {
        const Vertex2& vertex = vec[i];
        if(i == tamano-1) {
            const Vertex2 &vertex2 = vec[0];
            linea(vertex, vertex2);
        } else{
            const Vertex2& vertex2 = vec[i+1];
            linea(vertex, vertex2);
        }

    }
}

bool isPointInsidePolygon(const std::vector<Vertex2>& vertices, Vertex2 point) {
    bool inside = false;
    size_t numVertices = vertices.size();

    for (size_t i = 0, j = numVertices - 1; i < numVertices; j = i++) {
        const Vertex2& vertex1 = vertices[i];
        const Vertex2& vertex2 = vertices[j];

        if (((vertex1.y > point.y) != (vertex2.y > point.y)) &&
            (point.x < (vertex2.x - vertex1.x) * (point.y - vertex1.y) / (vertex2.y - vertex1.y) + vertex1.x)) {
            inside = !inside;
        }
    }

    return inside;
}

Vertex2 getRandomPointInsidePolygon(const std::vector<Vertex2>& vertices) {
    int minX = INT_MAX;
    int minY = INT_MAX;
    int maxX = INT_MIN;
    int maxY = INT_MIN;

    // Obtener los límites del polígono
    for (const Vertex2& vertex : vertices) {
        minX = std::min(minX, vertex.x);
        minY = std::min(minY, vertex.y);
        maxX = std::max(maxX, vertex.x);
        maxY = std::max(maxY, vertex.y);
    }

    // Generar puntos aleatorios hasta encontrar uno dentro del polígono
    while (true) {
        int randomX = minX + rand() % (maxX - minX + 1);
        int randomY = minY + rand() % (maxY - minY + 1);
        Vertex2 randomPoint(randomX, randomY);

        if (isPointInsidePolygon(vertices, randomPoint)) {
            return randomPoint;
        }
    }
}

void fillBucket(int x, int y, Color targetColor, Color fillColor) {
    // Obtener el color del punto actual
    Color currentC= framebuffer[y][x];

    // Verificar si el punto actual es diferente al color objetivo
    if (currentC != targetColor) {
        return;
    }

    // Verificar si el punto actual ya está rellenado con el color de relleno
    if (currentC == fillColor) {
        return;
    }

    // Cambiar el color del punto actual al color de relleno
    currentColor = fillColor;
    point(Vertex2(x, y));

    // Rellenar los píxeles vecinos recursivamente o iterativamente
    fillBucket(x + 1, y, targetColor, fillColor); // Derecha
    fillBucket(x - 1, y, targetColor, fillColor); // Izquierda
    fillBucket(x, y + 1, targetColor, fillColor); // Arriba
    fillBucket(x, y - 1, targetColor, fillColor); // Abajo
}

void point(Vertex2 punto, Color fillColor) {
    if (punto.x >= 0 && punto.x < pantallaAncho && punto.y >= 0 && punto.y < pantallaAlto) {
        framebuffer[punto.y][punto.x] = fillColor;
    }
}

void fillBucket(int x, int y, Color targetColor, Color fillColor, Color strokeColor) {
    // Obtener el color del punto actual
    Color currentC= framebuffer[y][x];

    // Verificar si el punto actual es diferente al color objetivo
    if (currentC != targetColor or currentC == strokeColor) {
        return;
    }

    // Verificar si el punto actual ya está rellenado con el color de relleno
    if (currentC == fillColor ) {
        return;
    }

    point(Vertex2(x, y), fillColor);

    // Rellenar los píxeles vecinos recursivamente o iterativamente
    fillBucket(x + 1, y, targetColor, fillColor); // Derecha
    fillBucket(x - 1, y, targetColor, fillColor); // Izquierda
    fillBucket(x, y + 1, targetColor, fillColor); // Arriba
    fillBucket(x, y - 1, targetColor, fillColor); // Abajo
}


void fillPoligon(const std::vector<Vertex2>& vertices, Color fillColor, Color strokeColor, Color backgroundColor) {
    Vertex2 pointInPoligon = getRandomPointInsidePolygon(vertices);
    fillBucket(pointInPoligon.x, pointInPoligon.y, backgroundColor, fillColor, strokeColor);
}





