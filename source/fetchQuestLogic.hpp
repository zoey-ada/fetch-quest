#pragma once

#include <baseGameLogic.hpp>

namespace platypus
{
class IResourceCache;
};

class FetchQuestLogic: public BaseGameLogic
{
public:
	FetchQuestLogic();
	virtual ~FetchQuestLogic() = default;

	void onUpdate(Milliseconds delta) override;

	bool initialize(std::shared_ptr<platypus::IResourceCache> cache) override;
};
