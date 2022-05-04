#ifndef PROGRAMA_CLIENT_H
#define PROGRAMA_CLIENT_H

#include <iostream>

#include "times.h"
#include "date.h"
#include "util.h"
#include "name.h"

using namespace std;

class Client {
private:
    //client attributes
    string phoneNumber;
    Name fullName;
    Time callDuration;
    Time callStart;
    Date callDate;
public:
    //CONSTRUCTORS
    Client();
    Client(const long long& phoneNumber, const Name& name, const Time& callStart, const Time& callDuration, const Date& callDate);
    //GETTERS AND SETTERS
    string getPhoneNumber();
    Name getFullName();
    Time getCallStart();
    Time getCallDuration();
    Date getCallDate();
    void setData(const string& phoneNumber, const Name& name, const Time& callStart, const Time& callDuration, const Date& callDate);
    void setPhoneNumber(const string& phoneNumber);
    void setFullName(const Name& name);
    void setCallStart(const Time& callStart);
    void setCallDuration(const Time& callDuration);
    void setCallDate(const Date& callDate);
    //returns a string of the client data separated by |
    string toString();
    //OPERATORS
    Client& operator = (const Client& client);
    bool operator == (const Client& client);
    bool operator != (const Client& client);
    bool operator < (const Client& client);
    bool operator <= (const Client& client);
    bool operator > (const Client& client);
    bool operator >= (const Client& client);
};


#endif //PROGRAMA_CLIENT_H
