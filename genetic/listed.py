import numpy as np

from Solution import Solution

def get_new_weights(n):
    a = np.random.random(n)
    return a/a.sum()
    
def compute_criterion(tasks, W, MAXP):
    for task in tasks:
        task.criterion = 0
        task.criterion    += \
            W[0] * task.p +  \
            W[1] * task.r +  \
            W[2] * MAXP * (task.d - task.r)/task.p

def schedule(tasks, MAXP):
    W = get_new_weights(3)
    compute_criterion(tasks, W, MAXP)
    tasks = sorted(tasks, key = lambda t: t.criterion)
    times = np.array([0 for _ in range(4)])
    solution = [[] for _ in range(4)]
    times = np.array([0 for _ in range(4)])
    val = 0
    for t in tasks:
        machine = np.argmin(times)
        solution[machine].append(t.nr)
        if times[machine] < t.r:
            times[machine] = t.r
        times[machine] += t.p
        val += max(times[machine] - t.d, 0)
    return Solution(solution, val)
