//
//  BasicOperation.cpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#include "BasicOperation.h"
#include "ShaderProgramCache.h"
#include "ImageFramebufferCache.h"

namespace gpu {

BasicOperation::BasicOperation(const std::string &vertexShader, const std::string &fragmentShader) {
    mPreventRendering = false;
    mRed = 0.0;
    mGreen = 0.0;
    mBlue = 0.0;
    mAlpha = 0.0;
    
    mProgram = ShaderProgramCache::getInstance().programFor(vertexShader, fragmentShader);
    if (!mProgram->initialized()) {
        mProgram->initialized();
        if (!mProgram->link()) {
            
        }
    }
    mPositionAttribute = mProgram->attributeIndex("position");
    mTextureCoordinateAttribute = mProgram->attributeIndex("inputTextureCoordinate");
    mInputTextureUniform = mProgram->uniformIndex("inputImageTexture");
    
    mProgram->user();
    
    glEnableVertexAttribArray(mPositionAttribute);
    glEnableVertexAttribArray(mTextureCoordinateAttribute);
}

void BasicOperation::initializeAttributes() {
    mProgram->addAttribute("position");
    mProgram->addAttribute("inputTextureCoordinate");
}

void BasicOperation::setupSize(const Size &size) {}

Size BasicOperation::sizeOfFBO() {
    Size outputSize = maximumOutputSize();
    return outputSize;
}

Size BasicOperation::maximumOutputSize() {
    return Size{.mWidth = 0.0, .mHeight = 0.0};
}

bool BasicOperation::shouldIgnoreUpdatesToThisTarget() const {
    return false;
}

void BasicOperation::processFrame(int index) {}


bool BasicOperation::enable() const {
    return true;
}

void BasicOperation::renderToTexture(const GLfloat *vertices, const GLfloat *textureCoordinates) {
    if (mPreventRendering) {
        mFirstFramebuffer->unlock();
    }
    
    mProgram->user();
    
    mOutputFramebuffer = ImageFramebufferCache::getInstance().fetchFramebuffer(sizeOfFBO(), mOptions, false);
    mOutputFramebuffer->activateFramebuffer();
    if (mUsingNextFrameForImageCapture) {
        mOutputFramebuffer->lock();
    }
    glClearColor(mRed, mGreen, mBlue, mAlpha);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mFirstFramebuffer->texture());
    
    glUniform1i(mInputTextureUniform, 2);
    glVertexAttribPointer(mPositionAttribute, 2, GL_FLOAT, 0, 0, vertices);
    glVertexAttribPointer(mTextureCoordinateAttribute, 2, GL_FLOAT, 0, 0, textureCoordinates);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    mFirstFramebuffer->unlock();
}

void BasicOperation::informTargets() {
    for (auto currentTarget: mTargets) {
        std::vector<ImageConsumer *>::iterator ite = std::find(mTargets.begin(), mTargets.end(), currentTarget);
        long index = std::distance(std::begin(mTargets), ite);
        setInputFramebufferForTarget(currentTarget, (int)index);
        currentTarget->setInputSize(outputFrameSize(), (int)index);
    }
    framebufferForOutput()->unlock();
    removeOutputFramebuffer();
    for (auto currentTarget: mTargets) {
        std::vector<ImageConsumer *>::iterator ite = std::find(mTargets.begin(), mTargets.end(), currentTarget);
        long index = std::distance(std::begin(mTargets), ite);
        currentTarget->newFrameReadyAtIndex((int)index);
    }
}

Size BasicOperation::outputFrameSize() {
    return mInputTextureSize;
}

void BasicOperation::setBackgroundColor(const GLfloat &red, const GLfloat &green, const GLfloat &blue, const GLfloat &alpha) {
    mRed = red;
    mGreen = green;
    mBlue = blue;
    mAlpha = alpha;
}

void BasicOperation::setUniform(const GLint &value, const std::string &name) {
    
}

void BasicOperation::setUniform(const GLfloat &value, const std::string &name) {
    
}

void BasicOperation::newFrameReadyAtIndex(int index) {
    static const GLfloat imageVertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f,  1.0f,
        1.0f,  1.0f,
    };
    renderToTexture(imageVertices, textureCoordinates());
    informTargets();
}

int BasicOperation::nextAvailableTextureIndex() {
    return 0;
}

void BasicOperation::setInputFramebuffer(ImageFramebuffer *const framebuffer, const int &index) {
    mFirstFramebuffer = framebuffer;
    mFirstFramebuffer->lock();
}

void BasicOperation::setInputSize(const Size &size, int index) {
    if (mPreventRendering) {
        return;
    }
    mInputTextureSize = size;
    setupSize(sizeOfFBO());
}

void BasicOperation::endProcessing() {}

const GLfloat * BasicOperation::textureCoordinates() {
    static const GLfloat noRotationTextureCoordinates[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    return noRotationTextureCoordinates;
}

}
