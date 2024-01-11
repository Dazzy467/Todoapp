#include "app.h"

app::app(/* args */)
{
}

app::~app()
{
    delete CmdSys;
    delete EventSys;
    delete todoModel;
}

void app::Init()
{
    todoModel = new TodoModel;
    EventSys = new eventSystem;
    CmdSys = new cmdsys(commands,EventSys,[this](const CommandEvent& e)
        {
            this->commandHandler(e);
        }
    );
    viewTodolist();
}

void app::Loop()
{
    std::cout << "Input command:\n";
    std::getline(std::cin,cmd);
    CmdSys->proccessCommand(cmd);

    if (isRun)
        viewTodolist();
}

void app::viewTodolist()
{
    std::cout << "============================\n";
    std::cout << "        Todolist APP        \n";
    std::cout << "============================\n\n";

    // Check todolist if empty
    if (!TodoList.empty())
    {
        for (size_t i = 0; i < TodoList.size(); i++)
        {
            std::cout << i + 1 << ". " << std::setw(20) << std::left << TodoList[i].task << ((TodoList[i].done)? "Finished\n" : "Unfinished\n");
        }
    }
    else
    {
        std::cout << "Todolist empty! Please add a task! Type help for list of commands\n";
    }
}

void app::viewHelp()
{
    std::cout << ".:: H E L P ::.\n\n";

    std::cout << "add {string}; Adds task to list, accepts string as input\n";
    std::cout << "delete {int}; Deletes task from list at specified index, accepts integer as input\n";
    std::cout << "check {int}; Checks task from list at specified index, accepts integer as input\n";
    std::cout << "clear_finished; Clears all finished tasks from list\n";
    std::cout << "clear; Clears all tasks from list\n";
    std::cout << "help; Displays this help message\n";
    std::cout << "save {string}; Saves current task list to file, accepts string as input\n";
    std::cout << "load {string}; Loads task list from file, accepts string as input\n";
    std::cout << "exit; Exits the application\n\n\n";

    std::cout << "Todolist made using console command and event system\n";
    std::cout << "Made by David Yusuf De Waskito :)\n";
    std::cout << "Check out the library on my github page: github.com/Dazzy467\n";
}

void app::commandHandler(const CommandEvent& e)
{
    if (e.getEvtType() == "CMD_EVT_PROCESSED")
    {
        if (e.getCmd().command == "add")
        {
            Todo temp;
            temp.done = false;
            temp.task = e.getCmd().arguments[0];

            TodoList.push_back(temp);
        }

        else if (e.getCmd().command == "exit")
        {
            std::cout << "exiting!\n";
            isRun = false;
            
        }

        else if (e.getCmd().command == "check")
        {
            int idx = std::stoi(e.getCmd().arguments[0]);
            if (idx >= 1 && idx <= TodoList.size())
            {
                TodoList[idx-1].done = !TodoList[idx-1].done;
            }
            else std::cout << "Invalid task selected!\n";
        }

        else if (e.getCmd().command == "save")
        {
            todoModel->set(TodoList);
            if (e.getCmd().arguments.empty())
            {
                todoModel->save();
            }
            else
            {
                todoModel->save(e.getCmd().arguments[0]);
            }
        }

        else if (e.getCmd().command == "load")
        {
            if (e.getCmd().arguments.empty())
            {
                todoModel->load();
            }
            else
            {
                todoModel->load(e.getCmd().arguments[0]);
            }
            TodoList = todoModel->get();
        }
    
        else if (e.getCmd().command == "delete")
        {
            int idx = std::stoi(e.getCmd().arguments[0]);
            if (!TodoList.empty())
            {
                if (idx > 0 && idx <= TodoList.size())
                    TodoList.erase(TodoList.begin() + (idx - 1));
                else std::cout << "Invalid, please enter the correct index!\n";
            }
            else std::cout << "Todolist already empty!\n";
        }

        else if (e.getCmd().command == "clear")
        {
            if (!TodoList.empty())
            {
                TodoList.clear();
            }
            else std::cout << "Todolist already empty!\n";
        }

        else if (e.getCmd().command == "clear_finished")
        {
            if (!TodoList.empty())
            {
                std::vector<Todo>::iterator it = TodoList.begin();
                while (it != TodoList.end())
                {
                    if (it.base()->done)
                        TodoList.erase(it);

                    if(!it.base()->done)
                        ++it;
                }
            }
            else std::cout << "Todolist already empty!\n";
        }

        else if (e.getCmd().command == "help")
        {
            viewHelp();
        }
    
    }
    else{
        std::cout << e.what() << std::endl;
    }

}


int main()
{
    app TodoApp;
    TodoApp.Init();
    do{
        TodoApp.Loop();
    }while(TodoApp.isRun);
}