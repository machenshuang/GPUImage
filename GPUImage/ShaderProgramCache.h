//
//  ShaderProgramCache.hpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#ifndef ShaderProgramCache_h
#define ShaderProgramCache_h

#include <stdio.h>
#include "ShaderProgram.h"
#include <string>
#include <map>
namespace gpu {

class ShaderProgramCache {
public:
    ~ShaderProgramCache();
    ShaderProgramCache(const ShaderProgramCache &)=delete;
    ShaderProgramCache & operator = (const ShaderProgramCache &)=delete;
    static ShaderProgramCache & getInstance();
    ShaderProgram * programFor(const std::string &vertexShader, const std::string &fragmentShader);
private:
    ShaderProgramCache();
    std::map<std::string, ShaderProgram *> mShaderProgramCache;
};

}

#endif /* ShaderProgramCache_h */
