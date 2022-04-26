N, K = map(int, input().split())
A = [int(i) for i in input().split()]
# 놓은 index를 표기
robots = []
cursor = 0
answer = 0

for i in A:
    if i == 0:
        K -= 1

while K > 0:
    cursor = (cursor - 1) % (2 * N)
    finish = (cursor + N - 1) % (2 * N)
    if len(robots) > 0 and robots[0] == finish:
        robots.pop(0)
    for idx in range(len(robots)):
        next_idx = (robots[idx] + 1) % (2 * N)
        if A[next_idx] > 0:
            if idx > 0 and robots[idx - 1] == next_idx:
                continue
            robots[idx] = next_idx
            A[next_idx] -= 1
            if A[next_idx] == 0:
                K -= 1
    if len(robots) > 0 and robots[0] == finish:
        robots.pop(0)
    if A[cursor] > 0:
        robots.append(cursor)
        A[cursor] -= 1
        if A[cursor] == 0:
            K -= 1
    answer += 1

print(answer)
