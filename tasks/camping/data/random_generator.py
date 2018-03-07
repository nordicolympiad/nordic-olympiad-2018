#!/usr/bin/python3

import sys
import random

default = {
    "n": 100,
    "m": 100,
    "q": 100,
    "k": 100
}


def cmdlinearg(name):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    return default[name]


def gen_randpoints(n, m, q):
    # res = set()
    assert q <= n * m
    return random.sample(list((i+1, j+1) for j in range(m) for i in range(n)), q)

def main():
    n, m, q = (int(cmdlinearg(name)) for name in ['n', 'm', 'q'])
    k = int(cmdlinearg('k'))
    assert k <= n*m
    assert q <= n*m
    random.seed(int(sys.argv[-1]))
    print("{} {} {}".format(n, m, k))

    idx = [ (i+1,j+1) for i in range(n) for j in range(m) ]
    random.shuffle(idx)

    arr = [ [ '.' for j in range(m) ] for i in range(n) ]

    for i in range(k):
        arr[idx[i][0]][idx[i][1]] = '#'

    for i in range(n):
        print('%s' % ''.join(arr[i]))

    random.shuffle(idx)
    print('%d' % q)
    for i in range(q):
        print('%d %d' % idx[i])


if __name__ == "__main__":
    main()

