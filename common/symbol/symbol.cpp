#include "symbol.h"
#include <string>

symbol::symbol() {
    this->idName = "";
    this->idType = symbolType::integer;
}

symbol::symbol(std::string idName, symbolType idType) {
    this->idName = idName;
    this->idType = idType;
}

const std::string symbol::getIdName() {
    return this->idName;
}

symbolType& symbol::getIdType() {
    return this->idType;
}

symbol* SymbolTable::findInThisTable(const std::string name) {
    std::unordered_map<std::string, symbol*>::iterator iter;
    iter = this->symbolHashTable.find(name);
    if (iter != this->symbolHashTable.end()) return iter->second;
    else return NULL;
}

SymbolTable::SymbolTable() {
    this->childTable = NULL;
    this->parentTable = NULL;
}

SymbolTable::SymbolTable(SymbolTable* parent) {
    this->childTable = NULL;
    this->parentTable = parent;
    parent->setChild(this);
}

symbol* SymbolTable::findSymbol(std::string name) {
    SymbolTable* t = this;
    while (t != NULL) {
        symbol* target = t->findInThisTable(name);
        if (target == NULL) {
            // Not found in current table, goto parent table.
            t = t->parentTable;
        } else {
            return target;
        }
    }
    return NULL;
}

int SymbolTable::addSymbol(symbol* symbol) {
    if (this->findInThisTable(symbol->getIdName()) == NULL) {
        this->symbolHashTable[symbol->getIdName()] = symbol;
        return SUCCESS;
    }
    else return FAIL;
}