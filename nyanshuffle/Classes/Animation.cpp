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

CCFiniteTimeAction* Animation::vibrationAnimation()
{
    CCMoveBy* move1 = CCMoveBy::create(0.03, ccp(-5, 0));
    CCMoveBy* move2 = CCMoveBy::create(0.06, ccp(10, 0));
    CCMoveBy* move3 = CCMoveBy::create(0.03, ccp(-5, 0));
    CCSequence* moves = CCSequence::create(move1, move2, move3, NULL);

    return CCRepeat::create(moves, 2);
}

CCFiniteTimeAction* Animation::boxesStartAction(CCObject* target, SEL_CallFunc selector)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    int random = rand();

    float delayTime = 1;

    switch (random % 5)
    {
        case 0: delayTime = delayTime * 0.90; break;
        case 1: delayTime = delayTime * 0.95; break;
        case 2: delayTime = delayTime * 1.05; break;
        case 3: delayTime = delayTime * 1.10; break;
        defalut: break;

    }

    CCDelayTime* delay1 = CCDelayTime::create(delayTime);
    CCMoveBy* move1 = CCMoveBy::create(1, ccp(0, - size.height));
    CCEaseIn* ease1 = CCEaseIn::create(move1, 10);

    CCDelayTime* delay2 = CCDelayTime::create(0.9);
    CCCallFunc* func = CCCallFunc::create(target, selector);
    CCFiniteTimeAction* seq = CCSequence::createWithTwoActions(delay2, func);

    CCSpawn* spawn = CCSpawn::createWithTwoActions(ease1, seq);

    return CCSequence::createWithTwoActions(delay1, spawn);
}

CCFiniteTimeAction* Animation::boxesStartActionWithVibration(CCObject* target, SEL_CallFunc selector)
{
    CCFiniteTimeAction* action1 = boxesStartAction(target, selector);
    CCFiniteTimeAction* action2 = Animation::vibrationAnimation();

    return CCSequence::createWithTwoActions(action1, action2);
}