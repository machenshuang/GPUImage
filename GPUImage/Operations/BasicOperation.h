//
//  BasicOperation.h
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/20.
//

#ifndef BasicOperation_h
#define BasicOperation_h

#include <stdio.h>
#include "ImageSource.h"
#include "ImageConsumer.h"
#include "ImageFramebuffer.h"
#include <OpenGLES/ES3/gl.h>
#include "ShaderProgram.h"
#include "Size.h"
#include <string>

namespace gpu {
class BasicOperation : ImageSource, ImageConsumer {
public:
    BasicOperation(const std::string &vertexShader, const std::string &fragmentShader);
    void initializeAttributes();
    void setupSize(const Size &size);
    Size sizeOfFBO();
    void renderToTexture(const GLfloat *vertices, const GLfloat *textureCoordinates);
    void informTargets();
    Size outputFrameSize();
    void setBackgroundColor(const GLfloat &red, const GLfloat &green, const GLfloat &blue, const GLfloat &alpha);
    void setUniform(const GLint &value, const std::string &name);
    void setUniform(const GLfloat &value, const std::string &name);
    static const GLfloat *textureCoordinates() ;
    
    void newFrameReadyAtIndex(int index);
    void setInputFramebuffer(ImageFramebuffer * const framebuffer, const int &index);
    int nextAvailableTextureIndex();
    void setInputSize(const Size &size, int index);
    Size maximumOutputSize();
    void endProcessing();
    bool shouldIgnoreUpdatesToThisTarget() const;
    bool enable() const;
    void processFrame(int index);
    
    bool mPreventRendering;
    
private:
    ImageFramebuffer *mFirstFramebuffer;
    ShaderProgram *mProgram;
    GLint mPositionAttribute, mTextureCoordinateAttribute;
    GLint mInputTextureUniform;
    GLfloat mRed, mGreen, mBlue, mAlpha;
    bool mIsEndProcessing;
    Size mCurrentSize;
    
    
};
}

#endif /* BasicOperation_h */
