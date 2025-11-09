#pragma once
#include "crow.h"
#include <iostream>
using namespace crow;
using namespace std;

struct AuthMiddleware {
    struct context {
        int _card_id;
        int _account_id;
        int _client_id;
    };

    void before_handle(request&, response&, context&);
    void after_handle(request&, response&, context&);
};
