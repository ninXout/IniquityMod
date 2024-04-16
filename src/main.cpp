#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/LocalLevelManager.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>

void addTransparentBG(CCNode* layer) {
	auto winSize = CCDirector::sharedDirector()->getWinSize();
        
	auto bg = CCSprite::create("GJ_gradientBG.png");
	auto bgSize = bg->getTextureRect().size;
	bg->setAnchorPoint({ 0.0f, 0.0f });
	bg->setScaleX((winSize.width + 10.0f) / bgSize.width);
	bg->setScaleY((winSize.height + 10.0f) / bgSize.height);
	bg->setPosition({ -5.0f, -5.0f });
	bg->setColor(ccc3(255, 255, 255));
	
	layer->addChild(bg, -2);
}

class $modify(EditLevelLayer) {
	bool init(GJGameLevel* ed) {
        EditLevelLayer::init(ed);
        
        addTransparentBG(this);
        getChildByID("level-name-background")->setVisible(false);
        getChildByID("description-background")->setVisible(false);

        return true;
    }
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
        LevelInfoLayer::init(level, challenge);
        
        addTransparentBG(this);

        return true;
 
    }
};

class $modify(CreatorLayer) {
	virtual bool init() {
        CreatorLayer::init();

        addTransparentBG(this);

        return true;
    }
};

class $modify(LeaderboardsLayer) {
    bool init(LeaderboardState state) {
        LeaderboardsLayer::init(state);

        addTransparentBG(this);

        return true;
    }
};

class $modify(LevelSearchLayer) {
	virtual bool init(int p0) {
		LevelSearchLayer::init(p0);

        addTransparentBG(this);
        
        return true;
    }
};

class $modify(LevelBrowserLayer) {
	bool init(GJSearchObject* search) {
		LevelBrowserLayer::init(search);

        addTransparentBG(this);

        return true;
    }
};

#include <Geode/modify/CCLayerColor.hpp>

class $modify(CCLayerColor) {
	bool initWithColor(cocos2d::_ccColor4B const& yk, float f1, float f2) {
		if (f1 != 569 && f2 != 320) return CCLayerColor::initWithColor({0,0,0,0},0,0);
		return CCLayerColor::initWithColor(yk, f1, f2);
	}
};