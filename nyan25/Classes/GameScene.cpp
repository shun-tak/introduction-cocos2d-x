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
    nextNumber = 1;
    gametime = 0;

    // タップイベントを取得する
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);

    // 背景を作成する
    makeBackground();

    // 1~25のカードを配置する
    makeCards();

    // ゲーム時間を表示する
    showGametimeLabel();

    // ゲーム時間をカウントアップする関数を毎フレーム呼び出す
    this->schedule(schedule_selector(GameScene::measureGametime));

    // リトライボタンを作成する
    makeRetryButton();

    // ハイスコアを表示する
    showHighScoreLabel();

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

// タップが開始されたことの処理
bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    return true;
}

// タップが終了したときの処理
void GameScene::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    // タップポイント取得
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());

    CCNode* pCard = this->getChildByTag(nextNumber);
    if (!pCard)
    {
        return;
    }

    CCRect cardRect = pCard->boundingBox();
    if (cardRect.containsPoint(touchPoint))
    {
        // 裏カードを作成する
        CCSprite* pNewCard = CCSprite::create("card_backside.png");
        pNewCard->setPosition(pCard->getPosition());
        this->addChild(pNewCard);

        // 表カードを削除する
        pCard->removeFromParentAndCleanup(true);

        if (nextNumber >= 25)
        {
            // ゲーム時間の計測を停止する
            this->unschedule(schedule_selector(GameScene::measureGametime));

            // ハイスコアを表示する
            showHighScoreLabel();

            return;
        }

        nextNumber++;
    }
}

// ゲーム時間をカウントアップする
void GameScene::measureGametime(float fDelta)
{
    gametime += fDelta;

    // ゲーム時間を表示する
    showGametimeLabel();
}

// ゲーム時間を表示する
void GameScene::showGametimeLabel()
{
    // ゲーム時間ラベル用タグ
    const int tagGametimeLabel = 100;

    // ゲーム時間を文字列に変換する
    CCString* timeString = CCString::createWithFormat("%8.1fs", gametime);

    CCLabelTTF* timerLabel = (CCLabelTTF*)this->getChildByTag(tagGametimeLabel);
    if (timerLabel)
    {
        // ゲーム時間を更新する
        timerLabel->setString(timeString->getCString());
    }
    else
    {
        // 画面サイズを取得する
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        // ゲーム時間ラベルを生成する
        timerLabel = CCLabelTTF::create(timeString->getCString(), "Arial", 24.0);
        timerLabel->setPosition(ccp(winSize.width * 0.9,
                                    winSize.height * 0.9));
        timerLabel->setTag(tagGametimeLabel);
        this->addChild(timerLabel);
    }
}

// リトライボタンを作成する
void GameScene::makeRetryButton()
{
    // 画面サイズを取得する
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    // リトライボタンを作成する
    CCLabelTTF* retryLabel = CCLabelTTF::create("Retry", "Arial", 24.0);
    CCMenuItemLabel* retryItem = CCMenuItemLabel::create(retryLabel,
                                                         this,
                                                         menu_selector(GameScene::tapRetryButton));
    retryItem->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.2));

    // メニューを作成する
    CCMenu* menu = CCMenu::create(retryItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

// リトライボタンタップ時の処理
void GameScene::tapRetryButton(CCNode *node)
{
    // ゲームのシーンを新しく用意する
    CCScene* gameScene = (CCScene*)GameScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
}

// ハイスコアラベルを表示する
void GameScene::showHighScoreLabel()
{
    // CCUserDefaultクラスのインスタンスを取得する
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();

    // ハイスコアのキーを取得する
    const char* highScoreKey = "highscore";

    // 以前のハイスコアを取得する
    float highscore = userDefault->getFloatForKey(highScoreKey, 99.9);
    if (gametime != 0)
    {
        if (gametime > highscore)
        {
            // ハイスコアが更新されていない場合は処理を抜ける
            return;
        }
        else
        {
            // ハイスコアを更新する
            highscore = gametime;

            // ハイスコアを記録する
            userDefault->setFloatForKey(highScoreKey, highscore);
            userDefault->flush();
        }
    }

    // ハイスコアラベル用タグ
    const int tagHighScoreLabel = 200;

    // ハイスコアを表示する文字列を生成する
    CCString* highScoreString = CCString::createWithFormat("%8.1fs", highscore);

    // ハイスコアラベルを取得する
    CCLabelTTF* highScoreLabel = (CCLabelTTF*)this->getChildByTag(tagHighScoreLabel);
    if (highScoreLabel)
    {
        // ハイスコアラベルを更新する
        highScoreLabel->setString(highScoreString->getCString());
    }
    else
    {
        // 画面サイズを取得する
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        // ハイスコアラベルを生成する
        highScoreLabel = CCLabelTTF::create(highScoreString->getCString(), "Arial", 24.0);
        highScoreLabel->setPosition(ccp(winSize.width * 0.9,
                                        winSize.height * 0.7));
        highScoreLabel->setTag(tagHighScoreLabel);
        this->addChild(highScoreLabel);
    }
}
