#include "firlus/shader/shader.h"

#include <fstream>
#include <sstream>
#include <GL/glew.h>

namespace firlus {
    Shader::Shader(const char *vertexShaderFile, const char *fragmentShaderFile) {
        unsigned vertexShader = createVertexShader(vertexShaderFile);
        unsigned fragmentShader = createFragmentShader(fragmentShaderFile);

        createShaderProgram(vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader() {
        glUseProgram(0);
        glDeleteProgram(mShaderProgram);
    }

    void Shader::use() {
        printf("Using shader %d\n", mShaderProgram);
        glUseProgram(mShaderProgram);
    }

    unsigned Shader::createVertexShader(const char *vertexShaderFile) {
        unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);

        printf("loading vertex shader: %s\n", vertexShaderFile);
        loadAndCompileShader(vertexShader, vertexShaderFile);
        printf("done\n");

        return vertexShader;
    }

    unsigned Shader::createFragmentShader(const char *fragmentShaderFile) {
        unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        printf("loading fragment shader: %s\n", fragmentShaderFile);
        loadAndCompileShader(fragmentShader, fragmentShaderFile);
        printf("done\n");

        return fragmentShader;
    }

    void Shader::createShaderProgram(unsigned vertexShader, unsigned fragmentShader) {
        mShaderProgram = glCreateProgram();

        glAttachShader(mShaderProgram, vertexShader);
        glAttachShader(mShaderProgram, fragmentShader);
        glLinkProgram(mShaderProgram);

        GLint success;
        glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[512] = { 0 };
            glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
            printf("program error: %s\n", infoLog);
            throw success;
        }
    }

    void Shader::loadAndCompileShader(unsigned shader, const char *shaderFile) {
        std::string shaderCode = loadShaderFile(shaderFile);

        const char *code = shaderCode.c_str();
        compileShader(shader, code);
    }

    std::string Shader::loadShaderFile(const char *shaderFile) {
        std::ifstream file;
        file.open(shaderFile);

        std::stringstream fileContent;
        fileContent << file.rdbuf();
        return fileContent.str();
    }

    void Shader::compileShader(unsigned shader, const char *shaderCode) {
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);

        checkShaderError(shader, GL_COMPILE_STATUS);
    }

    void Shader::checkShaderError(unsigned shader, unsigned thingToCheck) {
        const int LOG_SIZE = 512;
        int success;
        char infoLog[LOG_SIZE];
        glGetShaderiv(shader, thingToCheck, &success);
        if (!success) {
            glGetShaderInfoLog(shader, LOG_SIZE, NULL, infoLog);
            printf("Shader error:\n%s\n", infoLog);
            throw "Shader error";
        }
        printf("Shader %d created successfully\n", shader);
    }
}
