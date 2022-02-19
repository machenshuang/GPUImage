//
//  ImageFramebuffer.cpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/19.
//

#include "ImageFramebuffer.h"
#include "ImageFramebufferCache.h"

namespace gpu {

ImageFramebuffer::ImageFramebuffer(const Size &size,
                                   const TextureOptions &options,
                                   const bool &onlyTexture): mSize(size), mOptions(options), mOnlyTexture(onlyTexture) {
    mReferenceCount = 0;
    if (mOnlyTexture) {
        generateTexture();
    } else {
        generateFramebuffer();
    }
}

ImageFramebuffer::~ImageFramebuffer() {
    destroyFramebuffer();
}

void ImageFramebuffer::generateTexture() {
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mOptions.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mOptions.magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mOptions.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mOptions.wrapT);
}

void ImageFramebuffer::generateFramebuffer() {
    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    generateTexture();
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, mOptions.internalFormal, (int)mSize.width(), (int)mSize.height(), 0, mOptions.format, mOptions.type, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ImageFramebuffer::destroyFramebuffer() {
    if (mFramebuffer) {
        glDeleteFramebuffers(1, &mFramebuffer);
        mFramebuffer = 0;
    }
    
    if (mTexture) {
        glDeleteTextures(1, &mTexture);
        mTexture = 0;
    }
}

void ImageFramebuffer::activateFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    glViewport(0, 0, (int)mSize.width(), (int)mSize.height());
}

void ImageFramebuffer::lock() {
    mReferenceCount++;
}

void ImageFramebuffer::unlock() {
    mReferenceCount--;
    if (mReferenceCount < 1) {
        ImageFramebufferCache &cache = ImageFramebufferCache::getInstance();
        cache.returnFramebufferToCache(this);
    }
}

GLuint ImageFramebuffer::texture() {
    return mTexture;
}

Size ImageFramebuffer::size() {
    return mSize;
}

void ImageFramebuffer::clearAllLock() {
    mReferenceCount = 0;
}

}
