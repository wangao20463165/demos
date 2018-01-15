#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PopSprite.hpp"
USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    CREATE_FUNC(HelloWorld);
    
    //自动创建游戏的pop 10*10 的矩形方阵
    void autoCreatePopSprite(cocos2d::Size _s);
    
    //监听手势识别
    virtual bool onTouchBegan(cocos2d::Touch* _touch,cocos2d::Event *_event);
    
private:
    //定义pop的存储 数组
    PopSprite* _popSpriteArr[10][10];
    
    //点击获取 Pop对象
    PopSprite* getPopStarSprite(cocos2d::Size size,cocos2d::Point touchPoint);
    
    //创建一个数组来存放被点击的pop的上下左右的数据
    cocos2d::__Array* _popArr;
    
    //通过pop的对象获取其上下左右的数据
    cocos2d::__Array* checkPopUDLR(PopSprite* pop);
    
    //通过pop的上下左右数组来检测数组里面每一个pop的上下左右数据
    void checkPopISNEW(cocos2d::__Array* arr);
    //让空白被上面的pop填充
    void reDiessPopStar();
    void reDiessPopStarRun(int x);
    //判断完成上下移动之后，判读是否需要左右移动
    void reDiessPopStarRT();
    //检测游戏是否可以继续
    bool reGameOver();
};

















#endif
