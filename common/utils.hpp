#pragma once

#include <random>
#include <vector>
#include <fstream>

#include "Task.hpp"

using namespace std;

vector<Task> read_instance(string file_name)
{
    vector<Task> tasks;
    int p, r, d;
    ifstream instance(file_name);
    instance >> p;       //ignore task number
    
    int nr = 1;
    while (instance >> p >> r >> d) {
        Task t(nr++, p, r, d);
        tasks.push_back(t);
    }
    instance.close();
    return tasks;
}

