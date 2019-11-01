#!/usr/bin/env python3
import sys

def read_instance(instance_file):
    tasks = [None]
    with open(instance_file) as f:
        nr = int(f.readline())
        for _ in range(nr):
            prd = [int(x) for x in f.readline().split()]
            task = dict(zip('prd', prd))
            tasks.append(task)
    return tasks

def read_result(result_file):
    schedule = []
    with open(result_file) as f:
        claimed = int(f.readline())
        for _ in range(4):
            schedule.append(
                [int(x) for x in f.readline().split()]
            )
    return claimed, schedule

def error_string(p, cp):
    return f'Wrong penalty claimed\nTrue penalty = {p}\nClaimed penalty = {cp}'

def check_result(tasks, claimed_penalty, schedule):
    penalty = 0
    for processor in schedule:
        time = 0
        for task_num in processor:
            task = tasks[task_num]
            t_r = task['r']
            if time < t_r:
                time = t_r
            time += task['p']
            penalty += max(time - task['d'], 0)
    assert penalty == claimed_penalty, error_string(penalty, claimed_penalty)


def main():
    instance_file = sys.argv[1]
    result_file = sys.argv[2]

    tasks = read_instance(instance_file)
    claimed_penalty, schedule = read_result(result_file) 
    
    check_result(tasks, claimed_penalty, schedule)

if __name__ == '__main__':
    main()
