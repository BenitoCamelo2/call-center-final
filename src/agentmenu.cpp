#include "agentmenu.h"
#include "clientmenu.h"
#include "util.h"

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

AgentMenu::AgentMenu(AgentList* agentList, int *changesMade): agentListRef(agentList) {
    changesMadeRef = changesMade;
    mainAgentMenu();
}


void AgentMenu::enterToContinue() {
    cout << "Presione enter para continuar..." << endl;
    getchar();
}

void AgentMenu::addAgent() {
    //temp variables to add to the agent variable, then to add to the list
    Agent tempAgent;
    string codeSTR, firstName, lastName;
    Name name;
    Time startTime, endTime;
    int extension, extraHours, specialty, tempHour, tempMinute, codeINT;
    char option;

    system(CLEAR);
    cout << "AGREGAR AGENTE" << endl;

    //code, verify as int then assign to str
    cout << "Codigo: ";
    cin >> codeINT;
    while(!verifyINT(1, -1, codeINT)){
        cout << "Ingresa un numero mayor a 0: ";
        cin >> codeINT;
    }
    codeSTR = to_string(codeINT);

    //first name
    cout << "Primer nombre: ";
    cin.ignore();getline(cin, firstName);

    //last name
    cout << "Apellido: ";
    getline(cin, lastName);
    name.setData(firstName, lastName);

    //hour of when shift starts
    cout << "Hora de inicio de horario: ";
    cin >> tempHour;

    //minute of when shift starts
    cout << "Minuto de  de horario: ";
    cin >> tempMinute;

    while(!startTime.setData(tempHour, tempMinute)){
        cout << "Ingresa la hora de nuevo: ";
        cin >> tempHour;
        cout << "Ingresa el minuto de nuevo: ";
        cin >> tempMinute;
    }


    //hour of when shift ends
    cout << "Hora de fin de horario: ";
    cin >> tempHour;
    //minute of when shift ends
    cout << "Minuto de fin de horario: ";
    cin >> tempMinute;

    while(!endTime.setData(tempHour, tempMinute)){
        cout << "Ingresa la hora de nuevo: ";
        cin >> tempHour;
        cout << "Ingresa el minuto de nuevo: ";
        cin >> tempMinute;
    }

    //extension
    cout << "Extension: ";
    cin >> extension;
    while(!verifyINT(1, -1, extension)){
        cout << "Ingresa de nuevo mayor o igual a 1: ";
        cin >> extension;
    }

    //extra hours
    cout << "Horas extras: ";
    cin >> extraHours;
    while(!verifyINT(0, -1, extraHours)){
        cout << "Ingresa de nuevo mayor o igual a 0: ";
        cin >> extraHours;
    }

    //specialty
    cout << "Especialidad (1, 2, 3, 4, 5, 6): ";
    cin >> specialty;
    while(!verifyINT(1, 6, specialty)){
        cout << "Ingresa un valor de 1 a 6: ";
        cin >> specialty;
    }

    cout << "Guste agregar clientes al agente? (S/N): ";
    cin >> option;

    if(option == 's' || option == 'S'){
        new ClientMenu(tempAgent.getClientList(), changesMadeRef);
    }

    tempAgent.setData(codeSTR, name, startTime, endTime, extension, extraHours, specialty);
    agentListRef->insertData(agentListRef->getFirstPos(), tempAgent);
}

void AgentMenu::deleteAgent() {
    //agent variable to save to search for its position and then delete using that position
    Agent tempAgent;
    AgentNode* agentNode;
    //only searches by code
    string code;
    bool terminate = false;
    int n;

    system(CLEAR);
    cout << "ELIMINAR AGENTE" << endl << endl;
    printAgents('\0', 0);
    cout << "Ingresa el codigo del agente que desea eliminar: ";
    cin.ignore();getline(cin, code);
    //while loop to make sure the code entered is valid
    do {
        tempAgent.setCode(code);
        agentNode = agentListRef->findData(tempAgent, SEARCH_CODE);
        if (agentNode == nullptr) {
            cout << "Ingresa de nuevo porfavor (0 para cancelar): " << endl;
            getline(cin, code);
            if(code == "0"){
                return;
            }
        } else {
            terminate = true;
        }
    }while(!terminate);

    code += ".txt";

    std::remove(code.data());
    //deletes the node
    agentListRef->deleteData(agentNode);

}

void AgentMenu::modifyAgent() {
    //same theory as deleteAgent()
    bool terminate = false;
    AgentNode* temp;
    string agentCode;
    Agent tempAgent;

    //chose agent to modify
    system(CLEAR);
    cout << "MODIFICAR AGENTE" << endl;
    printAgents('\0', 0);
    cout << "Ingresa el codigo: ";
    cin.ignore();getline(cin, agentCode);
    tempAgent.setCode(agentCode);
    //makes sure the code entered is valid
    while(!terminate){
        temp = agentListRef->findData(tempAgent, SEARCH_CODE);
        if(temp == nullptr){
            cout << "Ingresa de nuevo: ";
            getline(cin, agentCode);
            tempAgent.setCode(agentCode);
        } else {
            terminate = true;
        }
    }

    tempAgent = agentListRef->retrieve(temp);

    terminate = false;
    //while loop to modify any attribute
    do{
        system(CLEAR);
        cout << "MODIFICANDO " << tempAgent.getName().getFirstName() << endl;
        int option = 0;
        cout << "Modificar: " << endl;
        cout << "1. Codigo" << endl;
        cout << "2. Nombre" << endl;
        cout << "3. Hora de inicio de jornada" << endl;
        cout << "4. Hora de fin de jornada" << endl;
        cout << "5. Extension" << endl;
        cout << "6. Horas extras" << endl;
        cout << "7. Especialidad" << endl;
        cout << "8. Clientes" << endl;
        cout << "9. Regresar" << endl;
        cout << "Opcion: ";
        cin >> option;
        switch(option){
            case MODIFY_CODE: {
                int codeINT;
                string codeSTR;

                cout << "Ingresa el codigo nuevo: ";
                cin >> codeINT;

                while (!verifyINT(1, -1, codeINT)) {
                    cout << "Ingresa de nuevo: ";
                    cin >> codeINT;
                }
                codeSTR = to_string(codeINT);
                tempAgent.setCode(codeSTR);
                break;
            }
            case MODIFY_NAME: {
                string firstName, lastName;
                Name name;

                cout << "Ingresa el primero nombre: ";
                cin.ignore();getline(cin, firstName);
                cout << "Ingresa su apellido: ";
                getline(cin, lastName);
                name.setData(firstName, lastName);

                tempAgent.setName(name);
                break;
            }
            case MODIFY_START_TIME: {
                int hour, minute;
                Time startTime;

                cout << "Ingresa la hora: ";
                cin >> hour;
                cout << "Ingresa el minuto: ";
                cin >> minute;

                while(!startTime.setData(hour, minute)){
                    cout << "Ingresa la hora de nuevo: ";
                    cin >> hour;
                    cout << "Ingresa el minuto de nuevo: ";
                    cin >> minute;
                }

                tempAgent.setStartTime(startTime);
                break;
            }
            case MODIFY_END_TIME: {
                int hour, minute;
                Time endTime;

                cout << "Ingresa la hora: ";
                cin >> hour;
                cout << "Ingresa el minuto: ";
                cin >> minute;

                while(!endTime.setData(hour, minute)){
                    cout << "Ingresa la hora de nuevo: ";
                    cin >> hour;
                    cout << "Ingresa el minuto de nuevo: ";
                    cin >> minute;
                }

                tempAgent.setEndTime(endTime);
                break;
            }
            case MODIFY_EXTENSION: {
                int extension;

                cout << "Ingresa la extension: ";
                cin >> extension;
                while(!verifyINT(1,-1,extension)){
                    cout << "Ingresa de nuevo: ";
                    cin >> extension;
                }

                tempAgent.setExtension(extension);
                break;
            }
            case MODIFY_EXTRA_HOURS: {
                int extraHours;

                cout << "Ingresa las horas extras a sumar: ";
                cin >> extraHours;
                while(!verifyINT(0,-1,extraHours)){
                    cout << "Ingresa de nuevo: ";
                    cin >> extraHours;
                }

                tempAgent.addExtraHours(extraHours);
                break;
            }
            case MODIFY_SPECIALTY: {
                int specialty;

                cout << "Ingresa la especialidad: ";
                cin >> specialty;
                while(!verifyINT(1,6,specialty)){
                    cout << "Ingresa de nuevo: ";
                    cin >> specialty;
                }
                tempAgent.setSpecialty(specialty);
                break;
            }
            case MODIFY_CLIENTS: {
                new ClientMenu(tempAgent.getClientList(), changesMadeRef);
                break;
            }
            case EXIT_MODIFY: {
                temp->setData(tempAgent);
                terminate = true;
                break;
            }
            default: {
                cout << "Opcion invalida" << endl;
                cin.ignore();
                enterToContinue();
            }
        }
    }while(!terminate);
}

void AgentMenu::searchAgent() {
    bool terminate = false;

    //chose what to search by
    do{
        int option = 0;
        system(CLEAR);
        cout << "BUSCAR AGENTE" << endl;
        cout << "Buscar por: " << endl;
        cout << "1. Codigo" << endl;
        cout << "2. Apellido" << endl;
        cout << "3. Hora de inicio de horario" << endl;
        cout << "4. Hora de fin de horario" << endl;
        cout << "5. Extension" << endl;
        cout << "6. Especialidad" << endl;
        cout << "7. Regresar" << endl;
        cout << "Opcion: ";
        cin >> option;
        switch(option){
        //search options
            case SEARCH_CODE: {
                int codeINT;
                string codeSTR;
                Agent tempAgent;

                cout << "Ingresa un codigo: ";
                cin >> codeINT;
                while(!verifyINT(1,-1,codeINT)){
                    cout << "Ingresa de nuevo: ";
                    cin >> codeINT;
                }
                codeSTR = to_string(codeINT);
                tempAgent.setCode(codeSTR);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_CODE));
                cin.ignore();enterToContinue();
                break;
            }
            case SEARCH_LAST_NAME: {
                string lastName, firstName;
                Name name;
                Agent tempAgent;

                cout << "Ingresa el apellido: ";
                cin.ignore();getline(cin, lastName);
                name.setData(firstName, lastName);
                tempAgent.setName(name);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_LAST_NAME));
                enterToContinue();
                break;
            }
            case SEARCH_HOUR_START: {
                int hour, minute=0;
                Time time;
                Agent tempAgent;

                cout << "Ingresa la hora de inicio: ";
                cin >> hour;

                while(!time.setData(hour, minute)){
                    cout << "Ingresa la hora de nuevo: ";
                    cin >> hour;
                }
                tempAgent.setStartTime(time);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_HOUR_START));
                cin.ignore();enterToContinue();
                break;
            }
            case SEARCH_HOUR_END: {
                int hour, minute=0;
                Time time;
                Agent tempAgent;

                cout << "Ingresa la hora de fin: ";
                cin >> hour;

                while(!time.setData(hour, minute)){
                    cout << "Ingresa la hora de nuevo: ";
                    cin >> hour;
                }
                tempAgent.setEndTime(time);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_HOUR_END));
                cin.ignore();enterToContinue();
                break;
            }
            case SEARCH_EXTENSION: {
                int extension;
                Agent tempAgent;

                cout << "Ingresa la extension: ";
                cin >> extension;
                while(!verifyINT(0, -1, extension)){
                    cout << "Ingresa de nuevo: ";
                    cin >> extension;
                }
                tempAgent.setExtension(extension);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_EXTENSION));
                cin.ignore();enterToContinue();
                break;
            }
            case SEARCH_SPECIALTY: {
                int specialty;
                Agent tempAgent;

                cout << "Ingresa la especialidad: ";
                cin >> specialty;
                while(!verifyINT(1, 6, specialty)){
                    cout << "Ingresa de nuevo: ";
                    cin >> specialty;
                }

                tempAgent.setSpecialty(specialty);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_SPECIALTY));
                cin.ignore();enterToContinue();
                break;
            }
            case EXIT_SEARCH: {
                terminate = true;
                break;
            }
            default: {
                cout << "Seleccione una opcion valida" << endl;
                cin.ignore();
                enterToContinue();
            }
        }
    }while(!terminate);
}

void AgentMenu::sortAgents() {
    bool terminate = false;
    int option = 0;

    do{
        system(CLEAR);
        cout << "ORGANIZAR AGENTES" << endl;
        cout << "1. Por nombre" << endl;
        cout << "2. Por especialidad" << endl;
        cout << "3. Regresar" << endl;
        cout << "Opcion: ";
        cin >> option;
        switch(option){
            case SORT_NAME: {
                agentListRef->sortByName();
                terminate = true;
                break;
            }
            case SORT_SPECIALTY: {
                agentListRef->sortBySpecialty();
                terminate = true;
                break;
            }
            case EXIT_SORT: {
                terminate = true;
                break;
            }
            default: {
                cout << "seleccione una opcion valida" << endl;
                getchar();
                enterToContinue();
            }
        }
    }while(!terminate);
}

void AgentMenu::printAgent(AgentNode* agentNode) {
    cout << "|" << agentNode->getData().getName().toString();
    cout.width(30 - agentNode->getData().getName().toString().size());
    cout << "|" << agentNode->getData().getCode();
    cout.width(20 - agentNode->getData().getCode().size());
    cout << "|";
    switch(agentNode->getData().getSpecialty()){
        case SERVIDORES: {
            cout << "Servidores         ";
            break;
        }
        case ESCRITORIO: {
            cout << "Escritorio         ";
            break;
        }
        case PORTATILES: {
            cout << "Portatiles         ";
            break;
        }
        case LINUX: {
            cout << "Linux              ";
            break;
        }
        case IMPRESORAS: {
            cout << "Impresoras         ";
            break;
        }
        case REDES: {
            cout << "Redes              ";
            break;
        }
        default: {
            cout << "ERROR";
            break;
        }
    }
    cout << "|" << agentNode->getData().getStartTime().toString();
    cout << " - " << agentNode->getData().getEndTime().toString();
    cout << "|" << agentNode->getData().getExtraHours();
    cout.width(20 - countDigits(agentNode->getData().getExtraHours()));
    cout << "|" << endl;
}

void AgentMenu::printClient(ClientNode* clientNode){
    //prints data in this structure:
    //|PhoneNumber|CallDate|CallStart|CallDuration|
    //can always build it some day to calculate when the call ended
    cout << "|" << clientNode->getData().getPhoneNumber();
    cout.width(20 - clientNode->getData().getPhoneNumber().length());
    cout << "|" << clientNode->getData().getFullName().toString();
    cout.width(30 - clientNode->getData().getFullName().toString().length());
    cout << "|" << clientNode->getData().getCallDate().toString();
    cout.width(20 - clientNode->getData().getCallDate().toString().length());
    cout << "|" << clientNode->getData().getCallStart().toString();
    cout.width(23 - clientNode->getData().getCallStart().toString().length());
    cout << "|" << clientNode->getData().getCallDuration().toString();
    cout.width(20 - clientNode->getData().getCallDuration().toString().length());
    cout << "|" << endl;
}

void AgentMenu::printAgents(char clients, int option) {
    AgentNode* temp(agentListRef->getFirstPos());
    AgentNode* last(agentListRef->getLastPos());

    int secondOption, sort, filter;

    //makes sure there is at least 1 agent, or else it breaks
    if(temp == nullptr){
        cout << "No hay agentes en la lista" << endl;
        enterToContinue();
        return;
    }
    system(CLEAR);
    if(option == 0){
        //in this case there is only one element in the list
        if (temp == last) {
            //prints the first line of the list, which shows the categories
            agentListHeader();
            if(clients == 's' || clients == 'S'){
                printAgent(temp);
                if(temp->getData().getClientList()->getFirstPos() != nullptr) {
                    cout << "\t";
                    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                    cout << "\t";
                    clientListHeader();
                    printClients(temp);
                    cout << endl;
                }
            } else {
                printAgent(temp);
            }
            //more than one element in the list
        } else {
            if(clients == 's' || clients == 'S'){
                while (temp != nullptr) {
                    //prints the first line of the list, which shows the categories
                    agentListHeader();
                    printAgent(temp);
                    if(temp->getData().getClientList()->getFirstPos() != nullptr) {
                        cout << "\t";
                        cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "\t";
                        clientListHeader();
                        printClients(temp);
                        cout << endl;
                    }
                    temp = temp->getNext();
                }

            } else {
                //prints the first line of the list, which shows the categories
                agentListHeader();
                while (temp != nullptr) {
                    printAgent(temp);
                    temp = temp->getNext();
                }
            }
        }
    } else {
        //in this case there is only one element in the list
        if (temp == last) {
            //prints the first line of the list, which shows the categories
            agentListHeader();
            if(temp->getData().getSpecialty() == option) {
                printAgent(temp);
            }
            //more than one element in the list
        } else {
            //prints the first line of the list, which shows the categories
            agentListHeader();
            while (temp != nullptr) {
                if(temp->getData().getSpecialty() == option) {
                    printAgent(temp);
                }
                temp = temp->getNext();
            }

        }
    }
    cout << endl;
    cout << "1. Ordenar agentes" << endl;
    cout << "2. Filtrar resultados" << endl;
    cout << "3. Salir" << endl;
    cout << "Opcion: ";
    cin >> secondOption;
    switch(secondOption){
        case 1: {
            cout << "1. Nombre" << endl;
            cout << "2. Especialidad" << endl;
            cout << "3. Cancelar" << endl;
            cout << "Opcion: ";
            cin >> sort;
            switch(sort){
                case 1: {
                    agentListRef->sortByName();
                    *changesMadeRef = true;
                    printAgents('n', 0);
                    break;
                }
                case 2: {
                    agentListRef->sortBySpecialty();
                    *changesMadeRef = true;
                    printAgents('n', 0);
                    break;
                }
                default: {
                    break;
                }
            }
            break;
        }
        case 2: {
            cout << "1. Escritorio" << endl;
            cout << "2. Impresoras" << endl;
            cout << "3. Linux" << endl;
            cout << "4. Portatiles" << endl;
            cout << "5. Redes" << endl;
            cout << "6. Servidores" << endl;
            cout << "0. Salir" << endl;
            cout << "Opcion: ";
            cin >> filter;
            if(filter == 0){
                return;
            } else {
                printAgents(clients, filter);
            }
            break;
        }
    }


}

void AgentMenu::printClients(AgentNode* agentNode){
    ClientNode* temp(agentNode->getData().getClientList()->getFirstPos());
    ClientNode* last(agentNode->getData().getClientList()->getLastPos());

    //makes sure there are nodes in the list
    if(temp != nullptr) {
        //this is when there is only one client in the list
        if (temp == last) {
            cout << "\t";
            printClient(temp);
        //multiple clients in the list
        } else {
            while (temp != nullptr) {
                cout << "\t";
                printClient(temp);
                temp = temp->getNext();
            }
        }
    } else {
        cout << "No hay clientes en la lista" << endl;
    }
}

void AgentMenu::mainAgentMenu() {
    bool terminate = false;
    bool saveChanges = false;

    //prints the agent menu
    do{
        int option = 0;
        system(CLEAR);
        cout << "MENU DE AGENTES" << endl;
        cout << "1. Agregar agente" << endl;
        cout << "2. Eliminar agente" << endl;
        cout << "3. Modificar agente" << endl;
        cout << "4. Buscar agente" << endl;
        cout << "5. Organizar agentes" << endl;
        cout << "6. Mostrar los agentes" << endl;
        cout << "7. Eliminar TODOS los agentes" << endl;
        cout << "8. Salir" << endl;
        cout << "Option: ";
        cin >> option;
        switch(option){
        //user chooses an option
            case ADD_AGENT: {
                addAgent();
                *changesMadeRef = true;
                break;
            }
            case DELETE_AGENT: {
                deleteAgent();
                *changesMadeRef = true;
                break;
            }
            case MODIFY_AGENT: {
                modifyAgent();
                *changesMadeRef = true;
                break;
            }
            case SEARCH_AGENT: {
                searchAgent();
                break;
            }
            case ORGANIZE_AGENTS: {
                sortAgents();
                break;
            }
            case SHOW_AGENTS: {
                char options;
                cout << "Guste ver los clientes tambien? (S/N): ";
                cin >> options;
                printAgents(options, 0);
                cin.ignore();
                enterToContinue();
                break;
            }
            case DELETE_ALL_AGENTS: {
                char deleteAgents = '\0';
                cout << "Esta seguro? (S/N): ";
                cin >> deleteAgents;
                if(deleteAgents == 's' || deleteAgents == 'S'){
                    agentListRef->deleteAll();
                    cin.ignore();
                    enterToContinue();
                }
                saveChanges = true;
                break;
            }
            case EXIT_AGENT: {
                terminate = true;
                break;
            }
            default: {
                cout << "Opcion invalida" << endl;
                enterToContinue();
                break;
            }
        }
    }while(!terminate);
}