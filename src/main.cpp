#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

std::list<int> gameplayElements = { 10, 11, 12, 13, 35, 36, 45, 46, 47, 67, 84, 99, 101, 111, 140, 141, 286, 287, 660, 745, 746, 747, 748, 1022, 1330, 1331, 1332, 1333, 1594, 1704, 1751, 1933, 2063, 2064, 2902, 2926, 3004, 3005, 3027};
std::list<int> hazards = { 8, 39, 103, 392, 216, 217, 218, 458, 144, 205, 145, 459, 177, 178, 179, 1715, 1719, 1720, 1721, 135, 1711, 1712, 1713, 1714, 1717, 1716, 1731, 367, 1723, 1732, 368, 1724, 1722, 1725, 1726, 1727, 1728, 1729, 1730, 1733, 3610, 3611, 9, 61, 243, 244, 366, 363, 364, 365, 446, 447, 667, 989, 991, 720, 421, 422, 768, 1705, 1706, 1707, 187, 188, 740, 1701, 1702, 1703, 183, 184, 185, 186, 741, 742, 1708, 1709, 1710, 678, 679, 680, 1734, 1735, 1736, 1619, 1620, 98, 88, 89, 397, 398, 399, 3034, 3035, 3036, 3037 };

int numCheckpoints = 0;

class $modify(MyPlayLayer, PlayLayer) {
	void addObject(GameObject* p0) {
		int objID = p0->m_objectID;
		if (objID == 2063) numCheckpoints++;
		if (this->m_level->m_stars.value() != 0 && !Mod::get()->getSettingValue<bool>("enableOnRated")) {
			PlayLayer::addObject(p0);
			return;
		}
        if (Mod::get()->getSettingValue<bool>("enabled") && this->m_level->isPlatformer()) {
			if (Mod::get()->getSettingValue<int64_t>("passableBlock") != 0 && objID != 143) {
				if (Mod::get()->getSettingValue<int64_t>("passableBlock") == 1) p0->m_isPassable = true;
				else if (Mod::get()->getSettingValue<int64_t>("passableBlock") == -1) p0->m_isPassable = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("breakableBlockPassable") != 0 && objID == 143) {
				if (Mod::get()->getSettingValue<int64_t>("breakableBlockPassable") == 1) p0->m_isPassable = true;
				else if (Mod::get()->getSettingValue<int64_t>("breakableBlockPassable") == -1) p0->m_isPassable = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("dontBoostX") != 0) {
				if (Mod::get()->getSettingValue<int64_t>("dontBoostX") == 1) p0->m_isDontBoostX = true;
				else if (Mod::get()->getSettingValue<int64_t>("dontBoostX") == -1) p0->m_isDontBoostX = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("dontBoostY") != 0) {
				if (Mod::get()->getSettingValue<int64_t>("dontBoostY") == 1) p0->m_isDontBoostY = true;
				else if (Mod::get()->getSettingValue<int64_t>("dontBoostY") == -1) p0->m_isDontBoostY = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("nonStickX") != 0) {
				if (Mod::get()->getSettingValue<int64_t>("nonStickX") == 1) p0->m_isNonStickX = true;
				else if (Mod::get()->getSettingValue<int64_t>("nonStickX") == -1) p0->m_isNonStickX = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("nonStickY") != 0) {
				if (Mod::get()->getSettingValue<int64_t>("nonStickY") == 1) p0->m_isNonStickY = true;
				else if (Mod::get()->getSettingValue<int64_t>("nonStickY") == -1) p0->m_isNonStickY = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("gripSlope") != 0) {
				if (Mod::get()->getSettingValue<int64_t>("gripSlope") == 1) p0->m_isGripSlope = true;
				else if (Mod::get()->getSettingValue<int64_t>("gripSlope") == -1) p0->m_isGripSlope = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("extraSticky") != 0) {
				if (Mod::get()->getSettingValue<int64_t>("extraSticky") == 1) p0->m_isExtraSticky = true;
				else if (Mod::get()->getSettingValue<int64_t>("extraSticky") == -1) p0->m_isExtraSticky = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("scaleStick") != 0) {
				if (Mod::get()->getSettingValue<int64_t>("scaleStick") == 1) p0->m_isScaleStick = true;
				else if (Mod::get()->getSettingValue<int64_t>("scaleStick") == -1) p0->m_isScaleStick = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("extendColl") != 0) {
				if (Mod::get()->getSettingValue<int64_t>("extendColl") == 1) p0->m_hasExtendedCollision = true;
				else if (Mod::get()->getSettingValue<int64_t>("extendColl") == -1) p0->m_hasExtendedCollision = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("iceBlock") != 0) {
				if (Mod::get()->getSettingValue<int64_t>("iceBlock") == 1) p0->m_isIceBlock = true;
				else if (Mod::get()->getSettingValue<int64_t>("iceBlock") == -1) p0->m_isIceBlock = false;
			}
			if (Mod::get()->getSettingValue<int64_t>("audioScale") != 0) {
				if (Mod::get()->getSettingValue<int64_t>("audioScale") == 1) p0->m_hasNoAudioScale = true;
				else if (Mod::get()->getSettingValue<int64_t>("audioScale") == -1) p0->m_hasNoAudioScale = false;
			}
			if ((((200 <= objID) && (objID <= 203)) || objID == 1334) && Mod::get()->getSettingValue<int64_t>("multiActivate") != 0) {
				auto effectObject = typeinfo_cast<EffectGameObject*>(p0);
				if (Mod::get()->getSettingValue<int64_t>("multiActivate") == 1) effectObject->m_isMultiActivate = true;
				else if (Mod::get()->getSettingValue<int64_t>("multiActivate") == -1) effectObject->m_isMultiActivate = false;
				PlayLayer::addObject(effectObject); // call the original function
				return; // abort to avoid accidentally calling original function twice
			}
			if ((std::find(gameplayElements.begin(), gameplayElements.end(), objID) != gameplayElements.end()) && Mod::get()->getSettingValue<int64_t>("multiActivate") != 0) {
				auto enhancedObj = typeinfo_cast<EnhancedGameObject*>(p0);
				if (Mod::get()->getSettingValue<int64_t>("multiActivate") == 1) enhancedObj->m_isNoMultiActivate = false;
				else if (Mod::get()->getSettingValue<int64_t>("multiActivate") == -1) enhancedObj->m_isNoMultiActivate = true;
				PlayLayer::addObject(enhancedObj); // call the original function
				return; // abort to avoid accidentally calling original function twice
			}
			PlayLayer::addObject(p0); // call the original function
        }
        else PlayLayer::addObject(p0); // call the original function
	}
	void onQuit() {
		PlayLayer::onQuit(); // call the original function
		if (Mod::get()->getSettingValue<bool>("enabled")) numCheckpoints = 0;
	}
	void levelComplete() {
		PlayLayer::levelComplete(); // call the original function
		if (Mod::get()->getSettingValue<bool>("enabled")) numCheckpoints = 0;
	}
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects)) { return false; }
		if (!this->m_level->isPlatformer() || !Mod::get()->getSettingValue<bool>("enabled")) return true;
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
		return true;
	}
	void destroyPlayer(PlayerObject* p0, GameObject* p1) {
		if (!this->m_level->isPlatformer()) {
			PlayLayer::destroyPlayer(p0, p1);
			return;
		}
		if (
			(p1 == nullptr) || 
			Mod::get()->getSettingValue<bool>("enabled")
			&& Mod::get()->getSettingValue<bool>("ignoreHazardHitboxes")
			&& (std::find(hazards.begin(), hazards.end(), p1->m_objectID) != hazards.end())
			&& !(this->m_level->m_stars.value() != 0 && !Mod::get()->getSettingValue<bool>("enableOnRated"))
		) { return; }
		PlayLayer::destroyPlayer(p0, p1);
	}
};