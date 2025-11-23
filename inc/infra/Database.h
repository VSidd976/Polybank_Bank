#pragma once
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <pqxx/pqxx>
using namespace std;
using namespace pqxx;

class Database {
public:
    Database(const string&, size_t size = 5);

    class ConnectionGuard;

private:
    friend class ConnectionGuard;
    struct ConnectionWrapper;

    string _connStr;
    vector<ConnectionWrapper> _pool;
    mutex _mutex;
    condition_variable _cv;

    size_t acquire();
    void release(size_t);
};

class Database::ConnectionGuard {
public:
    explicit ConnectionGuard(Database&);
    ~ConnectionGuard();

    connection& conn();

    ConnectionGuard(const ConnectionGuard&) = delete;
    ConnectionGuard(ConnectionGuard&&) noexcept;
    ConnectionGuard& operator=(const ConnectionGuard&) = delete;
    ConnectionGuard& operator=(ConnectionGuard&&) noexcept;

private:
    Database* _db;
    size_t _inx;
};

struct Database::ConnectionWrapper {
    unique_ptr<connection> conn;
    bool used = false;
};
