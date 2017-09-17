#pragma once

#include <string>

namespace firlus {
    class Shader {
    public:
        Shader(const char *vertexShaderFile, const char *fragmentShaderFile);
        virtual ~Shader();

        void use();

        unsigned shaderProgram() { return mShaderProgram; } // TODO: temporary

    private:
        unsigned createVertexShader(const char *vertexShaderFile);
        unsigned createFragmentShader(const char *fragmentShaderFile);
        void createShaderProgram(unsigned vertexShader, unsigned fragmentShader);

        void loadAndCompileShader(unsigned shader, const char *shaderFile);
        std::string loadShaderFile(const char *shaderFile);
        void compileShader(unsigned shader, const char *shaderCode);

        void checkShaderError(unsigned shader, unsigned thingToCheck);

    private:
        unsigned mShaderProgram;
    };
}
