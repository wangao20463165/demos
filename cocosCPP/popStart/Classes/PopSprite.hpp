//
//  PopSprite.hpp
//  popStart
//
//  Created by 曹佳兴 on 2018/1/10.
//
//

#ifndef PopSprite_hpp
#define PopSprite_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class PopSprite:public cocos2d::Sprite{
    
public:
    //初始化游戏     数值 宽度 高度 x坐标 y坐标
    static PopSprite * createPopSprite(int numbers,int width,int height,float popSpriteX,float popSpriteY);
    virtual bool init();
    CREATE_FUNC(PopSprite);
    
    //获取数字
    int getNumber();
    //设置数字
    void setNumber(int v);
    
    //获取色块的坐标
    cocos2d::Point getColorBGPoint();
    
    int _popX,_popY;
    //获取色块的 位值
    int getPopX();
    int getPopY();
    
    void setPopX(int _x);
    void setPopY(int _y);
    
private:
    //显示的颜色
    int _numbers;
    void enemyInit(int numbers,int width,int height,float popSpriteX,float popSpriteY);
    //显示的背景
    cocos2d::LayerColor* _layerColorBG;
};

#endif /* PopSprite_hpp */
