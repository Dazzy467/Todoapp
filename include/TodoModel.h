#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Todo.h"

class TodoModel
{
private:
    /* data */
    std::vector<Todo> todos;
public:
    TodoModel(){}
    ~TodoModel(){}

public: // method
    void save(const std::string& path = "todo.tds")
    {
        // Open file
        std::string npath = path + ".tds";
        std::fstream file(npath, std::fstream::out | std::fstream::binary | std::fstream::trunc);
        
        if (file.is_open())
        {
            // Serialize datas
            if (todos.empty())
            {
                throw "Cannot save empty list!";
                return;
            }

            for (auto& todo : todos)
            {
                // Serialize size
                size_t size = todo.task.size();
                // write data
                file.write(reinterpret_cast<char*>(&size),sizeof(size_t)); // Write the size
                file.write(reinterpret_cast<const char*>(todo.task.c_str()),size); // Write the task string
                file.write(reinterpret_cast<char*>(&todo.done),sizeof(bool)); // Write the done boolean
            }

            file.close();
        } else {
            throw "Unable to open file!";
            return;
        }


        
    }
    void load(const std::string& path = "todo.tds")
    {
        std::string npath = path + ".tds";
        std::fstream file(npath, std::fstream::in | std::fstream::binary);

        if (file.is_open())
        {
            // Clear existing data
            todos.clear();
            // read the data
            size_t size;

            while(file.read(reinterpret_cast<char*>(&size),sizeof(size_t)))
            {
                Todo temp;
                temp.task.resize(size);
                file.read(temp.task.data(),size);
                file.read(reinterpret_cast<char*>(&temp.done),sizeof(bool));

                todos.push_back(temp);
            }
        }else {
            throw "Unable to open file!";
            return;
        }
        
    }

    void set(const std::vector<Todo>& _todos)
    {
        todos = _todos;
    }
    const std::vector<Todo> get() const
    {
        return todos; 
    }

};