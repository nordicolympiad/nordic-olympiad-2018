#!/usr/bin/env pypy

from __future__ import print_function
from __future__ import division
import subprocess
import random
import math
import sys
import string

method = sys.argv[1]
n = int(sys.argv[2])
q = int(sys.argv[3])
random.seed(int(sys.argv[-1]))

if method == 'rand1':
    sys.stdout.write('%d %d\n' % (n,q))
    for i in range(q):
        a = random.randint(1,n)
        b = random.randint(1,n)
        if a > b: a,b = b,a
        x = random.randint(1,n)
        sys.stdout.write('%d %d %d\n' % (a,b,x))
elif method == 'rand2':
    sys.stdout.write('%d %d\n' % (n,q))

    perm = [ i+1 for i in range(n) ]
    random.shuffle(perm)

    # TODO: Maybe test cases with some special permutations?

    mn = [ [None]*n for i in range(20) ]
    for t in range(20):
        for i in range(n):
            if t == 0:
                mn[t][i] = perm[i]
            else:
                mn[t][i] = mn[t-1][i]
                if i+2**(t-1) < n:
                    mn[t][i] = min(mn[t][i], mn[t-1][i+2**(t-1)])

    for i in range(q):
        a = random.randint(0,n-1)
        b = random.randint(0,n-1)
        if a > b: a,b = b,a

        l2 = 0
        while 2**(l2+1) <= b-a+1:
            l2 += 1

        x = min(mn[l2][a], mn[l2][b-2**l2+1])
        # assert x == min( perm[i] for i in range(a,b+1) )
        sys.stdout.write('%d %d %d\n' % (a+1,b+1,x))
elif method == 'inc1':
    sys.stdout.write('%d %d\n' % (n,q))
    for i in range(q):
        a = i+1
        b = n
        x = i+1
        sys.stdout.write('%d %d %d\n' % (a,b,x))
elif method == 'inc2':
    sys.stdout.write('%d %d\n' % (n,q))
    for i in range(q):
        a = i+1
        b = i+1
        x = i+1
        sys.stdout.write('%d %d %d\n' % (a,b,x))
elif method == 'same':
    sys.stdout.write('%d %d\n' % (n,q))
    for i in range(q):
        a = 1
        b = n
        x = 1
        sys.stdout.write('%d %d %d\n' % (a,b,x))
else:
    assert False

