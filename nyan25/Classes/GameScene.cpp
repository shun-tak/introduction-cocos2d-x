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

    // 変数を初期化する
    srand((unsigned)time(NULL));

    // 背景を作成する
    makeBackground();

    // 1~25のカードを配置する
    makeCards();

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

// 1~25のカードを配置する
void GameScene::makeCards()
{
    // 数値配列を初期化する
    CCArray* numbers = CCArray::create();
    for (int i = 1; i <= 25; i++)
        numbers->addObject(CCInteger::create(i));

    // 画面サイズを取得
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    // カードを5x5に配置する
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            // ランダムで1つの値を取得する
            int index = rand() % numbers->count();
            int number = ((CCInteger*)numbers->objectAtIndex(index))->getValue();

            // カードを生成する
            CCSprite* pCard = CCSprite::create("card_frontside.png");
            CCSize cardSize = pCard->getContentSize();
            pCard->setPosition(ccp(winSize.width * 0.5 + (x -2) * cardSize.width,
                                   winSize.height * 0.5 + (y - 2) * cardSize.height));
            pCard->setTag(number);
            this->addChild(pCard);

           // カード番号を表示
            CCString* fileName = CCString::createWithFormat("%d.png", number);
            CCSprite* pNumber = CCSprite::create(fileName->getCString());
            pNumber->setPosition(ccp(cardSize.width * 0.5, cardSize.height * 0.5));
            pCard->addChild(pNumber);

            // 数値配列から値を削除する
            numbers->removeObjectAtIndex(index);
        }
    }

}
