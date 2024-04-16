#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/LocalLevelManager.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>

CCSprite* gif;

void GIFframe(int frame) {
    std::string resource = Mod::get()->getResourcesDir().string();
    std::stringstream nstr;
    nstr << resource << "/";
    nstr << std::setw(2) << std::setfill('0') << std::to_string(frame);
    nstr << ".png";
    gif->setTexture(CCTextureCache::sharedTextureCache()->addImage(nstr.str().c_str(), false));
}

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
        log::info("f1 is {} and f2 is {}", f1, f2);
		if ((f1 != 569 && f2 != 320) && (f1 != 358 && f2 != 40)) return CCLayerColor::initWithColor({0,0,0,0},0,0);
		return CCLayerColor::initWithColor(yk, f1, f2);
	}
};

#include <Geode/modify/LoadingLayer.hpp>

class $modify(LoadingLayer) {
    bool init(bool fromReload) {
        if (!LoadingLayer::init(fromReload)) return false;



        return true;
    }
};

#include <Geode/modify/MenuLayer.hpp>

class $modify(GIFLayer, MenuLayer) {
    double ss = 0.f;
    bool backsweep = false;

    bool init() {
        gif = CCSprite::create("00.png"_spr);
        for (int i = 0; i < 53; i++) GIFframe(i); // preload i think

        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        gif->setScaleY(winSize.height / gif->getContentSize().height);
        gif->setScaleX(winSize.width / gif->getContentSize().width);
        gif->setPositionX(winSize.width / 2);
        gif->setPositionY(winSize.height / 2);
        
        auto node = ((CCNode*)this->getChildren()->objectAtIndex(0));
        
        node->addChild(gif, 100);

        this->schedule(schedule_selector(GIFLayer::updateGIF));

        return true;
    }

    void updateGIF(CCObject*, float) {
        m_fields->ss += backsweep ? -(1.f / 2.f) : (1.f / 2.f);
        if (m_fields->ss > 53) backsweep = true;
        if (m_fields->ss < 1) backsweep = false;
        
        GIFframe((int)m_fields->ss);
    }
};