#pragma once
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using namespace std;

class Config {
public:
    static void load(const string&);
    static string dbUrl;
    static string jwtSecret;
    static int jwtExpire;
    static int port;
};
