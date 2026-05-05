#include "Database.h"
#include <iostream>

Database* Database::instance = nullptr;

Database::Database() {
    int rc = sqlite3_open("manager_fc.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao abrir banco: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

Database* Database::getInstance() {
    if (instance == nullptr) {
        instance = new Database();
    }
    return instance;
}

sqlite3* Database::getDb() {
    return db;
}

void Database::inicializar() {
    if (!db) return;

    const char* sql =
        "CREATE TABLE IF NOT EXISTS times ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  nome TEXT NOT NULL,"
        "  cidade TEXT"
        ");"

        "CREATE TABLE IF NOT EXISTS jogadores ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  nome TEXT NOT NULL,"
        "  posicao TEXT,"
        "  habilidade INTEGER,"
        "  id_time INTEGER,"
        "  FOREIGN KEY (id_time) REFERENCES times(id)"
        ");"

        "CREATE TABLE IF NOT EXISTS partidas ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  time_casa TEXT NOT NULL,"
        "  time_visitante TEXT NOT NULL,"
        "  gols_casa INTEGER,"
        "  gols_visitante INTEGER,"
        "  data TEXT"
        ");"

        "CREATE TABLE IF NOT EXISTS progresso ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  temporada INTEGER DEFAULT 1,"
        "  rodada INTEGER DEFAULT 1"
        ");";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao criar tabelas: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Database::fechar() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}