#include <firlus/shape/shape.h>

#include <GL/glew.h>

namespace firlus {
    Shape::Shape(ShapeVerticesInfo &info) {
        glGenBuffers(1, &mVertexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * info.verticesCount, info.vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        mVerticesCount = info.verticesCount;
    }

    Shape::~Shape() {
        glDeleteBuffers(1, &mVertexBuffer);
    }

    void Shape::draw(Shader *shader) {
        shader->use();

        // TODO: bind vertices attributes

        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glDrawArrays(GL_TRIANGLES, 0, mVerticesCount);
    }
}
