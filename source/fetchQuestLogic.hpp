#pragma once

#include <baseGameLogic.hpp>

class FetchQuestLogic: public BaseGameLogic
{
public:
	FetchQuestLogic();
	virtual ~FetchQuestLogic() = default;

	void onUpdate(Milliseconds delta) override;

	bool initialize() override;
};
