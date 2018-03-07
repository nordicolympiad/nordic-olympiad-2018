#!/usr/bin/env python

import re
import sys

NM_BOUND = 2000 # TODO: Decide upper bound!
K_BOUND = 10**5 # TODO: Decide upper bound!
Q_BOUND = 10**5 # TODO: Decide upper bound!

s = sys.stdin.readline()
assert re.match(r'^[1-9][0-9]* [1-9][0-9]*\n$', s)
n, m = map(int, s.strip().split())
assert 1 <= n <= NM_BOUND
assert 1 <= m <= NM_BOUND

for i in range(n):
    s = sys.stdin.readline()
    assert re.match(r'^[.#]+\n$', s)
    s = s.strip()
    assert len(s) == m

s = sys.stdin.readline()
assert re.match(r'^(0|[1-9][0-9]*)\n$', s)
q = int(s.strip())
assert 0 <= q <= Q_BOUND

for t in range(q):
    s = sys.stdin.readline()
    assert re.match(r'^[1-9][0-9]* [1-9][0-9]*\n$', s)
    x, y = map(int, s.strip().split())
    assert 1 <= x <= n
    assert 1 <= y <= m

    # TODO: Do we want to disallow duplicate water sources?
    # TODO: Do we want to disallow water sources on rocky cells?

assert sys.stdin.read() == ''
sys.exit(42)
