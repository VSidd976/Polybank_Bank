#include "Database.h"

Database::Database(const string& connStr)
    : _connStr(connStr)
{
    connect();
}

connection& Database::getConn() {
    if (!isAlive()) connect();
    return *_conn;
}

bool Database::isAlive() const {
    return _conn && _conn->is_open();
}

void Database::connect() {
    _conn.reset();
    _conn = std::make_unique<pqxx::connection>(_connStr);
}
