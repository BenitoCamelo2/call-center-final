#ifndef PROGRAMA_CLIENTLIST_H
#define PROGRAMA_CLIENTLIST_H

#include <iostream>
#include <string>
#include <fstream>

#include "clientnode.h"
#include "listexception.h"

using namespace std;

class ClientList {
private:
    //header and a couple functions
    ClientNode* header;
    //validates if a pos is valid
    bool isValidPos(ClientNode* clientNode);
    void copyAll(const ClientList& clientList);
public:
    //constructor, destructor
    ClientList();
    ClientList(ClientList& clientList);
    ~ClientList();
    //returs if list is empty
    bool isEmpty();
    //inserts data not ordered
    void insertData(ClientNode* clientNode, const Client& client);
    //inserts data ordered by phone number
    void insertOrdered(Client& client);
    //deletes a node in the list
    void deleteData(ClientNode* clientNode);
    //returns the header
    ClientNode* getFirstPos();
    //returns the last position in the list
    ClientNode* getLastPos();
    //returns the next position in the list
    static ClientNode* getNextPos(ClientNode* clientNode);
    //returns the position of a client
    ClientNode* retrievePos(Client& client, int searchBy);
    //returns the client of a position
    Client findData(ClientNode* clientNode);
    //returns a string of the list
    string toString();
    //deletes all the nodes in the list
    void deleteAll();
    //read-write to disk
    void writeToDisk(const string& fileName);
    ClientList* readFromDisk(const string& fileName);
};

enum{
    SEARCH_BY_PHONENUMBER = 1,
    SEARCH_BY_CALLDATE,
    SEARCH_BY_CALLSTART,
    SEARCH_BY_CALLDURATION,
};

enum{
    READ_PHONE_NUMBER = 0,
    READ_CALL_START,
    READ_CALL_DURATION,
    READ_CALL_DATE
};

enum{
    READ_YEAR = 0,
    READ_MONTH,
    READ_DAY
};

enum{
    READ_HOUR_CLIENT = 0,
    READ_MINUTE_CLIENT
};

#endif //PROGRAMA_CLIENTLIST_H
