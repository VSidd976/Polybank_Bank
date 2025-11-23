#pragma once
#include <jwt-cpp/jwt.h>
#include <chrono>
using namespace std;

class JwtUtils {
public:
    static void setSecret(const string&);
    static void setExpires(int);

    static string generateToken(const int, const int, const int);
    static bool verifyToken(const string&, int&, int&, int&);

private:
    static string _secretKey;
    static int _expiresSec;

};
