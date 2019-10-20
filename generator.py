#!/usr/bin/env python3
from numpy.random import normal, binomial, randint, choice
import os

def binary(n):
    return binomial(1, 0.5, n)

def generate(n, f):
    f.write(f'{n}\n')
    mask = binary(n)
    p = normal(20, 10, n)*mask + normal(35, 10, n)*(1-mask)
    p = p.clip(3,60)
    p = p.astype(int)
    total = p.sum()/4

    possible_r_means = randint(5, int(4/5*total), 5)
    r_means = choice(possible_r_means, n)
    r = normal(r_means, total/100)
    r = r * (r>0)
    r = r.astype(int)

    d = r + p + randint(10, 40)

    assert (d-r > p).all() 
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
