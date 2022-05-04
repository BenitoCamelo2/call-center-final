#include "client.h"

Client::Client() {
    phoneNumber = "";
    fullName = Name();
    callStart = Time();
    callDuration = Time();
    callDate = Date();
}

Client::Client(const long long &phoneNumber, const Name &name, const Time &callStart, const Time &callDuration, const Date &callDate) {
    this->phoneNumber = phoneNumber;
    this->fullName = name;
    this->callStart = callStart;
    this->callDuration = callDuration;
    this->callDate = callDate;
}

string Client::getPhoneNumber() {
    return phoneNumber;
}

Name Client::getFullName() {
    return fullName;
}

Time Client::getCallStart() {
    return callStart;
}

Time Client::getCallDuration() {
    return callDuration;
}

Date Client::getCallDate() {
    return callDate;
}

void Client::setData(const string &phoneNumber, const Name &name, const Time &callStart, const Time &callDuration, const Date &callDate) {
    this->phoneNumber = phoneNumber;
    this->callStart = callStart;
    this->callDuration = callDuration;
    this->callDate = callDate;
    this->fullName = name;
}

void Client::setPhoneNumber(const string &phoneNumber) {
    this->phoneNumber = phoneNumber;
}

void Client::setFullName(const Name &name){
    this->fullName = name;
}

void Client::setCallStart(const Time &callStart) {
    this->callStart = callStart;
}

void Client::setCallDuration(const Time &callDuration) {
    this->callDuration = callDuration;
}

void Client::setCallDate(const Date &callDate) {
    this->callDate = callDate;
}

string Client::toString(){
    string result;

    result = phoneNumber;
    result += "|";
    result += fullName.toString();
    result += "|";
    result += callStart.toString();
    result += "|";
    result += callDuration.toString();
    result += "|";
    result += callDate.toString();

    return result;

}

Client &Client::operator = (const Client &client) {
    phoneNumber = client.phoneNumber;
    fullName = client.fullName;
    callStart = client.callStart;
    callDuration = client.callDuration;
    callDate = client.callDate;

    return *this;
}

bool Client::operator == (const Client &client) {
    return phoneNumber == client.phoneNumber;
}

bool Client::operator != (const Client &client) {
    return phoneNumber != client.phoneNumber;
}

bool Client::operator < (const Client &client) {
    return phoneNumber < client.phoneNumber;
}

bool Client::operator <= (const Client &client) {
    return phoneNumber <= client.phoneNumber;
}

bool Client::operator > (const Client &client) {
    return phoneNumber > client.phoneNumber;
}

bool Client::operator >= (const Client &client) {
    return phoneNumber >= client.phoneNumber;
}
