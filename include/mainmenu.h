#ifndef PROGRAMA_MAINMENU_H
#define PROGRAMA_MAINMENU_H

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

#include <iostream>

#include "agentmenu.h"
#include "clientmenu.h"

using namespace std;

class MainMenu {
private:
    AgentList* agentList;
public:
    MainMenu();

    void menu();
    void printAgent(AgentNode* agentNode);
    void printAgents();

    void enterToContinue();
};

enum{
    AGENT_MENU = 1,
    CLIENT_MENU,
    SAVE_CHANGES,
    EXIT
};

#endif //PROGRAMA_MAINMENU_H
