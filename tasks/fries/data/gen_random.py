#!/usr/bin/python3

import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
p = int(cmdlinearg('p'))
t = int(cmdlinearg('t'))
l = cmdlinearg('l')
lims = cmdlinearg('lim', '10000000')
lims = list(map(int, lims.split(','))) if ',' in lims else [0, int(lims)]
dist = cmdlinearg('dist', 'uniform')
parity = cmdlinearg('parity', 'both')

try:
    l = float(l)
except:
    if l == 'mean':
        # Works best if p * t ** 0.5 >= lim
        l = max(p / (lims[1] - lims[0]), 1e-4)
    else:
        assert False, "Invalid l value"

if parity != 'both':
    lims[0] = lims[0] // 2 + 3
    lims[1] = lims[1] // 2 - 3

if dist == 'uniform':
    assert p <= lims[1] - lims[0] + 1
    ps = random.sample(range(lims[0], lims[1]+1), p)
elif dist == 'triangular':
    ps = []
    pss = set()
    mid = random.uniform(lims[0], lims[1])
    assert p*1.1 < lims[1] - lims[0]
    while len(pss) < p:
        x = round(random.triangular(lims[0], lims[1], mid))
        if x not in pss:
            pss.add(x)
            ps.append(x)
else:
    assert False

if parity == 'odd':
    ps = [2*x + 1 for x in ps]
elif parity == 'even':
    ps = [2*x for x in ps]
elif parity == 'biased':
    ps = [2*x + random.choice([0, 0, 0, 1]) for x in ps]
else:
    assert parity == 'both'

print(p, t, l)
print(*ps)
