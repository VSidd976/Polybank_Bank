#pragma once
#include "crow.h"
#include "AppContext.h"
#include "AuthMiddleware.h"
using namespace crow;

template <typename Service>
class BaseController {
protected:
    App<AuthMiddleware>& _app;
    Service& _service;

public:
    explicit BaseController(App<AuthMiddleware>& app)
        : _app(app), _service(AppContext::get<Service>())
    {}

    virtual void registerRoutes() = 0;
};
