#pragma once
#include <string>
#include <pqxx/pqxx>
using namespace std;
using namespace pqxx;

class Database {
public:
    explicit Database(const string&);

    connection& getConn();

private:
    string _connStr;
    unique_ptr<connection> _conn;

    bool isAlive() const;
    void connect();

};
