#include <platypus.hpp>
#include <views/humanView.hpp>

#include "fetchQuestLogic.hpp"

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
		logic->initialize();

		auto view = std::make_shared<HumanView>(this->_renderer, this->_cache, this->_settings);
		logic->addView(view);

		return logic;
	}
};
