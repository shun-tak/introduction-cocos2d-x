//
//  Animation.cpp
//  nyanshuffle
//
//  Created by shun-tak on 14/01/13.
//
//

#include "Animation.h"

CCFiniteTimeAction* Animation::catStartAction()
{
    CCSkewTo* skew1 = CCSkewTo::create(0.2, 1, 0);
    CCSkewTo* skew2 = CCSkewTo::create(0.2, -1, 0);
    CCSequence* seq = CCSequence::createWithTwoActions(skew1, skew2);
    CCRepeat* repeat = CCRepeat::create(seq, 10);

    return repeat;
}