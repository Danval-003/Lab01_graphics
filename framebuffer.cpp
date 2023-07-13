#include "framebuffer.h"
#include "vertex2.h"
#include <fstream>

std::array<std::array<Color, pantallaAncho>, pantallaAlto> framebuffer;
Color clearColor(0, 0, 0);
Color currentColor(0, 0, 0);


#include <thread>
#include <vector>

void clear() {
    const unsigned int numThreads = std::thread::hardware_concurrency();

    auto clearPortion = [](unsigned int startY, unsigned int endY) {
        for (unsigned int y = startY; y < endY; y++) {
            auto& row = framebuffer[y];
            for (auto& pixel : row) {
                pixel = clearColor;
            }
        }
    };

    std::vector<std::thread> threads;

    const unsigned int rowsPerThread = pantallaAlto / numThreads;
    unsigned int startY = 0;
    unsigned int endY = rowsPerThread;

    for (unsigned int i = 0; i < numThreads - 1; i++) {
        threads.emplace_back(clearPortion, startY, endY);
        startY = endY;
        endY += rowsPerThread;
    }

    threads.emplace_back(clearPortion, startY, pantallaAlto);

    for (auto& thread : threads) {
        thread.join();
    }
}

void setCurrentColor(Color changeColor) {
    currentColor = changeColor;
}

void setClearColor(Color changeColor) {
    clearColor = changeColor;
}

#pragma pack(push, 1) // Desactivar el alineamiento de bytes

struct BMPHeader {
    uint16_t signature; // "BM" (0x4D42)
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes; // Siempre 1
    uint16_t bitsPerPixel; // 24 bits
    uint32_t compression; // 0 (sin compresión)
    uint32_t imageSize;
    int32_t horizontalResolution; // Píxeles por metro
    int32_t verticalResolution; // Píxeles por metro
    uint32_t numColors; // 0 (todos los colores son importantes)
    uint32_t numImportantColors; // 0 (todos los colores son importantes)
};

#pragma pack(pop) // Restaurar el alineamiento de bytes

void renderBuffer() {
    // Encabezado del archivo BMP
    const int tamanoCabecera = sizeof(BMPHeader);
    const int bitsPorPixel = 24;
    const int tamanoImagen = pantallaAncho * pantallaAlto * (bitsPorPixel / 8);
    const int tamanoArchivo = tamanoCabecera + tamanoImagen;

    // Crear el encabezado BMP
    BMPHeader bmpHeader{};
    bmpHeader.signature = 0x4D42;
    bmpHeader.fileSize = tamanoArchivo;
    bmpHeader.reserved = 0;
    bmpHeader.dataOffset = tamanoCabecera;
    bmpHeader.headerSize = 40;
    bmpHeader.width = pantallaAncho;
    bmpHeader.height = pantallaAlto;
    bmpHeader.planes = 1;
    bmpHeader.bitsPerPixel = bitsPorPixel;
    bmpHeader.compression = 0;
    bmpHeader.imageSize = tamanoImagen;
    bmpHeader.horizontalResolution = 0;
    bmpHeader.verticalResolution = 0;
    bmpHeader.numColors = 0;
    bmpHeader.numImportantColors = 0;

    // Abrir el archivo BMP en modo binario para escritura
    std::ofstream archivoBMP("../out.bmp", std::ios::binary);

    // Escribir el encabezado del archivo BMP
    archivoBMP.write(reinterpret_cast<const char*>(&bmpHeader), tamanoCabecera);

    // Escribir los datos de color del framebuffer en formato BGR
    for (int y = 0; y <pantallaAncho; y++) {
        for (int x = 0; x < pantallaAncho; x++) {
            archivoBMP.write(reinterpret_cast<const char*>(&framebuffer[y][x].blue), 1);
            archivoBMP.write(reinterpret_cast<const char*>(&framebuffer[y][x].green), 1);
            archivoBMP.write(reinterpret_cast<const char*>(&framebuffer[y][x].red), 1);
        }
    }

    // Cerrar el archivo BMP
    archivoBMP.close();
}