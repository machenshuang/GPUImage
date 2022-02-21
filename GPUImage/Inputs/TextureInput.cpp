//
//  TextureInput.cpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#include "TextureInput.h"

namespace gpu {

TextureInput::TextureInput(const GLuint &newInputTexture, const Size &newTextureSize): mTextureSize(newTextureSize) {
    mOutputFramebuffer = new ImageFramebuffer(newTextureSize, newInputTexture);
}

TextureInput::~TextureInput() {
    delete mOutputFramebuffer;
}

void TextureInput::processTexture() {
    for (auto currentTarget : mTargets) {
        std::vector<ImageConsumer *>::iterator ite = std::find(mTargets.begin(), mTargets.end(), currentTarget);
        long index = std::distance(std::begin(mTargets), ite);
        currentTarget->setInputSize(mTextureSize, (int)index);
        currentTarget->setInputFramebuffer(mOutputFramebuffer, (int)index);
        currentTarget->processFrame((int)index);
    }
}

}
