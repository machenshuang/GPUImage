//
//  Size.hpp
//  GPUImage
//
//  Created by 马陈爽 on 2022/2/19.
//

#ifndef Size_h
#define Size_h

#include <stdio.h>

namespace gpu {
class Size {
public:
    Size(float width, float height);
    ~Size();
    float width() const;
    float height() const;
private:
    float mWidth;
    float mHeight;
};
}

#endif /* Size_h */
