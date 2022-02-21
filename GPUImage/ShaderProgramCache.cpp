//
//  ShaderProgramCache.cpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#include "ShaderProgramCache.h"

namespace gpu {

ShaderProgramCache::ShaderProgramCache() {}

ShaderProgramCache::~ShaderProgramCache() {
    for (auto program: mShaderProgramCache) {
        delete program.second;
    }
    mShaderProgramCache.clear();
}

ShaderProgramCache & ShaderProgramCache::getInstance() {
    static ShaderProgramCache instance;
    return instance;
}

ShaderProgram * ShaderProgramCache::programFor(const std::string &vertexShader, const std::string &fragmentShader) {
    std::string lookupKeyForShaderProgram = "V:" + vertexShader + "-F:" + fragmentShader;
    ShaderProgram *programFromCache = mShaderProgramCache[lookupKeyForShaderProgram];
    if (programFromCache == nullptr) {
        programFromCache = new ShaderProgram(vertexShader, fragmentShader);
        mShaderProgramCache[lookupKeyForShaderProgram] = programFromCache;
    }
    return programFromCache;
}


}
