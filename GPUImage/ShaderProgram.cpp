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
    mInitialized = false;
    mAttributes = vector<string>();
    mUniforms = vector<string>();
    mProgram = glCreateProgram();
        
    if (compileShader(this->mVertexShader, GL_VERTEX_SHADER, vertexShader)) {
        printf("Failed to compile vertex shader");
    }
        
    if (compileShader(this->mFragmentShader, GL_FRAGMENT_SHADER, fragmentShader)) {
        printf("Failed to compile fragment shader");
    }
    glAttachShader(mProgram, this->mVertexShader);
    glAttachShader(mProgram, this->mFragmentShader);
}

ShaderProgram::~ShaderProgram() {
    if (mVertexShader) {
        glDeleteShader(mVertexShader);
    }
        
    if (mFragmentShader) {
        glDeleteShader(mFragmentShader);
    }
        
    if (mProgram) {
        glDeleteProgram(mProgram);
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
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        return false;
    }
        
    if (mVertexShader) {
        glDeleteShader(mVertexShader);
        mVertexShader = 0;
    }
        
    if (mFragmentShader) {
        glDeleteShader(mFragmentShader);
        mFragmentShader = 0;
    }
        
    mInitialized = true;
    return true;
}

void ShaderProgram::user() {
    glUseProgram(mProgram);
}

void ShaderProgram::validate() {
    GLint logLength;
    glValidateProgram(mProgram);
    glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(mProgram, logLength, &logLength, log);
        printf("log: %s", log);
        free(log);
    }
}

bool ShaderProgram::initialized() {
    return mInitialized;
}

void ShaderProgram::addAttribute(const string &attributeName) {
    long count = std::count(mAttributes.begin(), mAttributes.end(), attributeName);
    if (count <= 0) {
        mAttributes.push_back(attributeName);
        glBindAttribLocation(mProgram, (GLuint)mAttributes.size(), attributeName.c_str());
    }
}


GLuint ShaderProgram::attributeIndex(const string &attributeName) {
    std::vector<std::string>::iterator ite = std::find(mAttributes.begin(), mAttributes.end(), attributeName);
    long index = std::distance(std::begin(mAttributes), ite);
    return (GLuint)index;
}

GLuint ShaderProgram::uniformIndex(const string &uniformName) {
    std::vector<std::string>::iterator ite = std::find(mUniforms.begin(), mUniforms.end(), uniformName);
    long index = std::distance(std::begin(mUniforms), ite);
    return (GLuint)index;
}



}
