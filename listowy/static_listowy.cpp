#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

#include "../common/Task.hpp"
#include "../common/utils.hpp"

using namespace std;

int schedule_static(vector<Task> &tasks)
{
    sort(tasks.begin(), tasks.end(), Task::static_cmp);
    vector<int> schedule[4];
    int times[4] {0};
    int arg_min;
    int penalty = 0;

    for (auto &task : tasks){
        arg_min = min_element(times, times+4) - times;
        schedule[arg_min].push_back(task.nr);
        if (times[arg_min] < task.r)
            times[arg_min] = task.r;
        times[arg_min] += task.p;
        penalty += max(times[arg_min] - task.d, 0);
    }
    return penalty;
}

int main(int argc, char* argv[])
{
    const vector<string> idxs {"127147", "132189", "132190", "132193", "132200",
                         "132213", "132232", "132265", "132284", "132323", "132346"};

    for (int i = 0; i < 1; i++) {
        Task::weight = vector<double> {9.0,0.0,1.0,0.0};
        vector<string> vps;
        for(auto &idx : idxs)
        {
            printf("%9s| ", idx.c_str()); 
            for (int n = 10; n<=10; n++)
            {
                string sn = to_string(n*50);
                auto tasks = read_instance("../instancje/inf"+idx+"/"+sn+".txt");
                int penalty = schedule_static(tasks);
                vps.push_back(to_string(penalty));
            }
        }
        cout << endl;
        for (string & ps : vps)
            printf("%9s| ", ps.c_str());
        cout << endl;
    }

    return 0;
}
