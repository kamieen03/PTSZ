import numpy as np
import bisect

import bisect

class Population:
    def __init__(self, solutions):
        self.array = sorted(solutions)
        self.size = len(self.array)

    def __len__(self):
        return len(self.array)

    def update(self, solutions):
        solutions = sorted(solutions)
        start_idx = bisect.bisect_left(self.array, solutions[0])
        self._merge(solutions, start_idx)

    def _merge(self, solutions, arr_idx):
        if arr_idx == self.size:
            return

        sol_idx = 0
        new_arr = self.array[:arr_idx]

        while len(new_arr) < self.size:
            if sol_idx < len(solutions) and solutions[sol_idx] <= self.array[arr_idx]:
                new_arr.append(solutions[sol_idx])
                sol_idx += 1
            else:
                new_arr.append(self.array[arr_idx])
                arr_idx += 1
        self.array = new_arr

    def __getitem__(self, key):
        return self.array[key]

        
        
