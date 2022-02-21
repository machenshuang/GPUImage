//
//  TextureInput.h
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#ifndef TextureInput_h
#define TextureInput_h

#include <stdio.h>
#include "ImageSource.h"
#include "Size.h"
#include <OpenGLES/ES3/gl.h>

namespace gpu {

class TextureInput: ImageSource {
public:
    TextureInput(const GLuint &newInputTexture, const Size &newTextureSize);
    ~TextureInput();
    void processTexture();
private:
    Size mTextureSize;
};

}

#endif /* TextureInput_h */
