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

inline float randomValueBetween(float low, float high)
{
	return ( (float)rand( ) / ( (float)RAND_MAX + 1.0f ) ) * high + low;
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