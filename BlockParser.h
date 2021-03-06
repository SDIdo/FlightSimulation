//
// Created by roy on 12/22/18.
//

#ifndef PROJECTPART1_BLOCKPARSER_H
#define PROJECTPART1_BLOCKPARSER_H

#include <vector>
#include <string>
#include "CommandMap.h"
#include "SmallLexer.h"
#include "BigLexer.h"
#include "SymbolTable.h"
#include "Utilities.h"
#include "DataReaderServer.h"
#include "DataSender.h"

/**
 * This class is responsible for parsing blocks of script code.
 * A block parser can parse a given string vector and make commands which could execute.
 */
class BlockParser {
    CommandMap commandMap;
    SymbolTable *symbolTable;
    DataReaderServer *dataReaderServer;
    DataSender *dataSender;
    Utilities util;
public:
    void parse(vector<string> stringVector);
    BlockParser(SymbolTable* symbolTable, DataReaderServer *dataReaderServer, DataSender *);
};


#endif //PROJECTPART1_BLOCKPARSER_H
