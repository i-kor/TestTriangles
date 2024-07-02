#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "state.h"
#include "triangle.h"

// Custom boolean read from stream
bool ReadBool(std::istream& input)
{
    std::string str;
    input >> str;
    if(str == "true")
        return true;
    else if(str == "false")
        return false;
    else
        input.setstate(std::ios::failbit);
    return true;
}

// Made it using templates to provide the possibility of extension to use also Vector3
// Single task
template<typename Vector, typename Segment>
struct Task
{
    Triangle<Vector, Segment> triangle[2];
    std::string name; // Name of the task is set from the commented line
    bool expectedResult;
};

// Read tasks from a file
template<typename Vector, typename Segment>
std::vector<Task<Vector, Segment>> ReadTasksFromFile(std::string filename)
{
    std::vector<Task<Vector, Segment>> tasks;
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Can't open file: " << filename << '\n';
        return {};
    }

    StateWrapper state;
    
    std::string line;
    size_t lineCount{};
    Task<Vector, Segment> task;

    while(std::getline(file, line))
    {
        ++lineCount;

        // Ignore empty lines
        if(line.empty())
            continue;

        // Ignore comments 
        if(line[0]== '#')
        {
            task.name = line;
            continue;
        }

        // Read data from line
        std::stringstream input(line);
        switch(state)
        {
            case State::FirstTriangle:
                input >> task.triangle[0];
                break;
            case State::SecondTriangle:
                input >> task.triangle[1];
                break;
            case State::ExpectedResult:
                task.expectedResult = ReadBool(input);
                break;
        }
        // Check for input errors
        if(input.fail())
        {
            std::cerr << "Error in line: " << lineCount << '\n';
            return {};
        }
        else
        {
            if(state == State::ExpectedResult)
                tasks.push_back(task);
            state.Next();
        }
    }
    return tasks;
}

// Output tasks to console for debugging
template<typename Vector, typename Segment>
void PrintTasks(std::vector<Task<Vector, Segment>>& tasks)
{
    size_t taskCount{};
    for(const auto& task : tasks)
    {
        std::cout << "Task #" << ++taskCount << ": ";
        std::cout << task.name << '\n';
        std::cout << "Triangle #1: " << task.triangle[0] << '\n';
        std::cout << "Triangle #2: " << task.triangle[1] << '\n';
        std::cout << "Expected result: " << (task.expectedResult ? "True" : "False") << '\n';

        auto intersect{ AreIntersecting(task.triangle[0], task.triangle[1]) };
        std::cout << "Calculated result: " << ( intersect ? "True" : "False") << '\n';
        if(intersect != task.expectedResult)
            std::cout << ">>>>> !!! Wrong answer !!! <<<<<<\n";
        std::cout << std::endl;
    }
}

template<typename Vector, typename Segment>
void RunTasks(std::vector<Task<Vector, Segment>>& tasks)
{
    size_t taskCount{};
    size_t failedCount{};
    for(const auto& task : tasks)
    {
        ++taskCount;
        auto intersect{ AreIntersecting(task.triangle[0], task.triangle[1]) };
        if(intersect != task.expectedResult)
        {
            std::cout << "test " << taskCount << ": expected " << (task.expectedResult ? "true" : "false") << ", got " << (intersect ? "true" : "false") << std::endl;
            ++failedCount;
        }
    }
    std::cout << "Tests done: " << taskCount << "; failed " << failedCount << std::endl;
}
