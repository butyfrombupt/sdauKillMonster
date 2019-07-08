#include "FightScene.h"
#include"XiaoshuLayer.h"
#include "cocostudio/CocoStudio.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

Scene* FightScene::createScene()
{

	auto scene = Scene::create();

	auto layer = FightScene::create();

	scene->addChild(layer);

	return scene;
}

bool FightScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bg.jpg");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	std::string path9=FileUtils::getInstance()->getWritablePath();
					FileUtils::getInstance()->addSearchPath(path9, true);
									auto role = FileUtils::getInstance()->getValueMapFromFile("task.xml");
									role["TASK"] = 7;
									std::string ch = path9+"/task.xml";
									FileUtils::getInstance()->writeToFile(role, ch.c_str());
	 roleMap1 = FileUtils::getInstance()->getValueMapFromFile("choose.xml");
	int choose = roleMap1["CHOOSE"].asInt();
	if (choose == 1){
		player = Sprite::create("wennv1.png");
	}
	if (choose == 2){
		player = Sprite::create("wennan1.png");
	}
	if (choose == 3){
		player = Sprite::create("linan1.png");
	}
	if (choose == 4){
		player = Sprite::create("linv1.png");
	}
	player->setPosition(Vec2(150, 200));
	this->addChild(player, 0, 5);

	monster = Sprite::create("chongzi1.png");
	monster->setPosition(Vec2(800, 200));
	this->addChild(monster, 0, 6);

	//鎬墿琛�鏉�
	auto loadingbar = LoadingBar::create("planeHP.png");
	loadingbar->setDirection(LoadingBar::Direction::LEFT);
	loadingbar->setPercent(value);
	Vec2 pos = Vec2(monster->getPosition().x, monster->getPosition().y);
	loadingbar->setPosition(Vec2(pos.x - 10, pos.y + 115));
	this->addChild(loadingbar, 2, 100);


	//浜虹墿琛�鏉�
	auto ploadingbar = LoadingBar::create("playerHP.png");
	ploadingbar->setDirection(LoadingBar::Direction::LEFT);
	ploadingbar->setPercent(playervalue);
	Vec2 ppos = Vec2(player->getPosition().x, player->getPosition().y);
	ploadingbar->setPosition(Vec2(ppos.x - 5, ppos.y + 80));
	this->addChild(ploadingbar, 2, 101);

	auto fightlistener = EventListenerTouchOneByOne::create();
	fightlistener->setSwallowTouches(true);
	fightlistener->onTouchBegan = [](Touch* touch, Event* event){
		return true;
	};
	fightlistener->onTouchEnded = [=](Touch* touch, Event* event){
		Vec2 touchlocation = touch->getLocation();
		Vec2 nodelocation = this->convertTouchToNodeSpace(touch);
		if (monster->getBoundingBox().containsPoint(nodelocation)){
			this->selectSkill();

		}

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(fightlistener, monster);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic.mp3", true);
	//棰勫姞杞介煶鏁�
	SimpleAudioEngine::getInstance()->preloadEffect("huo.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("guangbo.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("duqi.mp3");

	return true;
}

//鏍规嵁鍚嶅瓧寰楀埌鍔ㄧ敾
Animate* FightScene::getAnimationByName(std::string animName, float delay, int animnum){
	Animation* animation = Animation::create();
	for (unsigned int i = 1; i <= animnum; i++){
		std::string frameName = animName;
		frameName.append(StringUtils::format("%d", i)).append(".png");
		animation->addSpriteFrameWithFile(frameName.c_str());
	}
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);
	Animate* animate = Animate::create(animation);
	return animate;
}
void FightScene::playerAction(int attack){
	int choose = roleMap1["CHOOSE"].asInt();
	Animate *playerAction;
	if (choose == 1){
		playerAction = getAnimationByName("wennv", 0.4f, 2);
	}
	if (choose == 2){
		 playerAction = getAnimationByName("wennan", 0.4f, 2);
	}
	if (choose == 3){
		playerAction = getAnimationByName("linan", 0.4f, 2);
	}
	if (choose == 4){
	  playerAction = getAnimationByName("linv", 0.4f, 2);
	}
	//auto playerAction = getAnimationByName("wennan", 0.4f, 2);
	player->runAction(playerAction);

	auto loadingbar = static_cast<LoadingBar*>(this->getChildByTag(100));
	//璁剧疆琛�鏉�
	float p = (float)attack / blood;
	value = value - p * 100;
	loadingbar->setPercent(value);
	//鎬墿鏀诲嚮鍏夋尝
	if (value != 100){
		auto callfunc = CallFunc::create([=]{
			this->monsterAction(attack);
		});
		//寤惰繜0.8绉掔瓑灏勭鍔ㄧ敾瀹屾瘯鍚庢墽琛屾�墿鎺夎绮掑瓙
		auto sequence = Sequence::create(DelayTime::create(0.8f), callfunc, NULL);
		this->runAction(sequence);
	}
	if (value <= 0){
		
		Director::getInstance()->replaceScene(XiaoshuLayer::createScene());
	}

}


//涓嶅悓鎶�鑳藉緱鍒颁笉鍚岀矑瀛愮壒鏁�
ParticleSystem* FightScene::getParticleWithAttack(int attack){
	ParticleSystem* particle;
	MoveTo* move2;
	switch (attack)
	{
	case 20:
		particle = ParticleSystemQuad::create("huoyan.plist");
		particle->setPositionType(ParticleSystem::PositionType::FREE);
		particle->setAutoRemoveOnFinish(true);
		particle->setPosition(Vec2(monster->getPosition().x + 10, monster->getPosition().y));
		SimpleAudioEngine::getInstance()->playEffect("huo.mp3", false, 1.0, 0.0, 1.0);

		break;
	case 50:
		particle = ParticleSystemQuad::create("guang.plist");
		particle->setPosition(Vec2(player->getPosition().x, player->getPosition().y));
		particle->setPositionType(ParticleSystem::PositionType::FREE);
		particle->setAutoRemoveOnFinish(true);
		move2 = MoveTo::create(0.6, Point(monster->getPosition().x, monster->getPosition().y + 10));
		particle->runAction(move2);
		SimpleAudioEngine::getInstance()->playEffect("guangbo.mp3", false, 2.0, 0.0, 1.0);

		break;
	case 70:
		particle = ParticleSystemQuad::create("lvqi.plist");
		particle->setPosition(Vec2(monster->getPosition().x + 10, monster->getPosition().y + 20));
		particle->setPositionType(ParticleSystem::PositionType::FREE);
		particle->setAutoRemoveOnFinish(true);
		SimpleAudioEngine::getInstance()->playEffect("duqi.mp3", false, 1.0, 0.0, 1.0);

		break;
	default:
		break;
	}
	return particle;

}
void FightScene::monsterAction(int attack){
	ParticleSystem *particle = this->getParticleWithAttack(attack);
	particle->setBlendAdditive(true);
	this->addChild(particle, 1, 7);
	auto remove = Sequence::create(
		DelayTime::create(1.5f),
		CallFunc::create([=]{

		this->removeChildByTag(7);

		//鎺夎鎻愮ず
		std::string str = cocos2d::Value(attack).asString();
		auto label = Label::createWithSystemFont("-" + str, "Marker Felt", 30);
		label->setPosition(Vec2(monster->getPosition().x + 10, monster->getPosition().y));
		label->setColor(Color3B::RED);
		this->addChild(label);


		//鍚戜笂椋樼Щ娣″嚭
		auto easein = EaseExponentialIn::create(Spawn::create(MoveBy::create(1.5f, Vec2(0, 150)), FadeOut::create(0.8f), NULL));
		label->runAction(easein);


		//鎬墿鏀诲嚮
		auto monsterAttack = getAnimationByName("chongzi", 0.2f, 3);
		auto callfunc = CallFunc::create([=]{
			//浜虹墿鎺夎绮掑瓙
			auto particle = ParticleSystemQuad::create("bloodSpurts.plist");
			particle->setPosition(Vec2(player->getPosition().x + 10, player->getPosition().y));
			particle->setPositionType(ParticleSystem::PositionType::FREE);
			particle->setAutoRemoveOnFinish(true);
			this->addChild(particle);
			//浜虹墿鎺夎鎻愮ず
			std::string str = cocos2d::Value(10).asString();
			auto label = Label::createWithSystemFont("-" + str, "Marker Felt", 30);
			label->setPosition(Vec2(player->getPosition().x + 10, player->getPosition().y));
			label->setColor(Color3B::RED);
			this->addChild(label);
			//鍚戜笂椋樼Щ娣″嚭
			auto easein = EaseExponentialIn::create(Spawn::create(MoveBy::create(1.5f, Vec2(0, 150)), FadeOut::create(0.8f), NULL));
			label->runAction(easein);
			//浜虹墿琛�鏉�
			auto loadingbar = static_cast<LoadingBar*>(this->getChildByTag(101));
			//璁剧疆琛�鏉�
			float p = (float)10 / playerhp;
			playervalue = playervalue - p * 100;
			loadingbar->setPercent(playervalue);


		});
		auto sequence = Sequence::create(monsterAttack, callfunc, NULL);
		monster->runAction(sequence);
	}), NULL);
	this->runAction(remove);
}
void FightScene::selectSkill(){
	auto jn1 = Button::create("jn1.png");
	auto jn2 = Button::create("jn2.PNG");
	auto jn3 = Button::create("jn3.PNG");
	jn1->setPosition(Vec2(player->getPosition().x - 80, player->getPosition().y - 100));
	jn2->setPosition(Vec2(player->getPosition().x + 10, player->getPosition().y - 100));
	jn3->setPosition(Vec2(player->getPosition().x + 100, player->getPosition().y - 100));

	jn1->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			this->playerAction(20);
		}
	});
	jn2->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			this->playerAction(50);
		}
	});
	jn3->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			this->playerAction(70);
		}
	});
	auto jn_1 = Label::createWithSystemFont("火火火火火", "Marker Felt", 20);
	jn_1->setPosition(Vec2(jn1->getPosition().x, jn1->getPosition().y - 40));

	auto jn_2 = Label::createWithSystemFont("机电之光", "Marker Felt", 20);
	jn_2->setPosition(Vec2(jn2->getPosition().x, jn2->getPosition().y - 40));

	auto jn_3 = Label::createWithSystemFont("防狼喷雾", "Marker Felt", 20);
	jn_3->setPosition(Vec2(jn3->getPosition().x, jn3->getPosition().y - 40));


	jn_1->setColor(Color3B::BLACK);
	jn_2->setColor(Color3B::BLACK);
	jn_3->setColor(Color3B::BLACK);
	this->addChild(jn_1);
	this->addChild(jn_2);
	this->addChild(jn_3);

	this->addChild(jn1);
	this->addChild(jn2);
	this->addChild(jn3);
}
