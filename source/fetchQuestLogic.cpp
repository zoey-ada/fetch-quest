#include "fetchQuestLogic.hpp"

#include <entities/components/renderComponent2d.hpp>
#include <entities/entityFactory.hpp>
#include <resource_cache/iResourceCache.hpp>
#include <views/iView.hpp>

#include "entities/components/movementComponent2d.hpp"

FetchQuestLogic::FetchQuestLogic()
{}

void FetchQuestLogic::onUpdate(Milliseconds delta)
{
	switch (this->_state)
	{
	case GameState::Initializing:
	{
		// ServiceProvider::getAudioSystem()->playSound("event:/background", 0.2);
		// for (const auto& view : this->_views)
		// 	view->onRestore();

		// registerEventSink("input-event", DemoGameLogic::onInput);
		this->changeState(GameState::Loading);
		break;
	}
	case GameState::LoadingMainMenu:
	{
		// auto menu_image = this->createEntity("menu_title.json");
		// // auto logo = this->createEntity("logo.json");
		// // auto name = this->createEntity("company_name.json");
		// this->_menu_image = menu_image->getId();
		this->changeState(GameState::MainMenu);
		break;
	}
	case GameState::MainMenu:
	{
		for (const auto& view : this->_views)
			view->onUpdate(delta);

		for (const auto& entity : this->_entities)
			entity.second->update(delta);

		break;
	}
	case GameState::LoadingPauseMenu:
	{
		// auto menu_image = this->createEntity("menu_title.json");
		// this->_menu_image = menu_image->getId();
		this->changeState(GameState::PauseMenu);
		break;
	}
	case GameState::PauseMenu:
	{
		// ServiceProvider::getPhysicsSystem()->pause();

		for (const auto& view : this->_views)
			view->onUpdate(delta);

		for (const auto& entity : this->_entities)
			entity.second->update(delta);

		break;
	}
	case GameState::Loading:
	{
		auto player = this->createEntity("assets.zip/entities/blue_shirt.json");
		auto farmer = this->createEntity("assets.zip/entities/farmer.json");
		farmer->getComponent<RenderComponent2d>("render_component_2d")
			.lock()
			->playAnimation("idle");
		// this->createEntity("left_border.json");
		// this->createEntity("right_border.json");
		// this->createEntity("top_border.json");
		// this->createEntity("bottom_border.json");

		// auto ball = this->createEntity("ball.json");
		// this->_ball = ball->getId();

		// auto p1_paddle = this->createEntity("p1_paddle.json");
		// this->_player1_paddle = p1_paddle->getId();

		// auto p2_paddle = this->createEntity("p2_paddle.json");
		// this->_player2_paddle = p2_paddle->getId();

		// auto p1_goal = this->createEntity("p1_goal.json");
		// this->_player1_goal = p1_goal->getId();

		// auto p2_goal = this->createEntity("p2_goal.json");
		// this->_player2_goal = p2_goal->getId();

		// this->_p1_score_label.initialize();
		// this->_p1_score_value.initialize();
		// this->_p2_score_label.initialize();
		// this->_p2_score_value.initialize();

		// this->onResetGame();
		// this->registerEventSinks();

		// ServiceProvider::getInputManager()->loadConfiguration("./input_config.json");

		this->changeState(GameState::Running);
		break;
	}
	case GameState::Running:
	{
		for (const auto& view : this->_views)
			view->onUpdate(delta);

		for (const auto& entity : this->_entities)
			entity.second->update(delta);

		break;
	}
	default:
		throw std::exception("The game entered a state that could not be handled.");
	}
}

bool FetchQuestLogic::initialize(std::shared_ptr<platypus::IResourceCache> cache)
{
	if (!BaseGameLogic::initialize(cache))
		return false;

	this->_entity_factory->registerComponent("MovementComponent_2d", createMovementComponent2d);

	return true;
}
