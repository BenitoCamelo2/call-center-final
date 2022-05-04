#include "mainmenu.h"

MainMenu::MainMenu() {
    agentList = agentList->readFromDisk(AGENT_FILE_NAME);
    if(agentList == nullptr){
        agentList = new AgentList();
    }
    menu();
}

void MainMenu::menu() {

    bool end = false;
    int option;
    do{

        system(CLEAR);
        cout << "MENU PRINCIPAL" << endl;
        cout << "1. Menu de agentes" << endl;
        cout << "2. Menu de clientes" << endl;
        cout << "3. Guardar cambios" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> option;
        switch(option){
            case AGENT_MENU: {
                new AgentMenu(agentList);
                break;
            }
            case CLIENT_MENU: {
                bool terminate = false;
                AgentNode* temp(agentList->getFirstPos());
                string agentCode;
                Agent tempAgent;

                if(temp == nullptr){
                    cout << "No hay agentes en la lista" << endl;
                    enterToContinue();
                    break;
                }
                //select agent to retrieve client list
                system(CLEAR);
                printAgents();
                cout << "Ingresa el codigo: ";
                cin.ignore();getline(cin, agentCode);
                tempAgent.setCode(agentCode);
                //makes sure the code entered is valid
                while(!terminate){
                    temp = agentList->findData(tempAgent, SEARCH_CODE);
                    if(temp == nullptr){
                        cout << "Ingresa de nuevo: ";
                        getline(cin, agentCode);
                        tempAgent.setCode(agentCode);
                    } else {
                        terminate = true;
                    }
                }
                tempAgent = agentList->retrieve(temp);

                new ClientMenu(tempAgent.getClientList());
                break;
            }
            case SAVE_CHANGES: {
                agentList->writeToDisk(AGENT_FILE_NAME);
                break;
            }
            case EXIT: {
                end = true;
            }
        }
    }while(!end);
}

void MainMenu::printAgent(AgentNode* agentNode) {
    cout << "|" << agentNode->getData().getName().toString();
    cout.width(20 - agentNode->getData().getName().toString().size());
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



void MainMenu::printAgents() {
    AgentNode* temp(agentList->getFirstPos());
    AgentNode* last(agentList->getLastPos());

    //makes sure there is at least 1 agent, or else it breaks
    if(temp == nullptr) {
        cout << "No hay agentes en la lista" << endl;
        enterToContinue();
    }
    //in this case there is only one element in the list
    if (temp == last) {
        //prints the first line of the list, which shows the categories
        cout << "-----------------------------------------------------------------------------------------------" << endl;
        agentListHeader();
        printAgent(temp);

        //more than one element in the list
    } else {
        //prints the first line of the list, which shows the categories
        cout << "-----------------------------------------------------------------------------------------------" << endl;
        agentListHeader();
        while (temp != nullptr) {
            printAgent(temp);
            temp = temp->getNext();
        }

    }
}

void MainMenu::enterToContinue() {
    cout << "Presione enter para continuar..." << endl;
    getchar();
}
