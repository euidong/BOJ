N, M = map(int, input().split())

S = [int(i) for i in input().split()]

cursor = 0

MAX_ANSWER = 100_000

answer = MAX_ANSWER + 1
acc = 0
is_done = False
for idx in range(len(S)):
    while acc < M:
        if cursor == len(S):
            is_done = True
            break
        acc += S[cursor]
        cursor += 1
    if is_done:
        break
    answer = min([answer, cursor - idx])
    acc -= S[idx]

if answer == MAX_ANSWER + 1:
    print(0)
else:
    print(answer)
