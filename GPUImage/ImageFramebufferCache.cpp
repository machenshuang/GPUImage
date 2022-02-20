//
//  ImageFramebufferCache.cpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/19.
//

#include "ImageFramebufferCache.h"
#include "ImageFramebuffer.h"

namespace gpu {
ImageFramebufferCache & ImageFramebufferCache::getInstance() {
    static ImageFramebufferCache instance;
    return instance;
}

ImageFramebufferCache::ImageFramebufferCache() {
    
}

ImageFramebufferCache::~ImageFramebufferCache() {
    
}

ImageFramebuffer * ImageFramebufferCache::fetchFramebuffer(const Size &size, const TextureOptions &options, const bool &onlyTexture) {
    ImageFramebuffer *framebufferFromCache = nullptr;
    std::string lookupHash = hash(size, options, onlyTexture);
    int numberOfMatchingTextures = mFramebufferTypeCounts[lookupHash];
    if (numberOfMatchingTextures < 1) {
        framebufferFromCache = new ImageFramebuffer(size, options, onlyTexture);
    } else {
        int currentTextureId = numberOfMatchingTextures - 1;
        while ((framebufferFromCache == nullptr) && (currentTextureId >= 0)) {
            std::string textureHash = lookupHash + "-" + std::to_string(currentTextureId);
            framebufferFromCache = mFramebufferCache[textureHash];
            if (framebufferFromCache != nullptr) {
                mFramebufferCache.erase(textureHash);
            }
            currentTextureId--;
        }
        currentTextureId++;
        mFramebufferTypeCounts[lookupHash] = currentTextureId;
        
        if (framebufferFromCache == nullptr) {
            framebufferFromCache = new ImageFramebuffer(size, options, onlyTexture);
        }
    }
    framebufferFromCache->lock();
    return framebufferFromCache;
}

void ImageFramebufferCache::returnFramebufferToCache(ImageFramebuffer * const framebuffer) {
    framebuffer->clearAllLock();
    Size framebufferSize = framebuffer->size();
    TextureOptions options = framebuffer->options();
    std::string lookupHash = hash(framebufferSize, options, framebuffer->onlyTexture());
    int numberOfMatchingTextures = mFramebufferTypeCounts[lookupHash];
    std::string textureHash = lookupHash + "-" + std::to_string(numberOfMatchingTextures);
    mFramebufferCache[textureHash] = framebuffer;
    mFramebufferTypeCounts[lookupHash] = numberOfMatchingTextures + 1;
}

void ImageFramebufferCache::purgeAllUnassignedFramebuffer() {
    mFramebufferCache.clear();
    mFramebufferTypeCounts.clear();
}

std::string ImageFramebufferCache::hash(const Size &size, const TextureOptions &options, const bool &onlyTexture) {
    if (onlyTexture) {
        return std::to_string(size.width()) + "x" + std::to_string(size.height()) + "-" + std::to_string(options.minFilter) + std::to_string(options.magFilter) + std::to_string(options.wrapS) + std::to_string(options.wrapT) + std::to_string(options.internalFormal) + std::to_string(options.format) + std::to_string(options.type) + "-NOFB";
    } else {
        return std::to_string(size.width()) + "x" + std::to_string(size.height()) + "-" + std::to_string(options.minFilter) + std::to_string(options.magFilter) + std::to_string(options.wrapS) + std::to_string(options.wrapT) + std::to_string(options.internalFormal) + std::to_string(options.format) + std::to_string(options.type);
    }
}

}


