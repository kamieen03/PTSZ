class Task:
    def __init__(self, p, r, d, nr):
        self.p = p
        self.r = r
        self.d = d
        self.nr = nr
        self.criterion = -1

    def __str__(self):
        return f'{self.nr}: {self.p}|{self.r}|{self.d}'

    def __repr__(self):
        return f'{self.nr}: {self.p}|{self.r}|{self.d}'
