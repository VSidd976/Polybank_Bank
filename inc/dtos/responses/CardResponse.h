#pragma once
#include <string>
using namespace std;

struct CardResponse {
    int cardId;
    int accountId;
    int clientId;
    string pin;
};
