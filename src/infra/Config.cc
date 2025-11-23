#include "Config.h"

string Config::dbUrl;
string Config::jwtSecret;
int Config::jwtExpire;
int Config::port;

void Config::load(const string& path) {
    ifstream f(path);
    nlohmann::json j;
    f >> j;

    dbUrl = j.at("db_url").get<string>();
    jwtSecret = j.at("jwt_secret").get<string>();
    jwtExpire = j.at("jwt_expire_sec").get<int>();
    port = j.at("port").get<int>();
}
