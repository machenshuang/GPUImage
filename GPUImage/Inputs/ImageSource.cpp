//
//  ImageSource.cpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#include "ImageSource.h"
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include <algorithm>
namespace gpu {

ImageSource::ImageSource() {
    mEnable = true;
    mOptions = TextureOptions{
        .minFilter = GL_LINEAR,
        .magFilter = GL_LINEAR,
        .wrapS = GL_CLAMP_TO_EDGE,
        .wrapT = GL_CLAMP_TO_EDGE,
        .internalFormal = GL_RGBA,
        .format = GL_BGRA,
        .type = GL_UNSIGNED_BYTE
    };
    mUsingNextFrameForImageCapture = false;
}

ImageSource::~ImageSource() {
    removeAllTargets();
}

void ImageSource::setInputFramebufferForTarget(ImageConsumer * const target, const int &index) {
    target->setInputFramebuffer(mOutputFramebuffer, index);
}

ImageFramebuffer * ImageSource::framebufferForOutput() const {
    return mOutputFramebuffer;
}

void ImageSource::removeOutputFramebuffer() {
    delete mOutputFramebuffer;
    mOutputFramebuffer = nullptr;
}

std::vector<ImageConsumer *> ImageSource::targtes() const {
    return mTargets;
}

void ImageSource::addTarget(ImageConsumer *const target) {
    int nextAvailableTextureIndex = target->nextAvailableTextureIndex();
    addTarget(target, nextAvailableTextureIndex);
}

void ImageSource::addTarget(ImageConsumer *const target, const int &index) {
    long count = std::count(mTargets.begin(), mTargets.end(), target);
    if (count > 0) {
        return;
    }
    setInputFramebufferForTarget(target, index);
    mTargets.push_back(target);
    mTargetTextureIndices.push_back(index);
}

void ImageSource::removeTarget(ImageConsumer * const target) {
    long count = std::count(mTargets.begin(), mTargets.end(), target);
    if (count <= 0) {
        return;
    }
    std::vector<ImageConsumer *>::iterator ite = std::find(mTargets.begin(), mTargets.end(), target);
    long index = std::distance(std::begin(mTargets), ite);
    mTargetTextureIndices.erase(mTargetTextureIndices.begin() + index);
    mTargets.erase(ite);
}

TextureOptions ImageSource::outputOptions() const {
    return mOptions;
}

void ImageSource::removeAllTargets() {
    mTargets.clear();
    mTargetTextureIndices.clear();
}

}
