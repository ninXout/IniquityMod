#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/utils/web.hpp>
#include <matjson.hpp>
#include <fstream>

class $modify(IniqMenuLayer, MenuLayer) {
    void updatePack() {
        web::WebRequest req = web::WebRequest();
        EventListener<web::WebTask> thing;
        thing.bind([this] (web::WebTask::Event* e) {
            if (web::WebResponse* value = e->getValue()) {
                auto thebytes = value->data();
                //Loader::get()->getInstalledMod("geode.texture-loader")->getSavedValue<std::string>("")
                std::filesystem::path packpath = Loader::get()->getInstalledMod("geode.texture-loader")->getConfigDir() / "packs" / "iniquity-pack.zip";

                std::ofstream out(packpath.c_str(), std::ios::out | std::ios::binary);
                out.write(reinterpret_cast<const char*>(thebytes.data()), thebytes.size());
                out.close();

                geode::createQuickPopup(
                    "Iniquity",
                    "Iniquity updated! Would you like to restart your game to update?",
                    "No", "Yes",
                    [](auto, bool btn2) {
                        if (btn2) {
                            geode::utils::game::restart();
                        }
                    }
                );
            } else if (e->isCancelled()) {
                Notification::create("Iniquity could not download the latest version", geode::NotificationIcon::Error)->show();
            }
        });
        auto task = req.post("https://github.com/ninXout/iniquity-pack/releases/latest/download/iniquity-pack.zip");
        thing.setFilter(task);
    }

    void setMSSetting(std::string key) {
        if (!Loader::get()->getInstalledMod("cgytrus.menu-shaders")->getSettingValue<bool>(key)) Loader::get()->getInstalledMod("cgytrus.menu-shaders")->setSettingValue<bool>(key, true);
    }

    bool init() {
        setMSSetting("show-search");
        setMSSetting("show-play-level");
        setMSSetting("show-level-browser");
        setMSSetting("show-level-select");
        setMSSetting("show-edit-level");
        setMSSetting("show-creator");
        setMSSetting("show-main");

        if (!MenuLayer::init()) return false;

        web::WebRequest req = web::WebRequest();
        EventListener<web::WebTask> thing;
        thing.bind([this] (web::WebTask::Event* e) {
            if (web::WebResponse* value = e->getValue()) {
                auto thejson = value->json().unwrap();
                log::info("new pack version is {}", thejson["tag_name"].as_string());
                if (Mod::get()->getSavedValue<std::string>("pack-version") != thejson["tag_name"].as_string()) {
                    Mod::get()->setSavedValue<std::string>("pack-version", thejson["tag_name"].as_string());
                    IniqMenuLayer::updatePack();
                }
            } else if (e->isCancelled()) {
                Notification::create("Iniquity could not get the latest version", geode::NotificationIcon::Error)->show();
            }
        });
        //auto task = req.post("https://api.github.com/repos/ninXout/iniquity-pack/releases/latest");
        //thing.setFilter(task);
        //IniqMenuLayer::updatePack();

        return true;
    }
};

#include <Geode/modify/LevelCell.hpp>

class $modify(LevelCell) {
    bool init() {
        if (!LevelCell::init()) return false;

        getChildOfType<CCLayerColor>(this, 0)->setVisible(false); // TODO: mess with LevelCell::loadFromLevel to do custom stuff

        return true;
    }

    void draw() {} // removes the stupid line between cells
};

#include <Geode/modify/GJListLayer.hpp>

class $modify(GJListLayer) {
    bool init(BoomListView* p0, char const* p1, cocos2d::ccColor4B p2, float p3, float p4, int p5) {
        if (!GJListLayer::init(p0, p1, {0, 0, 0, 100}, p3, p4, p5)) return false;

        this->getChildByID("left-border")->setVisible(false);
        this->getChildByID("right-border")->setVisible(false);
        this->getChildByID("bottom-border")->setVisible(false);
        this->getChildByID("top-border")->setVisible(false);

        return true;
    }
};

#include <Geode/modify/InfoLayer.hpp>

class $modify(InfoLayer) {
    bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2) {
        if (!InfoLayer::init(p0, p1, p2)) return false;

        static_cast<CCSprite*>(m_mainLayer->getChildByID("desc-background"))->setColor(ccc3(0, 0, 0));
        static_cast<CCSprite*>(m_mainLayer->getChildByID("desc-background"))->setOpacity(150.f);

        return true;
    }
};

#include <Geode/modify/GJCommentListLayer.hpp>

class $modify(GJCommentListLayer) {
    bool init(BoomListView* listView, char const* title, cocos2d::ccColor4B color, float width, float height, bool blueBorder) {
        color = {0, 0, 0, 0};

        if (!GJCommentListLayer::init(listView, title, color, width, height, blueBorder)) return false;

        this->getChildByID("left-border")->setVisible(false);
        this->getChildByID("right-border")->setVisible(false);
        this->getChildByID("bottom-border")->setVisible(false);
        this->getChildByID("top-border")->setVisible(false);

        return true;
    }
};

#include <Geode/modify/CommentCell.hpp>

class $modify(CommentCell) {
    void loadFromComment(GJComment* uhh) {
        CommentCell::loadFromComment(uhh);
        getChildOfType<CCLayerColor>(this, 0)->setVisible(false);
        static_cast<CCScale9Sprite*>(getChildOfType<CCLayer>(this, 1)->getChildByID("background"))->setColor(ccc3(0, 0, 0));
    }

    void draw() {}
};