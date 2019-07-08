#ifndef __JIAOGUANLAYER_H__
#define __JIAOGUANILAYER_H__
#include<iostream>
#include"cocos2d.h"
#include"ui\CocosGUI.h"
#include"SceneManager.h"
#include"cocostudio/CocoStudio.h"
using namespace ui;
using namespace cocos2d;
using namespace cocostudio;
USING_NS_CC;
class SceneManager;
class JiaoguanLayer :public cocos2d::Layer{
public:
	CREATE_FUNC(JiaoguanLayer);
public:
	virtual bool init();
	SceneManager*tsm;
	static Scene *createScene();
	void touchCallBack(Ref*sender, Widget::TouchEventType controlEvent);
};
#endif

