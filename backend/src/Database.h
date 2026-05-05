#pragma once
#include <sqlite3.h>
#include <string>

class Database {
private:
    sqlite3* db;
    static Database* instance;
    Database();

public:
    static Database* getInstance();
    sqlite3* getDb();
    void inicializar();
    void fechar();
};