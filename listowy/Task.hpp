#ifndef TASK
#define TASK

#include <vector>
#include <random>

using namespace std;

class Task 
{
    private:
        double val;

    public:
        int p;
        int r;
        int d;
        int nr;
        bool scheduled;
        static vector<double> weight;

        Task(int nr, int p, int r, int d);
        double static_value() const;     //task's value; the smaller the better
        double dyanmic_value(const int[4] &cpu_times);

        static bool static_cmp(const Task &a, const Task &b);
        static vector<double> get_unit_vector(int n);

};
#endif
