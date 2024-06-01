#pragma once
#include "Requests.h"


class RequestResult;
class RequestInfo;

class IRequestHandler {
public:
    virtual bool isRequestRelevant(const RequestInfo& info) = 0;
    virtual RequestResult handleRequest(const RequestInfo& info) = 0;
};
