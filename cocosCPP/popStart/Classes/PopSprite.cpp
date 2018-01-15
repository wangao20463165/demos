//
//  PopSprite.cpp
//  popStart
//
//  Created by 曹佳兴 on 2018/1/10.
//
//

#include "PopSprite.hpp"

PopSprite * PopSprite::createPopSprite(int numbers,int width,int height,float popSpriteX,float popSpriteY){
    PopSprite *enemy=new PopSprite();
    if(enemy&&enemy->init()){
        enemy->autorelease();
        enemy->enemyInit( numbers,  width,  height,  popSpriteX,  popSpriteY);
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
}


bool PopSprite::init(){
    if (Sprite::init()==false) {
        return false;
    }
    return true;
}

cocos2d::Point PopSprite::getColorBGPoint(){
    return this->_layerColorBG->getPosition();
}

//获取数字
int PopSprite::getNumber(){
    return this->_numbers;
}
//设置数字
void PopSprite::setNumber(int v){
    this->_numbers=v;
    //痛殴数字来判断设置精灵的颜色
    if (this->_numbers==-1) {
        this->_layerColorBG->setColor(cocos2d::Color3B(200,190,180));
    }
    if (this->_numbers==0) {//黄色
        this->_layerColorBG->setColor(cocos2d::Color3B(250,230,40));
    }
    if (this->_numbers==1) {//蓝色
        this->_layerColorBG->setColor(cocos2d::Color3B(40,180,250));
    }
    if (this->_numbers==2) {//绿色
        this->_layerColorBG->setColor(cocos2d::Color3B(130,220,110));
    }
    if (this->_numbers==3) {//红色
        this->_layerColorBG->setColor(cocos2d::Color3B(250,80,130));
    }
    if (this->_numbers==4) {//紫色
        this->_layerColorBG->setColor(cocos2d::Color3B(100,50,250));
    }
}

int PopSprite::getPopX(){
    return this->_popX;
}
int PopSprite::getPopY(){
    return this->_popY;
}

void PopSprite::setPopX(int _x){
    this->_popX=_x;
}
void PopSprite::setPopY(int _y){
    this->_popY=_y;
}


//````````````````````private
void PopSprite::enemyInit(int numbers,int width,int height,float popSpriteX,float popSpriteY){
    //设置需要初始化的数据
    this->_numbers=numbers;
    this->_popX=0;
    this->_popY=0;
    //加入游戏每一个pop的背景颜色
    this->_layerColorBG=cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255),width-5,height-5);
    this->_layerColorBG->setPosition(Point(popSpriteX,popSpriteY));
    this->addChild(this->_layerColorBG);
}





