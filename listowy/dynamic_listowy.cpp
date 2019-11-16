#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

#include "../common/Task.hpp"
#include "../common/utils.hpp"

#define INT_MAX 2147483647

using namespace std;

vector<double> W {1.0, 1.0, 1.0, 1.0};

pair<int, int> choose_best_task(const vector<vector<int>> &criteria, const vector<Task> &tasks)
{
    pair<int, int> best_task_cpu(-1, -1);
    int best_val = INT_MAX;

    for (int i = 0; i < criteria.size(); i-=-1) 
    {
        if (tasks[i].scheduled)
            continue;
        for (int j = 0; j < 4; j++)
        {
            if (criteria[i][j] < best_val)
            {
                best_val = criteria[i][j];
                best_task_cpu = make_pair(i, j);
            }
        }
    }
    return best_task_cpu;
}

void compute_criteria(vector<vector<int>> &criteria, const vector<Task> &tasks, const int times[4])
{
    for (int i = 0; i < criteria.size(); i++) {
        for (int j = 0; j < 4; j++)
        {
//            criteria[i][j] = max(times[j], tasks[i].r) + tasks[i].p - tasks[i].d;
            criteria[i][j] = tasks[i].p * W[0] +
                             tasks[i].r * W[1] +
                             tasks[i].d * W[2] +
                             times[j] * W[3];
        }
    }
}

int schedule_dynamic(vector<Task> &tasks)
{
    vector<int> schedule[4];
    vector<vector<int>> criteria; //criterion value for given Task on 4 processors
    for ( auto &t : tasks) {
        vector<int> temp(4, 0);
        criteria.push_back(temp);
    }
    int times[4] {0};
    int penalty = 0;

    for (int i = 0; i < tasks.size(); i++)
    {
        compute_criteria(criteria, tasks, times);
        pair<int, int> task_cpu = choose_best_task(criteria, tasks); //task's index and cpu's index
        Task* t = &tasks[task_cpu.first];
        t->scheduled = true;
        int cpu = task_cpu.second;
        schedule[cpu].push_back(t->nr);
        if (times[cpu] < t->r)
            times[cpu] = t->r;
        times[cpu] += t->p;
        penalty += max(times[cpu] - t->d, 0);
    }
    return penalty;
}

int main(int argc, char* argv[])
{
    const vector<string> idxs {"127147", "132189", "132190", "132193", "132200",
                         "132213", "132232", "132265", "132284", "132323", "132346"};
    //vector<pair<vector<double>, double>> best_weights;
    for (auto &idx : idxs)
        printf("%9s| ", idx.c_str()); 
    cout << endl;
    vector<long> avg[11];

    for (int i = 0; i < 1000; i++) {
        W = Task::get_unit_vector(4);
        vector<string> vps;
        int k = 0;
        for(auto &idx : idxs)
        {
            for (int n = 10; n<=10; n++)
            {
                string sn = to_string(n*50);
                auto tasks = read_instance("../instancje/inf"+idx+"/"+sn+".txt");
                int penalty = schedule_dynamic(tasks);
                vps.push_back(to_string(penalty));
                avg[k].push_back((long)penalty);
            }
            k++;
        }
       // for (string & ps : vps)
       //     printf("%9s| ", ps.c_str());
       // cout << endl;
        //best_weights.push_back(make_pair(w, avg));
        //cout << i << " " << w[0]<<" "<<w[1]<<" "<<w[2]<<" "<<w[3]<<" " <<avg << endl;
    }
    cout <<"averages" <<endl;
    for (vector<long> v : avg)
        printf("%9s| ", to_string((long)accumulate( v.begin(), v.end(), 0.0)/v.size()).c_str());
    cout << endl;
/*
    sort(best_weights.begin(), best_weights.end(), 
        [](const pair<vector<double>, double> &wa1, const pair<vector<double>, double> &wa2) -> bool
    {
        return wa1.second < wa2.second;
    });
    for (auto &x : best_weights){
        auto w = x.first;
        cout << x.second << " | " <<  w[0]<<" "<<w[1]<<" "<<w[2]<<" "<<w[3] << endl;
    }
    */
    return 0;
}

