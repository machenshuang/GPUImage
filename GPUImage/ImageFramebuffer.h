//
//  ImageFramebuffer.hpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/19.
//

#ifndef ImageFramebuffer_h
#define ImageFramebuffer_h

#include <stdio.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include "Size.h"

namespace gpu {

struct TextureOptions {
    GLenum minFilter;
    GLenum magFilter;
    GLenum wrapS;
    GLenum wrapT;
    GLenum internalFormal;
    GLenum format;
    GLenum type;
};

class ImageFramebuffer {
public:
    ImageFramebuffer(const Size &size, const TextureOptions &options, const bool &onlyTexture);
    ImageFramebuffer(const Size &size, const GLuint &overriddenTexture);
    ~ImageFramebuffer();
    void activateFramebuffer();
    void lock();
    void unlock();
    void clearAllLock();
    
    Size size() const;
    GLuint texture() const;
    TextureOptions options() const;
    bool onlyTexture() const;
    
private:
    Size mSize;
    TextureOptions mOptions;
    GLuint mTexture;
    GLuint mFramebuffer;
    bool mOnlyTexture;
    unsigned int mReferenceCount;
    
    void generateFramebuffer();
    void generateTexture();
    void destroyFramebuffer();
};

}

#endif /* ImageFramebuffer_h */
