#ifndef TASK
#define TASK

#include <vector>
#include <random>
#include <ostream>

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
        int choose_processor(const int* cpu_times) const;

        static bool static_cmp(const Task &a, const Task &b);
        static vector<double> get_unit_vector(int n);
        friend ostream &operator<<( ostream &output, const Task &t ) {
            output << t.p << " " << t.r << " " << t.d << " " << t.nr << " " << t.scheduled;
            return output;
        }

};
#endif
