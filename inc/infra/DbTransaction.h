#pragma once
#include "Database.h"

class DbTransaction {
public:
    explicit DbTransaction(Database&);

    work& tx() { return _tx; }
    void commit() { _tx.commit(); }

private:
    Database::ConnectionGuard _guard;
    work _tx;
};
