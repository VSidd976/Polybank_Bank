#pragma once
#include "Database.h"
#include "AppContext.h"

class OperationsRepository {
public:
    explicit OperationsRepository();

    bool addOperation(
        optional<int>, optional<int>,
        double, const string&);

private:
    Database& _db;

};
