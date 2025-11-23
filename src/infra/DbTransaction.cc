#include "DbTransaction.h"

DbTransaction::DbTransaction(Database& db)
    : _guard(db), _tx(_guard.conn())
{}
