import sys
from queue import PriorityQueue

input = sys.stdin.readline

r, c, k = map(int, input().split())

r -= 1
c -= 1

A = []
for _ in range(3):
    A.append([int(i) for i in input().split()])

answer = 0
while answer <= 100:
    if len(A) > r and len(A[0]) > c and A[r][c] == k:
        print(answer)
        sys.exit()
    new_lines = []

    # 열 연산
    if len(A) < len(A[0]):
        op = 'C'
        M = len(A[0])
        N = len(A)
    # 행 연산
    else:
        op = 'R'
        M = len(A)
        N = len(A[0])

    bigest_len = 0
    for i in range(M):
        cache = {}
        for j in range(N):
            if op == 'C':
                num = A[j][i]
            else:
                num = A[i][j]
            if num == 0:
                continue
            cnt = cache.get(num)
            if cnt == None:
                cache[num] = 1
            else:
                cache[num] = cnt + 1
        pq = PriorityQueue()
        for num, cnt in cache.items():
            pq.put((cnt, num))
        new_line = []
        while not pq.empty():
            cnt, num = pq.get()
            new_line.append(num)
            new_line.append(cnt)
        new_lines.append(new_line)
        bigest_len = max([bigest_len, len(new_line)])

    # 열연산이면 행은 그대로
    if op == 'C':
        y = bigest_len
        x = len(new_lines)
    # 행연산이면 열은 그대로
    else:
        y = len(new_lines)
        x = bigest_len
    A = [[0 for _ in range(x)] for _ in range(y)]

    for i in range(len(new_lines)):
        for j in range(len(new_lines[i])):
            if op == 'R':
                A[i][j] = new_lines[i][j]
            else:
                A[j][i] = new_lines[i][j]

    answer += 1

print(-1)
