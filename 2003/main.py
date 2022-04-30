N, M = map(int, input().split())

S = [int(i) for i in input().split()]

answer = 0
for i in range(N):
    acc = 0
    for j in range(i, N):
        acc += S[j]
        if acc > M:
            break
        elif acc == M:
            answer += 1

print(answer)
