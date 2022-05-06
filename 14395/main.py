from collections import deque
from math import sqrt
import sys

s, t = map(int, input().split())

# -는 쓸일이 없음
# t > 0 이기 때문
case = ['*', '+', '/']

if s == t:
    print(0)
else:
    q = deque()
    q.append((s, ''))
    visited = {}
    visited.update({s: True})
    while len(q) > 0:
        curr, seq = q.popleft()
        if curr == t:
            print(seq)
            sys.exit()
        for i in range(3):
            if case[i] == '*':
                if sqrt(t) >= curr:
                    temp = curr ** 2
                    if visited.get(temp) == None:
                        visited.update({temp: True})
                        q.append((temp, seq + '*'))
            elif case[i] == '+':
                if t / 2 >= curr:
                    temp = curr * 2
                    if visited.get(temp) == None:
                        visited.update({temp: True})
                        q.append((temp, seq + '+'))
            elif case[i] == '/':
                if visited.get(1) == None:
                    visited.update({1: True})
                    q.append((1, seq + '/'))
    print(-1)
