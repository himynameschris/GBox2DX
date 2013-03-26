/*
 MIT License
 
 Copyright (c) 2012 Chris Hannon / channon.us
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#ifndef GB2HELPER_H
#define GB2HELPER_H

#include "cocos2d.h"
#include "GB2Engine.h"
#include <iomanip>

#ifndef PTM_RATIO
#define PTM_RATIO 32.0
#endif

#ifndef RANDVALBETW
#define RANDVALBETW

USING_NS_CC;

inline float randomValueBetween(float low, float high)
{
	return ( ((float)rand() / RAND_MAX) * (high - low) + low );
}

#endif

/**
 * Clamp a value between 2 values
 * @param v the value to clamp
 * @param min lower limit
 * @param max upper limit
 */
template <class T>
inline float clamp(T v, T min, T max)
{
    if(v < min)
    {
        return min;
    }
    if(v > max)
    {
        return max;
    }
    return v;
}

/*
double round(double r) {
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}
*/

/**
 * Convert CGPoint to b2Vec2 honoring PTM_RATIO
 */
inline CCPoint CCPointFromb2Vec2(const b2Vec2 &p)
{
    return ccp(p.x * PTM_RATIO, p.y*PTM_RATIO);
}

/**
 * Convert b2Vec2 to CGPoint honoring PTM_RATIO
 */
inline b2Vec2 b2Vec2FromCCPoint(const CCPoint &p)
{
    return b2Vec2(p.x/PTM_RATIO, p.y/PTM_RATIO);
}

#endif