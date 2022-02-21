//
//  ImageSource.h
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#ifndef ImageSource_h
#define ImageSource_h

#include <stdio.h>
#include "ImageFramebuffer.h"
#include <vector>
#include "ImageConsumer.h"
#include "Size.h"

namespace gpu {

class ImageSource {
public:
    ImageSource();
    ~ImageSource();
    
    void setInputFramebufferForTarget(ImageConsumer * const target, const int &index);
    ImageFramebuffer * framebufferForOutput() const;
    void removeOutputFramebuffer();
    std::vector<ImageConsumer *> targtes() const;
    void addTarget(ImageConsumer * const target);
    void addTarget(ImageConsumer * const target, const int &index);
    void removeTarget(ImageConsumer * const target);
    void removeAllTargets();
    
    bool mEnable;
    TextureOptions outputOptions() const;
    
    bool mUsingNextFrameForImageCapture;
    
protected:
    Size mInputTextureSize;
    
protected:
    ImageFramebuffer *mOutputFramebuffer;
    std::vector<ImageConsumer *> mTargets;
    std::vector<int> mTargetTextureIndices;
    TextureOptions mOptions;
};

}

#endif /* ImageSource_h */
