#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>

#include "../common/Task.hpp"
#include "../common/utils.hpp"

using namespace std;

int schedule_random(vector<Task> &tasks)
{
    random_shuffle(tasks.begin(), tasks.end());
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
                avg += schedule_random(tasks);
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