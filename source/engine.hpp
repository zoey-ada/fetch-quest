#include <platypus.hpp>

#include "fetchQuestLogic.hpp"
#include "fetchQuestPlayerView.hpp"

class Engine: public Platypus
{
public:
	Engine(): Platypus("Fetch Quest") {}
	virtual ~Engine() = default;

	bool initialize() { return Platypus::initialize(); }
	int run() { return Platypus::run(); }
	void deinitialize() { return Platypus::deinitialize(); }

protected:
	std::shared_ptr<BaseGameLogic> createLogicAndView() override
	{
		auto logic = std::make_shared<FetchQuestLogic>();
		logic->initialize(this->_cache);

		auto view =
			std::make_shared<FetchQuestPlayerView>(this->_renderer, this->_cache, this->_settings);
		assert(view->initialize());
		logic->addView(view);

		return logic;
	}
};
