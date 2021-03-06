#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <thread>
#include "BigLexer.h"
#include "SmallLexer.h"
#include "DataReaderServer.h"
#include "LineParser.h"
#include "SymbolTable.h"
#include "BlockParser.h"
#include "DataSender.h"
#include <fstream>

using namespace std;

// create mutex lock.
mutex mutex1;

void shared_print(string toPrint) {
    mutex1.lock();
    cout << toPrint << endl;
    mutex1.unlock();
}

void *pthreadFunc(void *arg) {
    int *idPtr = (int *) arg;
    int id = *idPtr;
    for (int i = 0; i < 1000; i++) {
        if (id == 1) {
            shared_print("hello, this is the NUMBER ONE thread");
        } else {
            shared_print("i am not the number one...");
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    pthread_exit(nullptr); // the thread which runs this func finishes.
}

/**
 * Shared memory try.
 * @param toPrint
 */

//void sharedMemory(map<string, double> *mapy, double id, string toPut) {
//
////    mutex1.lock();
//    mapy->insert(pair<string, double>("this", id));
//    cout << to_string(mapy->at("this")) + "\n";
////    mutex1.unlock();
//}
//
//void *pthreadFunc2(void *arg) {
//    map<string, double> mapy;
//    int *idPtr = (int *) arg;
//    double id = *idPtr;
//    mutex1.lock();
//    for (int i = 0; i < 100; i++) {
//        if (id == 1) {
//            sharedMemory(&mapy, 1);
//        } else {
//            sharedMemory(&mapy, 2);
//        }
//    }
//    mutex1.unlock();
//
//
//    pthread_exit(nullptr); // the thread which runs this func finishes.
//}


int main(int argc, char *argv[]) {

    /**
     * Pthread try:
     *  this try is using mutex in order to lock data usage from other threads.
     */

//    // create 1st thread
//    pthread_t threadID;
//    pthread_attr_t attr;
//    pthread_attr_init(&attr);
//    int valueForFunc = 1;
//    pthread_create(&threadID, &attr, pthreadFunc2, &valueForFunc);
//
//    // create 2nd thread
//    pthread_t thread2ID;
//    pthread_attr_t attr2;
//    pthread_attr_init(&attr2);
//    int secondValue = 2;
//    pthread_create(&thread2ID, &attr2, pthreadFunc2, &secondValue);
//
//    pthread_join(threadID, nullptr); // wait for thread to join.
//    pthread_join(thread2ID, nullptr); // wait for thread to join.


/**
 * 2nd Pthread try:
 * this try is trying to use thread on a class method.
 */

//    DataReaderServer dataReaderServer;
//    dataReaderServer.threadListen();

    /**
     * Lexer try:
     */
//    BigLexer lexer1;
//    string str;
//    vector<string> vec;
//    while (true) {
//        getline(cin, str); // client input will be sent to lexer function to receive string array.
//        vec = lexer1.lexer(str);
//        for (int i = 0; i < vec.size(); i++) {
//            cout << vec.at(i) << "\n";
//        }
//    }

//    SmallLexer lexer1;
//    string str;
//    vector<string> vec;
//    while (true) {
//        getline(cin, str); // client input will be sent to lexer function to receive string array.
//        vec = lexer1.lexer(str);
//        for (int i = 0; i < vec.size(); i++) {
//            cout << vec.at(i) << "\n";
//        }
//    }

/**
 * "REAL" main for sending commands.
 * this main simulates the real main used for the flight simulator.
 */

//    SymbolTable st;
//    LineParser lineParser(&st); // parser gets a pointer to the shared symbol table.
//    BlockParser blockParser(&st); // block parser gets a pointer to the shared symbol table.
//    BigLexer bl;
//    string userInput;
//    vector<string> stringVector;
//
//    while (true) {
//        getline(cin, userInput);
//        stringVector = bl.lexer(userInput);
//
//        // if the user wants to exit the process.
//        if (userInput == "exit") {
//            break;
//        }
//            // if command is block command.
//        else if (stringVector.at(0) == "while" || stringVector.at(0) == "if") {
//            string blockString = userInput.substr(0, userInput.length() - 2); // exclude curly bracket.
//            // get all of the user input until the end of the if/while statement.
//            int openedBrackets = 1;
//            while (openedBrackets != 0) {
//                getline(cin, userInput);
//                if (userInput.back() == '}') {
//                    openedBrackets -= 1;
//                    continue;
//                } else if (userInput.back() == '{') {
//                    openedBrackets += 1;
//                }
//                blockString += userInput;
//            }
//
//            stringVector = bl.lexer(blockString);
//            blockParser.parse(stringVector);
//        }
//            // command was a line command.
//        else {
//            lineParser.parse(bl.lexer(userInput), 0);
//        }
//    }




/**
 * "REAL" main for sending command - WITH FILEEE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * this main simulates the real main used for the flight simulator.
 */
    SymbolTable st;
    DataReaderServer dataReaderServer;
    DataSender dataSender;
    LineParser lineParser(&st, &dataReaderServer, &dataSender); // parser gets a pointer to the shared symbol table and DRS
    BlockParser blockParser(&st, &dataReaderServer, &dataSender); // block parser gets pointers to the shared symbol table and DRS
    BigLexer bl;
    string userInput;
    vector<string> stringVector;
    bool fromFile = false;
    string line;
    ifstream myFile(argv[1]);
    if (argc == 2) {
//        ifstream myFile(argv[1]);
        if (myFile.is_open()) {
            fromFile = true;
        }
    }
    while (true) {
        if (fromFile) {
            if (getline(myFile, line)) {
                userInput = line;
            } else {
                break;
            }
        }
        if (!fromFile) {
            getline(cin, userInput);
        }
        stringVector = bl.lexer(userInput);

        // if the user wants to exit the process.
        if (userInput == "exit") {
            break;
        }
            // if command is block command.
        else if (stringVector.at(0) == "while" || stringVector.at(0) == "if") {
            string blockString = userInput.substr(0, userInput.length() - 2); // exclude curly bracket.
            // get all of the user input until the end of the if/while statement.
            int openedBrackets = 1;
            while (openedBrackets != 0) {
                if (fromFile) {
                    if (getline(myFile, line)) {
                        userInput = line;
                    } else {
                        break;
                    }
                }
                if (!fromFile) {
                    getline(cin, userInput);
                }
                if (userInput.back() == '}') {
                    openedBrackets -= 1;
                    continue;
                } else if (userInput.back() == '{') {
                    openedBrackets += 1;
                }
                blockString += " " + userInput;
            }
            vector<string> lexedVec1 = bl.lexer(blockString);

            stringVector = bl.lexer(blockString);
            blockParser.parse(stringVector);
        }
            // command was a line command.
        else {
            cout << "user *Line Command input* is :" << userInput << endl;
            vector<string> lexedVec = bl.lexer(userInput);
            lineParser.parse(bl.lexer(userInput), 0);
        }
    }
    if (fromFile) {
        myFile.close();
    }

/**
 * Test with Ido (worked open server).
 *
 * And now also the client can connect to the flight simulator with it's own pthread.
 * After it connects it can send commands to the simulator.
 */

//    DataReaderServer dataReaderServer;
//    pthread_t t1ID;
//    pthread_create(&t1ID, NULL, &DataReaderServer::runOpen, &dataReaderServer);
//
//    dataReaderServer.set("5402", "10");
//
//    // unconnected print...
//    cout << "parallel activity" << endl;
//
//    DataSender dataSender;
//    pthread_t t2ID;
//    pthread_create(&t2ID, NULL, &DataReaderServer::runOpen, &dataSender);
//
//    sleep(18);
//
//    dataSender.set("127.0.0.1", "5401");
//    dataSender.openPipe();
//
//    sleep(18);
//    dataSender.sendCommand("ls");
//
//    // unconnected print...
//    cout << "parallel activity" << endl;
//
//    pthread_join(t1ID, nullptr); // wait for thread to join.
//    pthread_join(t2ID, nullptr); // wait for thread to join.


    return 0;
}