//
//  TextureOutput.h
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#ifndef TextureOutput_h
#define TextureOutput_h

#include <stdio.h>
#include "ImageConsumer.h"
#include <OpenGLES/ES3/gl.h>
#include "Size.h"
#include "ImageFramebuffer.h"

namespace gpu {
class TextureOutput: ImageConsumer {
public:
    void setInputFramebuffer(ImageFramebuffer * const framebuffer, const int &index);
    int nextAvailableTextureIndex() const;
    void setInputSize(const Size &size, int index);
    Size maximumOutputSize();
    void endProcessing();
    bool shouldIgnoreUpdatesToThisTarget() const;
    bool enable() const;
    void processFrame(int index);
    
    TextureOutput();
    ~TextureOutput();
    GLuint texture() const;
    void processTexture();
    
private:
    ImageFramebuffer *mFirstInputFramebuffer;
    bool mEnable;
};
}

#endif /* TextureOutput_h */


