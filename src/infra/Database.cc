#include "Database.h"

Database::Database(const string& connStr, size_t size)
    : _connStr(connStr)
{
    _pool.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        ConnectionWrapper item;
        item.conn = make_unique<connection>(_connStr);
        _pool.push_back(move(item));
    }
}

size_t Database::acquire() {
    unique_lock<mutex> lock(_mutex);

    _cv.wait(lock, [&]{
        for (const auto& item : _pool) {
            if (!item.used) return true;
        }
        return false;
    });

    for (size_t i = 0; i < _pool.size(); ++i) {
        if (!_pool[i].used) {
            _pool[i].used = true;
            return i;
        }
    }

    throw runtime_error("free connection not found((");
}

void Database::release(size_t inx) {
    lock_guard<mutex> lock(_mutex);
    _pool[inx].used = false;

    if (!_pool[inx].conn->is_open())
        _pool[inx].conn = make_unique<connection>(_connStr);

    _cv.notify_one();
}

Database::ConnectionGuard::ConnectionGuard(Database& db)
    : _db(&db), _inx(db.acquire())
{}

Database::ConnectionGuard::~ConnectionGuard() {
    if (_db) _db->release(_inx);
}

connection& Database::ConnectionGuard::conn() {
    return *(_db->_pool[_inx].conn);
}

Database::ConnectionGuard::ConnectionGuard(ConnectionGuard&& cg) noexcept
    : _db(cg._db), _inx(cg._inx)
{
    cg._db = nullptr;
}

Database::ConnectionGuard& Database::ConnectionGuard::operator=(ConnectionGuard&& cg) noexcept {
    if (this == &cg) return *this;

    if (_db) _db->release(_inx);
    _db = cg._db;
    _inx = cg._inx;
    cg._db = nullptr;
    return *this;
}
