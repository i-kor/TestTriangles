#include <iostream>
#include <string>
#include <vector>

#include "tasks.h"

enum class Mode
{
    D2,
    D3
};

int main(int argv, char** argc)
{
    Mode mode{Mode::D3};
    std::string fileName;
    if(argv < 3)
        fileName = "..\\input3D.txt";
    else
    {
        fileName = argc[1];
        std::string str(argc[2]);
        if(str == "2D")
            mode = Mode::D2;
    }
    
    if(mode == Mode::D2)
    {
        std::vector<Task<Vector2, Segment2D>> tasks{ ReadTasksFromFile<Vector2, Segment2D>(fileName) };
        PrintTasks(tasks);
        RunTasks(tasks);
    }
    else
    {
        std::vector<Task<Vector3, Segment3D>> tasks{ ReadTasksFromFile<Vector3, Segment3D>(fileName) };
        PrintTasks(tasks);
        RunTasks(tasks);
    }
}