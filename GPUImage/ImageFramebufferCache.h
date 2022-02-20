//
//  ImageFramebufferCache.hpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/19.
//

#ifndef ImageFramebufferCache_h
#define ImageFramebufferCache_h

#include <stdio.h>
#include "ImageFramebuffer.h"
#include "Size.h"
#include <string>
#include <map>

namespace gpu {

class ImageFramebufferCache {
public:
    ~ImageFramebufferCache();
    ImageFramebufferCache(const ImageFramebufferCache &)=delete;
    ImageFramebufferCache & operator = (const ImageFramebufferCache &)=delete;
    static ImageFramebufferCache & getInstance();
    
    ImageFramebuffer* fetchFramebuffer(const Size &size, const TextureOptions &options, const bool &onlyTexture);
    void purgeAllUnassignedFramebuffer();
    void returnFramebufferToCache(ImageFramebuffer * const framebuffer);
    
private:
    ImageFramebufferCache();
    std::map<std::string, ImageFramebuffer *> mFramebufferCache;
    std::map<std::string, int> mFramebufferTypeCounts;
    
    std::string hash(const Size &size, const TextureOptions &options, const bool &onlyTexture);
};

}

#endif /* ImageFramebufferCache_h */
