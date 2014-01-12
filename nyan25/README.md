# 5章 cocos2d-xの基本

サンプルゲーム: にゃんこタップ25

## メモ

### プロジェクトの自動生成

以下のPythonコマンドを叩けばプロジェクトが自動生成される。

    cd ${COCOS_HOME}/tools/project-creator
    ./create_project.py -project ProjectName -package com.example.projectname -language cpp

### 画面解像度

同じiPhoneシミュレータでも、
Retina 3.5インチかRetina 4.0インチかによって解像度が異なる。

シミュレータのハードウェア>デバイスから変更できる。

### convertToGL

iPhoneでは画面左上が(0, 0)座標だが、
OpenGLでは画面左下が(0, 0)座標となる。
この変換をCCDirector::convertToGL関数が行ってくれる。
