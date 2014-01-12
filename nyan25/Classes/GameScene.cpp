//
//  GameScene.cpp
//  nyan25
//
//  Created by shun-tak on 14/01/12.
//
//

#include "GameScene.h"

using namespace cocos2d;
using namespace std;

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    // 背景を作成する
    makeBackground();

    return true;
}

// 背景を作成する
void GameScene::makeBackground()
{
    // 画面サイズを取得
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    // 背景を生成
    CCSprite* pBG = CCSprite::create("background.png");
    pBG->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(pBG);
}
