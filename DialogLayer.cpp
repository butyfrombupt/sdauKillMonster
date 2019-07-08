#include "DialogLayer.h"
void pushChineseStr(std::string str, std::vector<std::string>&strVector){
	int sum = strlen(str.c_str());
	for (int cur = 0; cur < sum;){
		std::string lines;
		char t = str[cur];
		if ((t & 0xE0) == 0xE0){
			lines = lines + t + str[cur + 1] + str[cur + 2];
			cur += 3;
		}
		else if ((t & 0xC0) == 0xC0){
			lines = lines + t + str[cur + 1];
			cur += 2;
		}
		else{
			lines = lines + t;
			cur++;
		}
		strVector.push_back(lines);
	}
}

DialogLayer * DialogLayer::createWithJsonFile(const char* filename){
	DialogLayer* dialoglayer = new DialogLayer();
	if (dialoglayer&&dialoglayer->init(filename)){
		dialoglayer->autorelease();
	}
	else{
		CC_SAFE_DELETE(dialoglayer);
	}
	return dialoglayer;
}
bool DialogLayer::init(std::string str){
	initScene("DialogLayer.csb");
	tell = Label::create();
	tell->setColor(Color3B::BLACK);
	tell->setPosition(Vec2(500, 150));
	tell->setSystemFontSize(20);
	tell->setWidth(540);
	//tell->setHeight(100);
	tell->setLineBreakWithoutSpace(true);
	tell->setMaxLineWidth(540);
	this->addChild(tell);
	conversation = FileUtils::getInstance()->getStringFromFile(str);
	index = 0;
	getDataByIndex(index);
	return true;
}
void DialogLayer::MultUpdate(float dt){
	if (vecLength < (int)strVector.size()){
		tempStr = tempStr + strVector[vecLength].c_str();
		tell->setString(tempStr);
		speech->setVisible(false);
		vecLength++;
	}
}
void DialogLayer::getDataByIndex(int idx){
	Document doc;
	doc.Parse<kParseDefaultFlags>(conversation.c_str());
	conVector.clear();
	isover = false;
	vecLength = 0;

	rapidjson::Value &array = doc["Conversation"];
	if (array.IsArray()){
		int i = idx;
		int j = 0;
		strVector.clear();
		if (i >= array.Size()){
			auto delay = DelayTime::create(2.0f);
			auto action = Sequence::create(delay, CallFunc::create([&]{
				this->removeFromParent();
			}), nullptr);
			this->runAction(action);
			return;
		}
		for (j = 0; j < array[i]["content"].Size(); j++){
			rapidjson::Value &str = array[i]["content"][j];
			mStr = str.GetString();
			conVector.push_back(str.GetString());
			if (j == 2){
				pushChineseStr(mStr, strVector);
			}
		}
		name->setColor(Color3B::BLACK);
		name->setString(conVector[0].c_str());
		icon->loadTexture(conVector[1]);
	}
	tempStr = "";
	schedule(CC_SCHEDULE_SELECTOR(DialogLayer::MultUpdate), 0.1f);
}
void DialogLayer::showAllContent(){
	isover = true;
	unschedule(schedule_selector(DialogLayer::MultUpdate));
	tell->setString(mStr);
}
void DialogLayer::initScene(const char* filename){
	Node* node = CSLoader::createNode(filename);
	Layout * layout = static_cast<Layout*>(node->getChildByTag(1));
	name = static_cast<Text*>(layout->getChildByTag(141));
	speech = static_cast<Text*>(layout->getChildByTag(142));
	icon = static_cast<ImageView*>(layout->getChildByTag(101));
	icon->ignoreContentAdaptWithSize(true);
	layout->addTouchEventListener(CC_CALLBACK_2(DialogLayer::touchDownAction, this));
	this->addChild(node);
}
void DialogLayer::touchDownAction(Ref*sender, Widget::TouchEventType controlEvent){
	if (controlEvent == Widget::TouchEventType::ENDED){
		if (isover == true);
		index++;
		getDataByIndex(index);
	}
	else{
		this->showAllContent();
	}
}
