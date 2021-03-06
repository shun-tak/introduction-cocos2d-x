//
//  GameScene.h
//  nyan25
//
//  Created by shun-tak on 14/01/12.
//
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
private:
    int nextNumber;
    float gametime;

    void makeBackground();
    void makeCards();
    void measureGametime(float fDelta);
    void showGametimeLabel();
    void makeRetryButton();
    void tapRetryButton(CCNode *node);
    void showHighScoreLabel();
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif // __GAME_SCENE_H__
