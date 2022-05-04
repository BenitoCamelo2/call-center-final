#include "clientlist.h"
#include "util.h"

bool ClientList::isValidPos(ClientNode *clientNode) {
    ClientNode* temp(header);
    //traverse the list, if found returns true, if not after the loop if returns false
    while(temp != nullptr){
        if(temp == clientNode){
            return true;
        }
        temp = getNextPos(temp);
    }
    return false;
}

ClientList::ClientList() :header(nullptr) { }

ClientList::ClientList(ClientList &clientList) {
    copyAll(clientList);
}

ClientList::~ClientList() {
    delete header;
}

bool ClientList::isEmpty() {
    return header == nullptr;
}

string ClientList::toString() {
    ClientNode* temp(header);
    ClientNode* last(getLastPos());
    string result;

    while(temp != nullptr){
        result += temp->getData().toString();
        if(temp != last) {
            result += "\n";
        }

        temp = getNextPos(temp);
    }
    return result;
}

void ClientList::insertData(ClientNode *clientNode, const Client &client) {
    //not valid position, still inserts
    if(clientNode != nullptr && !isValidPos(clientNode)){
        throw ListException("Posicion invalida, tratando de insertar");
    }

    //new node built on the client data
    ClientNode* newOne(new ClientNode(client));

    //no ram available
    if(newOne == nullptr){
        throw ListException("Memoria no disponible, tratando de insertar");
    }

    //if the position is null, means its the first item inserted in the list
    if(clientNode == nullptr){
        newOne->setNext(header);
        header = newOne;
    } else {
        newOne->setNext(clientNode->getNext());
        clientNode->setNext(newOne);
    }
}

void ClientList::insertOrdered(Client& client){
    ClientNode* aux(header);
    ClientNode* temp(nullptr);

    //when the client phone number is lower than the current position it breaks the loop and inserts the data
    while(aux != nullptr && client.getCallStart().getHour() >= aux->getData().getCallStart().getHour()/* && client.getCallStart().getMinute() <= aux->getData().getCallStart().getMinute()*/){
        temp = aux;
        aux = getNextPos(aux);
        if(aux != nullptr && client.getCallStart().getHour() == aux->getData().getCallStart().getHour()){
            temp = aux;
            aux = getNextPos(aux);
        }
    }

    insertData(temp, client);
}

void ClientList::deleteData(ClientNode *clientNode) {
    ClientNode* temp(header);
    ClientNode* trail(nullptr);

    //makes sure the position is valid
    if(isValidPos(clientNode)) {
        //this is executed when there is only one item in the list
        //temp == clientNode technically isn't necesary, since isValidPos makes sure its in the list
        //but just to make sure its there
        if (temp->getNext() == nullptr && temp == clientNode) {
            //basically creates a new list
            free(header);
            header = nullptr;
        //when there is multiple nodes in the list
        } else {
            //finds it and "deletes" it
            while (temp != nullptr) {
                if (temp == clientNode) {
                    trail->setNext(getNextPos(temp));
                    temp = nullptr;
                } else {
                    trail = temp;
                    temp = getNextPos(temp);
                }
            }
            delete temp;
        }
    //if the node is not valid
    } else {
        throw ListException("No existe el cliente");
    }
}

void ClientList::copyAll(const ClientList &clientList1) {
    ClientNode* temp1(clientList1.header);
    ClientNode* last(nullptr);
    ClientNode* newNode;

    while(temp1 != nullptr){
        newNode = new ClientNode(temp1->getData());

        if(newNode == nullptr){
            throw ListException("No memoria disponible, copyAll()");
        }

        if(last == nullptr){
            header = newNode;
        } else {
            last->setNext(newNode);
        }

        last = newNode;
        temp1 = temp1->getNext();
    }
}

ClientNode *ClientList::getFirstPos() {
    if(!isEmpty()){
        return header;
    } else {
        return nullptr;
    }
}

ClientNode *ClientList::getLastPos() {
    //basic search of list, returns null if not found
    ClientNode* temp;
    temp = header;
    if(!isEmpty()){
        if(getNextPos(temp) == nullptr){
            return temp;
        } else {
            while(temp != nullptr){
                if(getNextPos(temp) == nullptr){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
        }
    }
    return nullptr;
}

ClientNode *ClientList::getNextPos(ClientNode* clientNode) {
    return clientNode->getNext();
}

ClientNode *ClientList::retrievePos(Client& client, int searchBy) {
    ClientNode* temp;
    ClientNode* last;

    last = getLastPos();
    temp = header;
    //depending on searchBy, it will search by the specified attribute
    switch(searchBy){
        case SEARCH_BY_PHONENUMBER:{
            if(temp == last){
                if(temp->getData().getPhoneNumber() == client.getPhoneNumber()){
                    return temp;
                } else {
                    return nullptr;
                }
            } else {
                do{
                    if(temp->getData().getPhoneNumber() == client.getPhoneNumber()){
                        return temp;
                    }
                    temp = getNextPos(temp);
                }while(temp != nullptr);
            }
            return nullptr;
        }
        case SEARCH_BY_CALLDATE:{
            Date tempDate = client.getCallDate();
            if(temp == last){
                if(temp->getData().getCallDate().operator==(tempDate)){
                    return temp;
                } else {
                    return nullptr;
                }
            } else {
                do{
                    if(temp->getData().getCallDate().operator==(tempDate)){
                        return temp;
                    }
                    temp = getNextPos(temp);
                }while(temp != nullptr);
            }
            return nullptr;
        }
        case SEARCH_BY_CALLSTART:{
            Time callStart = client.getCallStart();
            if(temp == last){
                if(temp->getData().getCallStart().operator==(callStart)){
                    return temp;
                } else {
                    return nullptr;
                }
            } else {
                do{
                    if(temp->getData().getCallStart().operator==(callStart)){
                        return temp;
                    }
                    temp = getNextPos(temp);
                }while(temp != nullptr);
            }
            return nullptr;
        }
        case SEARCH_BY_CALLDURATION:{
            Time callDuration = client.getCallDuration();
            if(temp == last){
                if(temp->getData().getCallDuration().operator==(callDuration)){
                    return temp;
                } else {
                    return nullptr;
                }
            } else {
                do{
                    if(temp->getData().getCallDuration().operator==(callDuration)){
                        return temp;
                    }
                    temp = getNextPos(temp);
                }while(temp != nullptr);
            }
            return nullptr;
        }
        default: {
            cout << "Presiona enter para continuar..." << endl;
            getchar();
            break;
        }
    }
    //returns nullptr if not found
    return nullptr;

}

Client ClientList::findData(ClientNode *clientNode) {
    ClientNode* temp(header);
    ClientNode* last(getLastPos());

    //not sure why the phoneNumber is 0, it works so i dont want to remove it
    Client tempClient;
    //basic search, if its not in the list it prints doesn't exist
    if(isValidPos(clientNode)) {
        if (temp == last) {
            if (temp == clientNode) {
                return temp->getData();
            } else {
                return tempClient;
            }
        } else {
            while (temp != nullptr) {
                if (temp == clientNode) {
                    return temp->getData();
                }
                temp = getNextPos(temp);
            }
        }
        return tempClient;
    } else {
        throw ListException("Cliente no existe");
    }
}

void ClientList::deleteAll() {
    //goes throught the list, temp gets the next position and trail deletes the previous position
    ClientNode* temp;
    ClientNode* trail;
    ClientNode* last;

    last = getLastPos();
    temp = header;
    trail = nullptr;
    if(temp == last){
        delete temp;
        header = new ClientNode();
    } else {
        while(temp != nullptr){
            trail = temp;
            temp = getNextPos(temp);
            delete trail;
        }
        delete temp;
    }
}

void ClientList::writeToDisk(const string& fileName) {
    ofstream file;
    file.open(fileName, ios::out);
    if(!file.is_open()){
        throw ListException("No se pudo abrir o crear el archivo");
    } else {
        file << toString();
        file.close();
    }
}

ClientList* ClientList::readFromDisk(const string& fileName) {
    ClientList* tempClientList = new ClientList();

    string tempLine;
    ifstream file(fileName);

    if(!file.is_open()){
        return nullptr;
    }

    while(!file.eof()){
        Client tempClient;

        string phoneNumber, firstName, lastName;
        int yearCall, monthCall, dayCall;
        int hourCall, minuteCall;

        Name fullName;
        Date callDate;
        Time callStart, callDuration;

        getline(file, tempLine, '|');
        if(!tempLine.empty()) {
            phoneNumber = tempLine;

            getline(file, tempLine, ' ');
            firstName = tempLine;
            getline(file, tempLine, '|');
            lastName = tempLine;
            fullName.setData(firstName, lastName);

            getline(file, tempLine, ':');
            hourCall = atoi(tempLine.data());
            getline(file, tempLine, '|');
            minuteCall = atoi(tempLine.data());
            callStart.setData(hourCall, minuteCall);

            getline(file, tempLine, ':');
            hourCall = atoi(tempLine.data());
            getline(file, tempLine, '|');
            minuteCall = atoi(tempLine.data());
            callDuration.setData(hourCall, minuteCall);

            getline(file, tempLine, '/');
            dayCall = atoi(tempLine.data());
            getline(file, tempLine, '/');
            monthCall = atoi(tempLine.data());
            getline(file, tempLine);
            yearCall = atoi(tempLine.data());
            callDate.setData(yearCall, monthCall, dayCall);

            tempClient.setData(phoneNumber, fullName, callStart, callDuration, callDate);
            tempClientList->insertOrdered(tempClient);
        }
    }
    return tempClientList;
}
