#include "GameRequestHandler.h"

class HeadOnGameRequestHandler : public GameRequestHandler {
public:
	RequestResult getHeadOnGameHealthState(const RequestInfo& info);
};