#!/usr/bin/env python

import re
import sys

s = sys.stdin.readline()
assert re.match(r'^[1-9][0-9]* [1-9][0-9]*\n$', s)
n, q = map(int, s.strip().split())
assert 1 <= n <= 2*10**5
assert 1 <= q <= 2*10**5

for i in range(q):
    s = sys.stdin.readline()
    assert re.match(r'^[1-9][0-9]* [1-9][0-9]* [1-9][0-9]*\n$', s)
    a, b, x = map(int, s.strip().split())
    assert 1 <= a <= b <= n
    assert 1 <= x <= n

assert sys.stdin.read() == ''
sys.exit(42)
