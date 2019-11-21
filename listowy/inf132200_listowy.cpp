#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

#define INT_MAX 2147483647

using namespace std;

const vector<double> W = vector<double> {5.0, 2.0, 6.0, 0.9};
vector<int>* schedule[4];
int MAXP;

class Task {
    public: 
        int nr;
        int p;
        int r;
        int d;
        bool scheduled;

        Task(int nr, int p, int r, int d) :
            nr(nr),
            p(p),
            r(r),
            d(d),
            scheduled(false){};
};


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


void set_globals(const vector<Task> &tasks)
{
    MAXP = -1;
    for (const auto & task: tasks)
        if (task.p > MAXP)
            MAXP = task.p;
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
    for (int i = 0; i < criteria.size(); i++) {
        for (int j = 0; j < 4; j++)
        {
            criteria[i][j] = 0.0;
            criteria[i][j] += tasks[i].p * W[0];
            criteria[i][j] += tasks[i].r * W[1];
            criteria[i][j] += t[j] * W[2];
            criteria[i][j] += (double) MAXP*(tasks[i].d - t[j])/tasks[i].p * W[3];
        }
    }
}

int schedule_dynamic(vector<Task> &tasks)
{
    for (int i = 0; i < 4; i++)
        schedule[i] = new vector<int>;
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
        schedule[cpu]->push_back(t->nr);
        if (times[cpu] < t->r)
            times[cpu] = t->r;
        times[cpu] += t->p;
        penalty += max(times[cpu] - t->d, 0);
    }
    return penalty;
}

bool write_to_file(string filename, int penalty) 
{
    ofstream file(filename);
    file << penalty << endl;
    for (int i = 0; i < 4; i++)
    {
        for(const int &nr : *schedule[i])
            file << nr << " ";
        file << endl;
    }
    file.close();

}

int main(int argc, char* argv[])
{
    auto tasks = read_instance(argv[1]);
    set_globals(tasks);
    int penalty = schedule_dynamic(tasks);
    write_to_file(argv[2], penalty );
    return 0;
}

