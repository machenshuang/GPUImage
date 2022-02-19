//
//  Size.cpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/19.
//

#include "Size.h"

namespace gpu {

Size::Size(float width, float height): mWidth(width), mHeight(height) {
    
}

Size::~Size() {
    printf("Size 释放");
}

float Size::width() {
    return mWidth;
}

float Size::height() {
    return mHeight;
}

}
