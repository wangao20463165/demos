#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"



Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //创建游戏背景
    auto layerColor=cocos2d::LayerColor::create(cocos2d::Color4B(180,170,160,255));
//    layerColor->setContentSize(visibleSize);
    this->addChild(layerColor);
    
    this->autoCreatePopSprite(visibleSize);
    
    //初始化触摸监听
    auto touchListener=EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan=CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* _touch,cocos2d::Event *_event){
   
    //初始化poparr
    _popArr=cocos2d::__Array::create();
    
    //获取触摸的X 和 Y
    Point touchPoint=_touch->getLocation();
    
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //
    PopSprite *pop=this->getPopStarSprite(visibleSize, touchPoint);
//    log("%i,%i",pop->getPopX(),pop->getPopY());
    
    if (pop!=nullptr) {
        log("点击::(%d,%d)",pop->getPopX(),pop->getPopY());
        _popArr=checkPopUDLR(pop);
        if (_popArr->count()<2) {
            return true;
        }
        checkPopISNEW(_popArr);
    }
    return true;
}

void HelloWorld::checkPopISNEW(cocos2d::__Array* arr_old){
    //获取到新的数据数组
    //arr_old 1，0
    cocos2d::__Array * arrnew=cocos2d::__Array::create();
    
    for (int i=0; i<arr_old->count(); i++) {
        PopSprite* pop=(PopSprite*)arr_old->getObjectAtIndex(i);
        cocos2d::__Array* arr_news=this->checkPopUDLR(pop);
        //arr_news 1,1 0,0 2,0 3,0
        
        log("arr_old->(%d,%d)",pop->getPopX(),pop->getPopY());
        for (int j=0; j<arr_news->count(); j++) {
            bool isSave=false;
            PopSprite* popnew=(PopSprite*)arr_news->getObjectAtIndex(j);
//            log("arr_new->(%d,%d)",popnew->getPopX(),popnew->getPopY());
            
            for(int k=0;k<this->_popArr->count();k++){
                //_popArr 1,0
                PopSprite* popold=(PopSprite*)this->_popArr->getObjectAtIndex(k);
                
                if (popnew->getPopX()==popold->getPopX()&&
                    popnew->getPopY()==popold->getPopY()) {//已经保存过了
                    isSave=true;
                    break;
                }
            }
            if(!isSave){//没保存的 保存一下
                arrnew->addObject(popnew);
            }
        }
    }
    if (arrnew->count()>0) {
        for (int f=0;f<arrnew->count(); f++) {
            this->_popArr->addObject(arrnew->getObjectAtIndex(f));
        }
        this->checkPopISNEW(arrnew);//对新数据数组进行迭代
    }else{//晴空数据
        for(int s=0;s<this->_popArr->count();s++){
            PopSprite* p=(PopSprite*)this->_popArr->getObjectAtIndex(s);
            p->setNumber(-1);
        }
        reDiessPopStar();
    }
}
void HelloWorld::reDiessPopStar(){
    
    //逐列检测每一个pop的number是否等于-1 如果是 number=-1的pop向上移动到（x,9）
    for (int x=0; x<10; x++) {
        this->reDiessPopStarRun(x);
    }
    
    //判断完成上下移动之后，判读是否需要左右移动
    this->reDiessPopStarRT();
    
    this->reGameOver();
}

//检测游戏是否可以继续
bool HelloWorld::reGameOver(){
    bool isGameOver=true;
    
    for (int j=0; j<10; j++) {
        for (int i=0; i<10; i++) {
            int tmp_count=this->checkPopUDLR(this->_popSpriteArr[j][i])->count();
            int tmp_numb=this->_popSpriteArr[j][i]->getNumber();
            
//            log("j=%d  j=%d  tmp_count=%d  tmp_numb=%d",j,i,tmp_count,tmp_numb);
            
            
            
            if(tmp_count>0&&tmp_numb!=-1){
                isGameOver=false;
                break;
            }
        }
        if(!isGameOver){
            break;
        }
    }
    if(isGameOver){
        //重新开始游戏
        Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::create()));
    }
    
    return isGameOver;
}

void HelloWorld::reDiessPopStarRT(){
   
    for (int x=0; x<10; x++) {
        int offset=1;
        
        int number=0;
        for (int k=0; k<10; k++) {
            if(_popSpriteArr[x][k]->getNumber()==-1){
                number++;
            }
        }
        if(number==10){//整列都是-1 需要做整个x+1列向左移动
            for (int z=0; z<10; z++) {
                /*
                 if(this->_popSpriteArr[x+1][0]->getNumber()==-1){
                 offset++;
                 continue;
                 }
                 for (int s=x; s<9; s++) {
                 this->_popSpriteArr[s][z]->setNumber(this->_popSpriteArr[s+offset][z]->getNumber());
                 this->_popSpriteArr[s+offset][z]->setNumber(-1);
                 }
                 */
                
                
                /**/
                 for (int s=x; s<9; s++) {
                     this->_popSpriteArr[s][z]->setNumber(this->_popSpriteArr[s+1][z]->getNumber());
                     this->_popSpriteArr[s+1][z]->setNumber(-1);
                 }
                 
            }
        }
    }
}
void HelloWorld::reDiessPopStarRun(int x){
    int number=0;
    for (int k=0; k<10; k++) {
        if(_popSpriteArr[x][k]->getNumber()==-1){
            number++;
        }
    }
    if(number<1){
        return;
    }
//    log("=====>>x::%d",x);
    for (int y=0; y<10; y++) {
//         log("=====>>x::%d,y::%d,number::%d",x,y,number);
        if (this->_popSpriteArr[x][y]->getNumber()==-1) {
            int tmp=10-this->_popSpriteArr[x][y]->getPopY();
//            log("tmp::%d,x::%d,y::%d,number::%d",tmp,x,y,number);
            if(tmp>number){//判断当前的pop是不是最顶部的一个nunber=-1的pop
                for (int s=y; s<10; s++) {//在y=7的时候 如果789的number都是-1 这个时候直接跳出（上面没有了，自然不需要移动）
                    if(s+1==10){
                        this->_popSpriteArr[x][s]->setNumber(-1);
                    }else{
                        this->_popSpriteArr[x][s]->setNumber(this->_popSpriteArr[x][s+1]->getNumber());
                    }
                }
                reDiessPopStarRun(x);
            }else{
//                log("tmp::%d,x::%d,y::%d,number::%d--->break",tmp,x,y,number);
                break;
            }
        }
    }
}
cocos2d::__Array* HelloWorld::checkPopUDLR(PopSprite* pop){
    cocos2d::__Array* arr=cocos2d::__Array::create();
    //上下左右如果只有一个相同则忽略 有2个及2个以上则继续业务-消除
    bool isDoublePop=false;
    
    //校验上
    int up=pop->getPopY();
    for(int yu=up+1;yu<10;yu++){
        //上一个的numb
        int numb1=_popSpriteArr[pop->getPopX()][yu]->getNumber();
        //当前的numb
        int numb2=_popSpriteArr[pop->getPopX()][up]->getNumber();
        if(numb1==numb2&&numb1!=-1){
            isDoublePop=true;
            arr->addObject((PopSprite*)_popSpriteArr[pop->getPopX()][yu]);
//            _popSpriteArr[pop->getPopX()][yu]->setNumber(-1);
        }else{
            break;
        }
    }
//    log("up::%d",arr->count());
    //校验下
    int down=pop->getPopY();
    for(int yu=down-1;yu>=0;yu--){
        //下一个的numb
        int numb1=_popSpriteArr[pop->getPopX()][yu]->getNumber();
        //当前的numb
        int numb2=_popSpriteArr[pop->getPopX()][down]->getNumber();
        if(numb1==numb2&&numb1!=-1){
            isDoublePop=true;
            arr->addObject((PopSprite*)_popSpriteArr[pop->getPopX()][yu]);
//            _popSpriteArr[pop->getPopX()][yu]->setNumber(-1);
        }else{
            break;
        }
    }
//    log("down::%d",arr->count());
    //校验左边
    int left=pop->getPopX();
    for(int yu=left-1;yu>=0;yu--){
        //下一个的numb
        int numb1=_popSpriteArr[yu][pop->getPopY()]->getNumber();
        //当前的numb
        int numb2=_popSpriteArr[left][pop->getPopY()]->getNumber();
        if(numb1==numb2&&numb1!=-1){
            isDoublePop=true;
            arr->addObject((PopSprite*)_popSpriteArr[yu][pop->getPopY()]);
//            _popSpriteArr[yu][pop->getPopY()]->setNumber(-1);
        }else{
            break;
        }
    }
//    log("left::%d",arr->count());
    //校验右边
    int right=pop->getPopX();
    for(int yu=right+1;yu<10;yu++){
        //下一个的numb
        int numb1=_popSpriteArr[yu][pop->getPopY()]->getNumber();
        //当前的numb
        int numb2=_popSpriteArr[pop->getPopX()][pop->getPopY()]->getNumber();
        if(numb1==numb2&&numb1!=-1){
            isDoublePop=true;
            arr->addObject((PopSprite*)_popSpriteArr[yu][pop->getPopY()]);
//            _popSpriteArr[yu][pop->getPopY()]->setNumber(-1);
        }else{
            break;
        }
    }
//    log("right::%d",arr->count());
    if(isDoublePop){
        arr->addObject(pop);
//        _popSpriteArr[pop->getPopX()][pop->getPopY()]->setNumber(-1);
    }
    return arr;
}

PopSprite* HelloWorld::getPopStarSprite(cocos2d::Size size,cocos2d::Point touchPoint){
    //计算每一个 pop的宽高
    int lon=(size.width-28)/10;
    //求出X轴位置
    float x=(touchPoint.x-28)/lon;
    //求出Y轴位置
    float y=(touchPoint.y-(size.height/6+20))/lon;
    
    if(x<10 && y<10 && x>=0 && y>=0){
        int x1=(touchPoint.x-28)/lon;
        int y1=(touchPoint.y-size.height/6)/lon;
        return _popSpriteArr[x1][y1];
    }
    return nullptr;
}

//自动创建游戏的pop 10*10 的矩形方阵
void HelloWorld::autoCreatePopSprite(cocos2d::Size _s){
    //设置随机种子
    srand((unsigned)time(NULL));
    
    //计算每一个 pop的宽高
    int lon=(_s.width-28)/10;
    for (int j=0; j<10; j++) {
        for (int i=0; i<10; i++) {
            int maxX=5;
            int minX=0;
//            log("j::%d , i::%d",j,i);
            int rangeX=maxX-minX;
            int actvalX=((rand())%rangeX)+minX;
            
            
//            log("j::%d,i::%d,lon::%d , X::%f.0 ,Y::%f.0",j,i,lon,lon*j+20,lon*i+20+_s.height/6);
            PopSprite* pop=PopSprite::createPopSprite(-1, lon, lon, lon*j+20,lon*i+20+_s.height/6);
            pop->setPopX(j);
            pop->setPopY(i);
            /*
             if(j==1){
             actvalX=2;
             }
             if(i==3){
             actvalX=2;
             }
             */
            pop->setNumber(actvalX);
//            pop->setScale(1.25,1.2);
            addChild(pop);
            //将 pop添加到数组
            _popSpriteArr[j][i]=pop;
            
        }
    }
}



//~~~~~~~~~~~~~~~private







