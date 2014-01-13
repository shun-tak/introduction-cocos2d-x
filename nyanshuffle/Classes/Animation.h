//
//  Animation.h
//  nyanshuffle
//
//  Created by shun-tak on 14/01/13.
//
//

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "cocos2d.h"

USING_NS_CC;

class Animation
{
public:
    // Chapter 6.4で追記する内容
    static CCFiniteTimeAction* catStartAction();

    static CCFiniteTimeAction* vibrationAnimation();
    static CCFiniteTimeAction* boxesStartAction(CCObject* target, SEL_CallFunc selector);
    static CCFiniteTimeAction* boxesStartActionWithVibration(CCObject* target, SEL_CallFunc selector);
};

#endif // __ANIMATION_H__
