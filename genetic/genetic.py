#!/usr/bin/env python3
import random
import numpy as np
import copy
from time import time

from const import *
from listed import schedule
from Task import Task
from Solution import Solution
from population import Population 

START_TIME = -1
RADIUS = -1

def get_max(tasks):
    maxp = 0
    maxr = 0
    for t in tasks:
        if t.p > maxp:
            maxp = t.p
        if t.r > maxr:
            maxr = t.r
    return maxp, maxr

def read_file(file_name):
    tasks = []
    with open(file_name, 'r') as f:
        N = int(f.readline())
        for i in range(N):
            p, r, d = [int(x) for x in f.readline().split(' ')]
            tasks.append(Task(p, r, d, i))
    return tasks


def initialize(tasks):
    MAXP, MAXR = get_max(tasks)
    solutions = [schedule(tasks, MAXP, MAXR) for _ in range(POPULATION)]
    return Population(solutions)


# mutation
def swap(solution):
    machine = random.randrange(4) 
    idx1 = random.randrange(len(solution[machine]))
    idx2 = random.randrange(idx1 - RADIUS, idx1 + RADIUS)
    idx2 = min(max(0, idx2), len(solution[machine])-1)
    temp = solution[machine][idx1]
    solution[machine][idx1] = solution[machine][idx2]
    solution[machine][idx2] = temp 
    return solution

def cross_swap(solution):
    m1, m2 = random.sample([0,1,2,3], 2)
    idx1 = random.randrange(len(solution[m1]))
    idx2 = random.randrange(idx1 - RADIUS, idx1 + RADIUS)
    idx2 = min(max(0, idx2), len(solution[m2])-1)
    temp = solution[m1][idx1]
    solution[m1][idx1] = solution[m2][idx2]
    solution[m2][idx2] = temp 
    return solution

def mutate(population):
    mutations = [swap, cross_swap]
    distribution = np.array([sol.val for sol in population.array])**2
    distribution = distribution / distribution.sum()
    counts = np.random.multinomial(int(POPULATION * MUT), distribution)
    new = []

    for i, c in enumerate(counts):
        for _ in range(c):
            m = random.choice(mutations)
            new.append(Solution(m(copy.deepcopy(population[i].sol))))
    return new



def execute_algorithm(tasks):
    global RADIUS
    population = initialize(tasks)
    best_solution = copy.deepcopy(population[0])
    print(best_solution.val)

    while True:
        used = time() - START_TIME 
        RADIUS = ((MAX_TIME-used)*6 + 2*used) / MAX_TIME
        RADIUS = int(RADIUS)
        if used > MAX_TIME - 0.1:
            break
        mutated = mutate(population)
        population.update(mutated)
        if population[0] < best_solution:
            best_solution = copy.deepcopy(population[0])
            print(best_solution.val)
            if best_solution.val == 0:
                break
    print(best_solution)


def main():
    global START_TIME
    START_TIME = time()
    tasks = read_file('instancje/inf132190/500.txt')
    Solution.tasks = tasks
    execute_algorithm(tasks)
    

if __name__ == '__main__':
    main()
    


    
        
