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
int MAXP;
double HORIZON;

void set_globals(const vector<Task> &tasks)
{
    MAXP = -1;
    for (const auto & task: tasks)
        if (task.p > MAXP)
            MAXP = task.p;
    double sum = 0;
    for (const auto & task: tasks)
        sum += task.p;
    sum /= 4.0;
    HORIZON = sum/tasks.size()*10;

}

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

void compute_criteria(vector<vector<int>> &criteria, const vector<Task> &tasks, const int t[4])
{
    vector<int> times(4, 1.0);
    if (!(t[0] == t[1] == t[2] == t[3])){
        times[0] = (double) t[0];
        times[1] = (double) t[1];
        times[2] = (double) t[2];
        times[3] = (double) t[3];
        double m = (double) *min_element(times.begin(), times.end());
        for (auto &x : times)
            x -= m;
        double M = (double) *max_element(times.begin(), times.end());
        for (auto &x : times)
            x /= M;
    }
    for (int i = 0; i < criteria.size(); i++) {
        for (int j = 0; j < 4; j++)
        {
            criteria[i][j] = max(times[j], tasks[i].r) + tasks[i].p - tasks[i].d;
            criteria[i][j] = 0.0;
            criteria[i][j] += tasks[i].p * W[0];
            criteria[i][j] += tasks[i].r * W[1];
            criteria[i][j] += tasks[i].d * W[2];
            criteria[i][j] += t[j] * W[3];
            criteria[i][j] += (double) MAXP*(tasks[i].d - t[j])/tasks[i].p * W[4];
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
    vector<double> avg[11];
    vector<vector<double>> ws;

    for (int i = 0; i < 1000; i++) {
        W = Task::get_unit_vector(5);
        //W = vector<double> {0.15, 0.4, 0.3, 0.15};
        ws.push_back(W);
        vector<string> vps;
        int k = 0;
        for(auto &idx : idxs)
        {
            for (int n = 10; n<=10; n++)
            {
                string sn = to_string(n*50);
                auto tasks = read_instance("../instancje/inf"+idx+"/"+sn+".txt");
                set_globals(tasks);
                int penalty = schedule_dynamic(tasks);
                vps.push_back(to_string(penalty));
                avg[k++].push_back((double)penalty);
            }
        }
       // for (string & ps : vps)
       //     printf("%9s| ", ps.c_str());
       // cout << endl;
    }
    cout <<"minimums" <<endl;
    for (const vector<double> &v : avg)
        printf("%9s| ", to_string((long) *min_element(v.begin(), v.end())).c_str());
    cout << endl;

    auto avg_copy = avg;
    //for (vector<double> &v : avg)
    //{
    //    int m = *min_element(v.begin(), v.end());
    //    for (auto &elem : v)
    //        elem = elem-m+0.000001;
    //    int M = *max_element(v.begin(), v.end());
    //    for (auto &elem : v)
    //        elem /= M;

    //}
    double best_val = 1.0;
    int idx;
    double temp;
    for (int i = 0; i < 11; i++)
    {
        best_val = INT_MAX;
        idx = -1;
        for (int j = 0; j < ws.size(); j++)
        {
            if (avg_copy[i][j] < best_val){
                best_val = avg[i][j];
                idx = j;
            }
        }
        auto w = ws[idx];
        cout << avg_copy[i][idx] << " " <<idx<<" " ;
    //    cout <<  w[0]<<" "<<w[1]<<" "<<w[2]<<" "<<w[3]<< endl;
    }

    return 0;
}

