#include "Task.hpp"

vector<double> Task::weight = get_unit_vector(4); //static weight vector for computing Tasks' values

Task::Task(int nr, int p, int r, int d) :
    nr(nr),
    p(p),
    r(r),
    d(d),
    scheduled(false)
{
    val = static_value();
};

double Task::static_value() const     //task's value; the smaller the better
{
    return p * weight[0] + 
           r * weight[1] +
           d * weight[2] +
           (r-d) * weight[3];   //maximise the gap d-r
}

bool Task::static_cmp(const Task &a, const Task &b)
{
    return a.val < b.val;
};

double Task::dynamic_value(const int[4] &cpu_times)
{
    int best_cpu = 0;
    double best_val = numeric_limits<double>::max();
    double temp_val;
    for (int i = 0; i < 4; i++) {
        temp_val = (r - times[i]) * weight[0] +
                   p * weight[1] + 
                   d *  weight[2] + 
                   (r-d) * weight[3];   //maximise the gap d-r
        if (temp_val < best_val) {
            best_val = temp_val;
            best_cpu = i;
        } 
        /*
        minimise tiredness diresctly!
        czas zakończenia zadania na danym procku - d
        */
    }
    return 

}

vector<double> Task::get_unit_vector(int n)
{
    vector<double> rand;
    random_device dev;
    default_random_engine rng(dev());
    uniform_real_distribution<double> distribution(0.0,1.0);

    for (int i = 0; i < n; i++) {
        rand.push_back(distribution(rng));
    }
    double sum = accumulate(rand.begin(), rand.end(), 0.0);
    for (int i = 0; i < n; i++) {
        rand[i] = rand[i]/sum;
    }
    return rand;
}




