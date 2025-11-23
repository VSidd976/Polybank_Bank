#pragma once
#include "crow.h"
#include <iostream>
using namespace crow;
using namespace std;

struct AuthMiddleware {
    struct context {
        int cardId;
        int accountId;
        int clientId;
    };

    void before_handle(request&, response&, context&);
    void after_handle(request&, response&, context&);
};
