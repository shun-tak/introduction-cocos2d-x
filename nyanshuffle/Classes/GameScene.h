//
//  GameScene.h
//  nyanshuffle
//
//  Created by shun-tak on 14/01/13.
//
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
protected:
    CCSprite* m_pCat;
    CCMenuItemImage* m_pBox1;
    CCMenuItemImage* m_pBox2;
    CCMenuItemImage* m_pBox3;

    // Chapter 6.4で追記する内容
    void playDroppingSound();

public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
