#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

std::list<int> gameplayElements = { 10, 11, 12, 13, 35, 36, 45, 46, 47, 67, 84, 99, 101, 111, 140, 141, 286, 287, 660, 745, 746, 747, 748, 1022, 1330, 1331, 1332, 1333, 1594, 1704, 1751, 1933, 2063, 2064, 2902, 2926, 3004, 3005, 3027};
std::list<int> hazards = { 8, 39, 103, 392, 216, 217, 218, 458, 144, 205, 145, 459, 177, 178, 179, 1715, 1719, 1720, 1721, 135, 1711, 1712, 1713, 1714, 1717, 1716, 1731, 367, 1723, 1732, 368, 1724, 1722, 1725, 1726, 1727, 1728, 1729, 1730, 1733, 3610, 3611, 9, 61, 243, 244, 366, 363, 364, 365, 446, 447, 667, 989, 991, 720, 421, 422, 768, 1705, 1706, 1707, 187, 188, 740, 1701, 1702, 1703, 183, 184, 185, 186, 741, 742, 1708, 1709, 1710, 678, 679, 680, 1734, 1735, 1736, 1619, 1620, 98, 88, 89, 397, 398, 399, 3034, 3035, 3036, 3037 };

int numCheckpoints = 0;
int timesCalled = 0;

class $modify(MyLevelEditorLayer, LevelEditorLayer) {
	bool init(GJGameLevel* theLevel, bool p1) {
		if (!LevelEditorLayer::init(theLevel, p1)) return false;
		numCheckpoints = 0;
		timesCalled = 0;
		return true;
	}
};

class $modify(MyPlayerObject, PlayerObject){
	void animatePlatformerJump(float p0) {
		if (!(Mod::get()->getSettingValue<bool>("enabled") && Mod::get()->getSettingValue<bool>("noPlatformerJumpAnim"))) { PlayerObject::animatePlatformerJump(p0); }
	}
};

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	void onGarage(cocos2d::CCObject* sender) {
		if (!CCDirector::get()->getRunningScene()->getChildByID("EditLevelLayer")) {
			return LevelInfoLayer::onGarage(sender);
		}
		if (!Mod::get()->getSettingValue<bool>("enabled") || !Mod::get()->getSettingValue<bool>("checkpointCompatibility")) {
			LevelInfoLayer::onGarage(sender);
		} else {
			Notification* notification = Notification::create("[BreakingPlatforming] Disable \"Checkpoint Notif Compat\" for Garage.", nullptr, Mod::get()->getSettingValue<double>("notifDura") * 2.f);
			notification->show();
		}
	}
};

class $modify(MyPlayLayer, PlayLayer) {
	bool checkSetting(std::string setting, int value = 1) {
		Mod* brPL = Mod::get();
		if (!brPL->getSetting(setting)) {
			return false;
		}
		if (value != 0 && value != 1 && value != -1) {
			brPL->setSettingValue(setting, 0);
			return (brPL->getSettingValue<int64_t>(setting) == 0);
		}
		return (brPL->getSettingValue<int64_t>(setting) == value);
	}
	bool checkSettingEnabled(std::string setting) {
		return !MyPlayLayer::checkSetting(setting, 0);
	}
	void addObject(GameObject* theObject) {
		int objID = theObject->m_objectID;
		if (objID == 2063) { numCheckpoints++; }
		if (this->m_level->m_stars.value() != 0 && !Mod::get()->getSettingValue<bool>("enableOnRated")) {
			return PlayLayer::addObject(theObject);
		}
		if (Mod::get()->getSettingValue<bool>("enabled") && this->m_level->isPlatformer()) {
        		if (theObject->m_objectType == GameObjectType::Solid || theObject->m_objectType == GameObjectType::Slope) {    
				if (MyPlayLayer::checkSettingEnabled("breakableBlockPassable") && objID != 143) {
					theObject->m_isPassable = MyPlayLayer::checkSetting("passableBlock");
				}
			}
			if (MyPlayLayer::checkSettingEnabled("breakableBlockPassable") && objID == 143) {
				theObject->m_isPassable = MyPlayLayer::checkSetting("breakableBlockPassable");
			}
			if (MyPlayLayer::checkSettingEnabled("dontBoostX")) {
				theObject->m_isDontBoostX = MyPlayLayer::checkSetting("dontBoostX");
			}
			if (MyPlayLayer::checkSettingEnabled("dontBoostY")) {
				theObject->m_isDontBoostY = MyPlayLayer::checkSetting("dontBoostY");
			}
			if (MyPlayLayer::checkSettingEnabled("nonStickX")) {
				theObject->m_isNonStickX = MyPlayLayer::checkSetting("nonStickX");
			}
			if (MyPlayLayer::checkSettingEnabled("nonStickY")) {
				theObject->m_isNonStickX = MyPlayLayer::checkSetting("nonStickY");
			}
			if (MyPlayLayer::checkSettingEnabled("gripSlope") && theObject->m_objectType == GameObjectType::Slope) {
				theObject->m_isGripSlope = MyPlayLayer::checkSetting("gripSlope");
			}
			if (MyPlayLayer::checkSettingEnabled("extraSticky")) {
				theObject->m_isExtraSticky = MyPlayLayer::checkSetting("extraSticky");
			}
			if (MyPlayLayer::checkSettingEnabled("scaleStick")) {
				theObject->m_isScaleStick = MyPlayLayer::checkSetting("scaleStick");
			}
			if (MyPlayLayer::checkSettingEnabled("extendColl")) {
				theObject->m_hasExtendedCollision = MyPlayLayer::checkSetting("extendColl");
			}
			if (MyPlayLayer::checkSettingEnabled("iceBlock")) {
				theObject->m_isIceBlock = MyPlayLayer::checkSetting("iceBlock");
			}
			if (MyPlayLayer::checkSettingEnabled("audioScale")) {
				theObject->m_hasNoAudioScale = MyPlayLayer::checkSetting("audioScale");
			}
			if ((((200 <= objID) && (objID <= 203)) || objID == 1334) && MyPlayLayer::checkSettingEnabled("multiActivate")) {
				// note to self: in past versions of geode, the correct member to change was m_isMultiActivate
				auto effectObject = typeinfo_cast<EffectGameObject*>(theObject);
				effectObject->m_isMultiTriggered = MyPlayLayer::checkSetting("multiActivate");
				return PlayLayer::addObject(effectObject); // call the original function + abort to avoid accidentally calling original function twice
			} else if ((std::find(gameplayElements.begin(), gameplayElements.end(), objID) != gameplayElements.end()) && Mod::get()->getSettingValue<int64_t>("multiActivate") != 0) {
				auto enhancedObj = typeinfo_cast<EnhancedGameObject*>(theObject);
				enhancedObj->m_isNoMultiActivate = MyPlayLayer::checkSetting("multiActivate", -1);
				return PlayLayer::addObject(enhancedObj); // call the original function + abort to avoid accidentally calling original function twice
			}
			PlayLayer::addObject(theObject); // call the original function
        	}
        	else PlayLayer::addObject(theObject); // call the original function
	}
	void onQuit() {
		PlayLayer::onQuit(); // call the original function
		if (Mod::get()->getSettingValue<bool>("enabled")) {
			numCheckpoints = 0;
			timesCalled = 0;
		}
	}
	void levelComplete() {
		PlayLayer::levelComplete(); // call the original function
		if (Mod::get()->getSettingValue<bool>("enabled")) { numCheckpoints = 0; }
	}
	void updateTimeLabel(int p0, int p1, bool p2) {
		PlayLayer::updateTimeLabel(p0, p1, p2);
		if (!this->m_level->isPlatformer() || !Mod::get()->getSettingValue<bool>("enabled") || timesCalled > 0) { return; }
		timesCalled++;
		if (numCheckpoints == 0 && Mod::get()->getSettingValue<bool>("noCheckpointsNotify")) {
			Notification* notification = Notification::create("There are no checkpoints in this platformer.", nullptr, Mod::get()->getSettingValue<double>("notifDura") * 2.f);
			notification->show();
		} else if (Mod::get()->getSettingValue<bool>("numCheckpointsNotify")) {
			std::string checkpointsPlural = " checkpoints";
			if (numCheckpoints == 1) checkpointsPlural = " checkpoint";
			std::string checkpointTemplate = "This platformer has " + std::to_string(numCheckpoints) + checkpointsPlural + ".";
			Notification* notification = Notification::create(checkpointTemplate, nullptr, Mod::get()->getSettingValue<double>("notifDura"));
			notification->show();
		}
	}
	void destroyPlayer(PlayerObject* thePlayer, GameObject* theObject) {
		if (!this->m_level->isPlatformer() || !(Mod::get()->getSettingValue<bool>("enabled") && Mod::get()->getSettingValue<bool>("ignoreHazardHitboxes"))) {
			PlayLayer::destroyPlayer(thePlayer, theObject);
			return;
		}
		if (
			(theObject == nullptr) || 
			(std::find(hazards.begin(), hazards.end(), theObject->m_objectID) != hazards.end() || theObject->m_objectType == GameObjectType::Hazard || theObject->m_objectType == GameObjectType::AnimatedHazard)
			&& !(this->m_level->m_stars.value() != 0 && !Mod::get()->getSettingValue<bool>("enableOnRated"))
		) { return; }
		PlayLayer::destroyPlayer(thePlayer, theObject);
	}
};
