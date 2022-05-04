#include "agentlist.h"
#include "listexception.h"
#include "agentmenu.h"
#include "util.h"

bool AgentList::isValidPos(AgentNode *agentNode) {
    AgentNode* temp(header);

    while(temp != nullptr){
        //if agent is found the position is valid
        if(temp == agentNode){
            return true;
        }
        temp = getNextPos(temp);
    }
    //in this case the agent is not in the list
    return false;
}

void AgentList::copyAll(const AgentList &agentList) {

}

AgentNode* AgentList::mergeName(AgentNode *first, AgentNode *second) {
    if(!first){
        return second;
    }

    if(!second){
        return first;
    }

    if(first->getData().getName() < second->getData().getName()){
        first->setNext(mergeName(first->getNext(), second));
        first->getNext()->setPrev(first);
        first->setPrev(nullptr);
        return first;
    } else {
        second->setNext(mergeName(first, second->getNext()));
        second->getNext()->setPrev(second);
        second->setPrev(nullptr);
        return second;
    }
}

AgentNode* AgentList::mergeSpecialty(AgentNode *first, AgentNode *second) {
    //if list is empty
    if(!first){
        return second;
    }

    //if there is only one element
    if(!second){
        return first;
    }

    //chooses which is greater
    if(first->getData().getSpecialty() < second->getData().getSpecialty()){
        first->setNext(mergeSpecialty(first->getNext(), second));
        first->getNext()->setPrev(first);
        first->setPrev(nullptr);
        return first;
    } else {
        second->setNext(mergeSpecialty(first, second->getNext()));
        second->getNext()->setPrev(second);
        second->setPrev(nullptr);
        return second;
    }
}

AgentNode* AgentList::mergeSort(AgentNode *head, int option) {
    if(!head || !head->getNext()){
        return head;
    }
    AgentNode* second = split(head);

    //recursive for left and right halves
    head = mergeSort(head, option);
    second = mergeSort(second, option);

    //return merged halves depending on name sort or specialty sort
    if(option == SORT_NAME){
        return mergeName(head, second);
    } else if (option == SORT_SPECIALTY){
        return mergeSpecialty(head, second);
    } else {
        return nullptr;
    }
}

AgentNode* AgentList::split(AgentNode *head) {
    AgentNode* fast(head);
    AgentNode* slow(head);

    //split list in half and return middle element
    while(fast->getNext() && fast->getNext()->getNext()){
        fast = fast->getNext()->getNext();
        slow = slow->getNext();
    }
    AgentNode* temp(slow->getNext());
    slow->setNext(nullptr);
    return temp;
}

AgentList::AgentList() : header(nullptr){}

AgentList::~AgentList() {
    deleteAll();
    delete header;
}

bool AgentList::isEmpty() {
    return header == nullptr;
}

void AgentList::insertData(AgentNode *agentNode, const Agent &tempAgent) {
    //position is invalid, will try to insert
    if(agentNode != nullptr && !isValidPos(agentNode)){
        throw ListException("Posicion invalida, tratando de insertar");
    }

    //first node to add to the list
    if(agentNode == nullptr){
        agentNode = header;
    }

    //temp node using the agent in the parameter as the data
    AgentNode* newOne(new AgentNode(tempAgent));

    //no more memory
    if(newOne == nullptr){
        throw ListException("Memoria no disponible, tratando de insertar");
    }

    //setters
    newOne->setNext(header);
    newOne->setPrev(nullptr);

    //if header is not the only item in the list
    if(header!=nullptr){
        header->setPrev(newOne);
    }
    header = newOne;
}

void AgentList::deleteData(AgentNode *agentNode) {
    AgentNode* temp(header);

    //if the agent wasn't found
    if(agentNode == nullptr){
        throw ListException("No existe el agente");
    //no elements in the list
    } else if(temp == nullptr){
        throw ListException("No hay agentes en la lista");
    }
    //if the element is the header
    if(temp == agentNode){
        header = header->getNext();
        free(agentNode);
        return;
    }
    //if the element is the last in the list
    if(agentNode == getLastPos()){
        temp = agentNode;
        temp = temp->getPrev();
        temp->setNext(nullptr);
        free(agentNode);
        return;
    }
    //when the node has a prev and next that are not nullptr, so in between two nodes
    if(agentNode != header && agentNode != getLastPos()) {
        while (temp != agentNode) {
            temp = getNextPos(temp);
        }
        if (temp == agentNode) {
            temp->getNext()->setPrev(temp->getPrev());
            temp->getPrev()->setNext(temp->getNext());
            free(agentNode);
        }
    }


}

AgentNode *AgentList::getFirstPos() {
    if(!isEmpty()){
        return header;
    } else {
        return nullptr;
    }
}

AgentNode *AgentList::getLastPos() {
    if(!isEmpty()) {
        AgentNode *temp;
        temp = header;
        while (temp != nullptr) {
            if(getNextPos(temp) == nullptr){
                return temp;
            } else {
                temp = getNextPos(temp);
            }
        }

    } else {
        return nullptr;
    }
    return nullptr;
}

AgentNode *AgentList::getPrevPos(AgentNode* agentNode) {
    return agentNode->getPrev();
}

AgentNode *AgentList::getNextPos(AgentNode* agentNode) {
    return agentNode->getNext();
}

AgentNode *AgentList::findData(Agent &agent, int option) {
    AgentNode* temp(header);

    //switch for what attribute to search by
    switch(option){
        //searching by code
        case SEARCH_CODE : {
            //basic way to traverse list
            while(temp != nullptr){
                if(temp->getData() == agent){
                    //if found returns the node in the list
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            //if not found returns nullptr
            return nullptr;
        }
        //searching by name
        case SEARCH_LAST_NAME: {
            //all of the cases use the same search method
            while(temp != nullptr){
                if(temp->getData().getName().getLastName() == agent.getName().getLastName()){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            return nullptr;
        }
        //search by shift start time
        case SEARCH_HOUR_START: {
            while(temp != nullptr){
                if(temp->getData().getStartTime().getHour() == agent.getStartTime().getHour()){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            return nullptr;
        }
        //search by shift end time
        case SEARCH_HOUR_END: {
            while(temp != nullptr){
                if(temp->getData().getEndTime().getHour() == agent.getEndTime().getHour()){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            return nullptr;
        }
        //search by extension
        case SEARCH_EXTENSION: {
            while(temp != nullptr){
                if(temp->getData().getExtension() == agent.getExtension()){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            return nullptr;
        }
        //search by specialty, should improve to show all agents with the same specialty
        case SEARCH_SPECIALTY: {
            while(temp != nullptr){
                if(temp->getData().getSpecialty() == agent.getSpecialty()){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            return nullptr;
        }
        //shouldn't happen, would be unfortunate
        default: {
            ListException("Error al buscar un agente");
            cin.ignore();
            cout << "Ingresa una tecla para continuar..." << endl;
            getchar();
        }
    }
    return nullptr;
}

Agent AgentList::retrieve(AgentNode *agentNode) {
    //searches through the list
    //could use the isValidPos(), but it returns a blank agent if node is not found, so its the same thing
    AgentNode* temp(header);
    while(temp != nullptr){
        if(temp == agentNode){
            return temp->getData();
        } else {
            temp = getNextPos(temp);
        }
    }
    return {};
}

void AgentList::sortByName() {
    header = mergeSort(getFirstPos(), SORT_NAME);
}

void AgentList::sortBySpecialty() {
    header = mergeSort(getFirstPos(), SORT_SPECIALTY);
}

string AgentList::toString() {
    AgentNode* temp(header);
    AgentNode* last(getLastPos());
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

void AgentList::deleteAll() {
    //deletes all while going through the list, temp gets the next element and prev deletes the previous element
    AgentNode* temp(header);
    AgentNode* prev;
    string tempString;
    while(temp != nullptr){
        prev = temp;
        temp = getNextPos(temp);
        tempString = prev->getData().getCode() + ".txt";
        remove(tempString.data());
        delete prev;
    }
    header = nullptr;
}

void AgentList::copyAll(AgentList* agentList){
    AgentNode* tempSender(agentList->header);
    Agent tempAgent;

    if(isEmpty()){
        return;
    }

    while(tempSender != nullptr){
        tempAgent = tempSender->getData();
        insertData(getFirstPos(), tempAgent);
        tempSender = tempSender->getNext();
    }
}

void AgentList::writeToDisk(const string &fileName) {
    ofstream file;

    file.open(fileName, ios::out);
    if(!file.is_open()){
        throw ListException("No se pudo abrir el archivo");
    } else {
        file << toString();
        file.close();
        AgentNode* temp(header);
        while(temp != nullptr){
            temp->getData().getClientList()->writeToDisk(temp->getData().getCode() + ".txt");
            temp = temp->getNext();
        }
    }
}

//reads agent and agents clients
AgentList* AgentList::readFromDisk(const string &fileName) {
    //agentList to return
    AgentList* tempAgentList = new AgentList();
    //clientlist used to assign to each agent, erased after every assignment
    ClientList* tempClientList = new ClientList();

    //temp string and file
    string tempLine;
    ifstream file(fileName);

    //not open, means agents dont exist, so creates a new file
    if(!file.is_open()){
        file.close();
        ofstream fileOpen(fileName, ios::out);
        fileOpen.close();
        return nullptr;
    }

    //here file exists, so we read it
    while(!file.eof()){
        Agent tempAgent;

        string code;
        string firstName, lastName;
        int hour, minute;
        int extension;
        int extraHours;
        int specialty;

        Name name;
        Time timeStart, timeEnd;

        //here if the first portion is empty, we assume the rest is empty, so we skip this line
        //this is in case of certain types of data loss
        getline(file, tempLine, '|');
        if(!tempLine.empty()) {
            //creation of the agent
            code = tempLine;

            getline(file, tempLine, ' ');
            firstName = tempLine;

            getline(file, tempLine, '|');
            lastName = tempLine;

            getline(file, tempLine, ':');
            hour = atoi(tempLine.data());
            getline(file, tempLine, '|');
            minute = atoi(tempLine.data());
            timeStart.setData(hour, minute);

            getline(file, tempLine, ':');
            hour = atoi(tempLine.data());
            getline(file, tempLine, '|');
            minute = atoi(tempLine.data());
            timeEnd.setData(hour, minute);

            getline(file, tempLine, '|');
            extension = atoi(tempLine.data());

            getline(file, tempLine, '|');
            extraHours = atoi(tempLine.data());

            getline(file, tempLine, '|');
            specialty = atoi(tempLine.data());

            getline(file, tempLine);

            name.setData(firstName, lastName);

            //set data to the agent, create the client list and then add the agent to the agent list
            tempAgent.setData(code, name, timeStart, timeEnd, extension, extraHours, specialty);
            tempClientList = tempClientList->readFromDisk(code + ".txt");
            if (tempClientList == nullptr) {
                tempClientList = new ClientList();
            }
            tempAgent.setClientList(tempClientList);

            tempAgentList->insertData(tempAgentList->getFirstPos(), tempAgent);
        }
    }
    return tempAgentList;
}
