import numpy as np

class Solution:
    tasks = None

    def __init__(self, solution, val = -1):
        self.sol = solution
        if val == -1:
            val = self._get_val(solution)
        self.val = val

    def __cmp__(self, other):
        return cmp(self.val, other.val)

    def __lt__(self, other):
        return self.val < other.val

    def __le__(self, other):
        return self.val <= other.val

    def __repr__(self):
        return str(self.sol[0]) + '\n' + \
               str(self.sol[1]) + '\n' + \
               str(self.sol[2]) + '\n' + \
               str(self.sol[3]) + '\n' + \
               'Value: ' + str(self.val)

    def _get_val(self, solution):
        val = 0
        for machine in solution:
            time = 0
            for task_num in machine:
                task = Solution.tasks[task_num]
                if time < task.r:
                    time = task.r
                time += task.p
                val += max(time - task.d, 0)
        return val

        
