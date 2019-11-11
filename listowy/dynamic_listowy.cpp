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

unsigned int best_task_index(const vector<Task> &tasks, const int[4] &times)
{
    unsigned int idx = -1;
    int best_val, temp_val;

    for (int i = 0; i < tasks.size(); i++) {
        if (!tasks[i].scheduled) {
            temp_val = tasks[i].dynamic_value(times);
            if (temp_val < best_val) {
                best_val = temp_val;
                idx = i;
            }
        }
    }
    if (idx < 0)
        throw runtime_error("All tasks already scheduled");
    return idx;
}

int schedule_dynamic(vector<Task> &tasks)
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
    //auto begin = std::chrono::steady_clock::now();
    //auto end = std::chrono::steady_clock::now();
    vector<pair<vector<double>, double>> best_weights;
    for (int i = 0; i < 1000; i++) {
        //begin = std::chrono::steady_clock::now();
        double avg = 0.0;
        //Task::weight = vector<double> {9.0,0.0,1.0,0.0};
        Task::weight = Task::get_unit_vector(4);
        for (int n = 10; n<=10 ;n++) {
            string sn = to_string(n*50);
            for (int j = 0; j< 1000; j++){
                string sj = to_string(j);
                auto tasks = read_instance("../instances/"+sn+"_"+sj+".txt");
                avg += schedule_static(tasks);
            }
        }
        //end = std::chrono::steady_clock::now();
        //cout << i << " "  << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << endl;
        auto w = Task::weight; 
        avg /= 1000.0;
        best_weights.push_back(make_pair(w, avg));
        cout << i << " " << w[0]<<" "<<w[1]<<" "<<w[2]<<" "<<w[3]<<" " <<avg << endl;
    }

    sort(best_weights.begin(), best_weights.end(), 
        [](const pair<vector<double>, double> &wa1, const pair<vector<double>, double> &wa2) -> bool
    {
        return wa1.second < wa2.second;
    });
    for (auto &x : best_weights){
        auto w = x.first;
        cout << x.second << " | " <<  w[0]<<" "<<w[1]<<" "<<w[2]<<" "<<w[3] << endl;
    }
    return 0;
}

