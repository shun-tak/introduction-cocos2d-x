//
//  GameScene.cpp
//  nyanshuffle
//
//  Created by shun-tak on 14/01/13.
//
//

#include "GameScene.h"
#include "Animation.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

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

    srand((unsigned int)time(NULL));
    int random = rand();

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // 背景の表示
    CCSprite* pBG = CCSprite::create("game_bg.png");
    pBG->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(pBG);

    CCSize bgSize = pBG->getContentSize();

    // 雲のアクション作成
    CCMoveBy* cloud1Action = CCMoveBy::create(80, ccp(bgSize.width, 0));
    CCMoveBy* cloud2Action = CCMoveBy::create(160, ccp(bgSize.width, 0));

    // 雲の表示
    CCSprite* pCloud1 = CCSprite::create("cloud.png");
    pCloud1->setPosition(ccp(bgSize.width * 0.4, bgSize.height * 0.83));
    pCloud1->runAction(cloud1Action);
    pBG->addChild(pCloud1);

    CCSprite* pCloud2 = CCSprite::create("cloud.png");
    pCloud2->setPosition(ccp(bgSize.width * 0.2, bgSize.height * 0.9));
    pCloud2->setScale(0.6);
    pCloud2->runAction(cloud2Action);
    pBG->addChild(pCloud2);

    // ネコの表示
    CCString* catImagePath = CCString::createWithFormat("cat%d.png", random % 5 + 1);
    m_pCat = CCSprite::create(catImagePath->getCString());
    m_pCat->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    m_pCat->runAction(Animation::catStartAction());
    this->addChild(m_pCat, 0);

    // 箱の表示
    CCString* boxFileName = CCString::createWithFormat("box%d.png", random % 2 + 1);
    m_pBox1 = CCMenuItemImage::create(boxFileName->getCString(), boxFileName->getCString(), NULL, NULL);
    m_pBox1->setPosition(ccp(size.width * 0.2, size.height * 1.5));
    m_pBox1->runAction(Animation::boxesStartAction(this, callfunc_selector(GameScene::playDroppingSound)));

    m_pBox2 = CCMenuItemImage::create(boxFileName->getCString(), boxFileName->getCString(), NULL, NULL);
    m_pBox2->setPosition(ccp(size.width * 0.5, size.height * 1.5));
    m_pBox2->runAction(Animation::boxesStartActionWithVibration(this, callfunc_selector(GameScene::playDroppingSound)));

    m_pBox3 = CCMenuItemImage::create(boxFileName->getCString(), boxFileName->getCString(), NULL, NULL);
    m_pBox3->setPosition(ccp(size.width * 0.8, size.height * 1.5));
    m_pBox3->runAction(Animation::boxesStartAction(this, callfunc_selector(GameScene::playDroppingSound)));

    CCMenu* menu = CCMenu::create(m_pBox1, m_pBox2, m_pBox3, NULL);
    menu->setPosition(CCPointZero);

    this->addChild(menu);

    return true;
}

void GameScene::playDroppingSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("rakka.mp3");
}
