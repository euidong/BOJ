import sys
from collections import deque

input = sys.stdin.readline

T = int(input())

MAX_RANGE = 10000

is_prime = [True for _ in range(MAX_RANGE)]
is_prime[0] = False
is_prime[1] = False
for i in range(2, MAX_RANGE):
    if not is_prime[i]:
        continue
    cursor = i + i
    while cursor < MAX_RANGE:
        is_prime[cursor] = False
        cursor += i


for _ in range(T):
    start, end = map(int, input().split())
    if start == end:
        print(0)
        continue
    visited = [False] * MAX_RANGE
    visited[start] = True
    q = deque([(start, 0)])
    while len(q) > 0:
        prime, depth = q.popleft()
        cursor = prime
        ok = False
        for i in range(3, -1, -1):
            value, cursor = divmod(cursor, 10 ** i)
            temp = prime - (value * (10 ** i))
            for j in range(1 if i == 3 else 0, 10):
                if j != value:
                    check = temp + (10 ** i) * j
                    if not visited[check] and is_prime[check]:
                        if check == end:
                            print(depth + 1)
                            ok = True
                        q.append((check, depth + 1))
                    visited[check] = True
                if ok:
                    break
            if ok:
                break
        if ok:
            break
    if not ok:
        print("Impossible")
