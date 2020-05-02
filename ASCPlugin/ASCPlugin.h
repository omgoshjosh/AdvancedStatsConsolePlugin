#pragma once

// shot speed original
#pragma comment( lib, "bakkesmod.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "ballchasing/BallchasingApi.h"
#include "GUISettings.h"

constexpr auto plugin_version = "1.0";

struct Popup
{
	float startTime = 0.f;
	std::string text = "";
	Vector2 startLocation = { -1, -1 };
};

class ASCPlugin : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginWindow
{
public:
	// boiler plate
	virtual void onLoad();
	virtual void onUnload();

	// SHOT SPEED
	// shot speed popup
	std::vector<Popup> popups;
	// shot speed event handlers
	void OnHitBallPre(CarWrapper cw, void* params, std::string eventName);
	void OnHitBall(std::string eventName);
	// shot speed popup render
	void RenderShotSpeedPopup(CanvasWrapper canvas);

	// BALLCHASING
	std::shared_ptr<BallchasingAPI> api;

	//// Inherited via PluginWindow
	bool isWindowOpen_ = false;
	bool isMinimized_ = false;
	std::string menuTitle_ = "Ballchasing.com - Log";
	GUISettings guiSettings;

	virtual void Render() override;
	virtual std::string GetMenuName() override;
	virtual std::string GetMenuTitle() override;
	virtual void SetImGuiContext(uintptr_t ctx) override;
	virtual bool ShouldBlockInput() override;
	virtual bool IsActiveOverlay() override;
	virtual void OnOpen() override;
	virtual void OnClose() override;

	// The meat and potatoes
	void RenderReplayDetail(GetReplayResponseData* detail);

	void CoreStatsContextMenu();
	void ContextMenu(std::vector<TableColumn>& columnData);
	void RenderTableTab(std::string name, TableSettings& settings, GetReplayResponseData* detail, bool blueHeader = true, bool orangeHeader = true);
	void RenderTeamTable(Team& t, TableSettings& settings, bool drawHeader = true);
};

