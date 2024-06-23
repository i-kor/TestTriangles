#include <iostream>
#include <string>
#include <vector>

#include "tasks.h"
#include "vector2.h"

int main(int argv, char** argc)
{
    std::string fileName;
    if(argv < 2)
        fileName = "..\\input.txt";
    else
        fileName = argc[1];
    
    std::vector<Task<Vector2>> tasks{ ReadTasksFromFile<Vector2>(fileName) };
    //PrintTasks(tasks);
    RunTasks(tasks);
}