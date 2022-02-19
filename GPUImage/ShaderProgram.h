//
//  ShaderProgram.h
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/10.
//

#ifndef ShaderProgram_h
#define ShaderProgram_h

#include <stdio.h>
#include <OpenGLES/ES3/gl.h>
#include <string>
#include <vector>

using namespace std;

namespace gpu {
class ShaderProgram {
public:
    ShaderProgram(const string &vertexShader, const string &fragmentShader);
    ~ShaderProgram();
    void addAttribute(const string &attributeName);
    GLuint attributeIndex(const string &attributeName);
    GLuint uniformIndex(const string &uniformName);
    bool link();
    void user();
    void validate();
private:
    vector<string> attributes;
    vector<string> uniforms;
    GLuint program;
    GLuint vertexShader;
    GLuint fragmentShader;
    bool initialized;
    bool compileShader(GLuint &shader, GLenum type, const string &shaderStrinng);
};
}



#endif /* ShaderProgram_h */
