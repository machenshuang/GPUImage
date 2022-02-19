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

namespace gpu {

class ImageFramebufferCache {
public:
    ~ImageFramebufferCache();
    ImageFramebufferCache(const ImageFramebufferCache &)=delete;
    ImageFramebufferCache & operator = (const ImageFramebufferCache &)=delete;
    static ImageFramebufferCache & getInstance();
    ImageFramebuffer* fetchFramebuffer(const Size &size, const TextureOptions &option);
    void purgeAllUnassignedFramebuffer();
    void returnFramebufferToCache(ImageFramebuffer *framebuffer);
    void addFramebuffer(ImageFramebuffer *framebuffer);
    void removeFramebuffer(ImageFramebuffer *framebuffer);
private:
    ImageFramebufferCache();
    
};

}

#endif /* ImageFramebufferCache_h */
