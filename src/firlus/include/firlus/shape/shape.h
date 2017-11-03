#pragma once

#include <firlus/shader/shader.h>

namespace firlus {

    struct Vertex {
        float x, y, z;
        // TODO: texCoords, normals
    };

    struct ShapeVerticesInfo {
        Vertex *vertices;
        unsigned verticesCount;

        // TODO:
        // unsigned *indices;
        // unsigned indicesCount;
    };

    class Shape {
    public:
        Shape(ShapeVerticesInfo &info);
        ~Shape();

        void draw(Shader *shader);

    private:
        unsigned mVertexBuffer;
        unsigned mVerticesCount;
    };
}
