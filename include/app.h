#pragma once
#include <iostream>
#include <iomanip>
#include "cmdsys.h"
#include "event.h"
#include "Todo.h"
#include "TodoModel.h"
class app
{
private:
    std::vector<Command> commands = 
    {
        {"add",{ARG_TYPE::ARG_STRING},false,true},
        {"delete",{ARG_TYPE::ARG_INT}},
        {"check",{ARG_TYPE::ARG_INT}},
        {"clear_finished"},
        {"clear"},
        {"help"},
        {"save",{ARG_TYPE::ARG_STRING},true,true},
        {"load",{ARG_TYPE::ARG_STRING},true,true},
        {"exit"},
    };
    std::string cmd;
    std::vector<Todo> TodoList;

    // Element
    cmdsys* CmdSys;
    eventSystem* EventSys;
    TodoModel* todoModel;
    
public:
    bool isRun = true;
public: // Runners
    app(/* args */);
    ~app();
    void Init();
    void Loop();
public: // Methods
    void viewTodolist();
    void viewHelp();
public: // Handler
    void commandHandler(const CommandEvent&);

};
