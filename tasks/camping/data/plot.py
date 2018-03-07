import sys

n,m,k = map(int,sys.stdin.readline().strip().split())
arr = [ [ '.' for j in range(m) ] for i in range(n) ]

for i in range(k):
    x,y = map(int, sys.stdin.readline().strip().split())
    x -= 1
    y -= 1
    arr[x][y] = '#'

for row in arr:
    print(''.join(row))


