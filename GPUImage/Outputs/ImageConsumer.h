//
//  ImageConsumer.h
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#ifndef ImageConsumer_h
#define ImageConsumer_h

#include <stdio.h>
#include "ImageFramebuffer.h"
#include "Size.h"

namespace gpu {

class ImageConsumer {
public:
    virtual void newFrameReadyAtIndex(int index) = 0;
    virtual void setInputFramebuffer(ImageFramebuffer * const framebuffer, const int &index) = 0;
    virtual int nextAvailableTextureIndex() const = 0;
    virtual void setInputSize(const Size &size, int index) = 0;
    virtual Size maximumOutputSize() = 0;
    virtual void endProcessing() = 0;
    virtual bool shouldIgnoreUpdatesToThisTarget() const = 0;
    virtual bool enable() const = 0;
    virtual void processFrame(int index) = 0;
};

}

#endif /* ImageSource_h */
