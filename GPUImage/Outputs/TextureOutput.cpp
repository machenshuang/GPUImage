//
//  TextureOutput.cpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#include "TextureOutput.h"

namespace gpu {

TextureOutput::TextureOutput() {
    mEnable = false;
}

TextureOutput::~TextureOutput() {
    
}

void TextureOutput::processTexture() {
    mFirstInputFramebuffer->unlock();
}

GLuint TextureOutput::texture() const {
    return mFirstInputFramebuffer->texture();
}

void TextureOutput::setInputFramebuffer(ImageFramebuffer *const framebuffer, const int &index) {
    mFirstInputFramebuffer = framebuffer;
    mFirstInputFramebuffer->lock();
}

int TextureOutput::nextAvailableTextureIndex() const {
    return 0;
}

void TextureOutput::setInputSize(const Size &size, int index) {
    
}

Size TextureOutput::maximumOutputSize() {
    return Size{.mWidth = 0.0, .mHeight = 0.0};
}

void TextureOutput::endProcessing() {}

bool TextureOutput::shouldIgnoreUpdatesToThisTarget() const {
    return false;
}

bool TextureOutput::enable() const {
    return mEnable;
}

void TextureOutput::processFrame(int index) {
    
}

}
