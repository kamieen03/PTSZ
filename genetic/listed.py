import numpy as np
import random

from Solution import Solution

def get_new_weights(n):
    a = np.array([0.22, 0.77, 0.0013])
    eps = np.random.normal(0, 0.02, 3)
    eps[2] = 0
    a = a + eps
    P = 2.85 + np.random.normal(0, 0.02)
    R = 0.38 + np.random.normal(0, 0.02)
    return a, P, R
    
def compute_criterion(tasks, W, MAXP, MAXR, P, R):
    MAXP = MAXP ** P
    MAXR = MAXR ** R
    for task in tasks:
        task.criterion = 0
        task.criterion    += \
            W[0] * (task.p ** P) / MAXP +  \
            W[1] * (task.r ** R) / MAXR +  \
            W[2] * (task.d - task.r)/task.p
        #print(W[0] * task.p / MAXP,
        #    W[1] * task.r / MAXR,
        #    W[2] * (task.d - task.r)/task.p)

def schedule(tasks, MAXP, MAXR):
    W, P, R = get_new_weights(3)
    compute_criterion(tasks, W, MAXP, MAXR, P, R)
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
    return Solution(solution, val, W, P, R)
