#!/usr/bin/env python3
from numpy.random import normal, binomial, randint, choice
import os

def generate(n, f):
    f.write(f'{n}\n')
    p = normal(27, 13, n)
    p = p.clip(3,60)
    p = p.astype(int)
    total = p.sum()/4

    possible_r_means = randint(5, int(4/5*total), 5)
    r_means = choice(possible_r_means, n)
    r = normal(r_means, total/100)
    r = r * (r>0)
    r = r.astype(int)

    d = r + p + randint(10, 40)
    min_r = r.min()
    r -= min_r
    d -= min_r

    assert (d-r > p).all() 
    assert (p > 0).all()
    assert (r >= 0).all()
    assert (d >= 0).all()
    for pi, ri, di in zip(p, r, d):
        f.write(f'{pi} {ri} {di}\n')

def main():
    try:
        os.mkdir('instances')
    except FileExistsError:
        pass
    for n in range(50, 501, 50):
            f_name = f'instances/{n}.txt'
            with open(f_name, 'w+') as f: 
                generate(n, f)

if __name__ == '__main__':
    main()
