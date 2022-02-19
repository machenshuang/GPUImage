//
//  ShaderProgram.cpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/10.
//

#include "ShaderProgram.h"
using namespace std;

namespace gpu {
ShaderProgram::ShaderProgram(const string &vertexShader, const string &fragmentShader) {
    initialized = false;
    attributes = vector<string>();
    uniforms = vector<string>();
    program = glCreateProgram();
        
    if (compileShader(this->vertexShader, GL_VERTEX_SHADER, vertexShader)) {
        printf("Failed to compile vertex shader");
    }
        
    if (compileShader(this->fragmentShader, GL_FRAGMENT_SHADER, fragmentShader)) {
        printf("Failed to compile fragment shader");
    }
    glAttachShader(program, this->vertexShader);
    glAttachShader(program, this->fragmentShader);
}

ShaderProgram::~ShaderProgram() {
    if (vertexShader) {
        glDeleteShader(vertexShader);
    }
        
    if (fragmentShader) {
        glDeleteShader(fragmentShader);
    }
        
    if (program) {
        glDeleteProgram(program);
    }
}

bool ShaderProgram::compileShader(GLuint &shader, GLenum type, const string &shaderString) {
    GLint status;
    const GLchar *source = shaderString.c_str();
    if (!source) {
        printf("Failed to load shader");
        return false;
    }
        
    shader = glCreateShader(type);
    glCompileShader(shader);
        
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        
    if (status != GL_TRUE) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar *log = (GLchar *)malloc(logLength);
            glGetShaderInfoLog(shader, logLength, &logLength, log);
            //TODO: 这些需要传递给外部
            printf("log: %s", log);
            free(log);
        }
    }
    return status == GL_TRUE;
}

bool ShaderProgram::link() {
    GLint status;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        return false;
    }
        
    if (vertexShader) {
        glDeleteShader(vertexShader);
        vertexShader = 0;
    }
        
    if (fragmentShader) {
        glDeleteShader(fragmentShader);
        fragmentShader = 0;
    }
        
    initialized = true;
    return true;
}

void ShaderProgram::user() {
    glUseProgram(program);
}

void ShaderProgram::validate() {
    GLint logLength;
    glValidateProgram(program);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(program, logLength, &logLength, log);
        printf("log: %s", log);
        free(log);
    }
}
}




