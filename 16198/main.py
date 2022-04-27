N = int(input())
W = [int(i) for i in input().split()]

answer = [0]


def solve(W, sum=0):
    if len(W) == 2:
        answer[0] = max([answer[0], sum])
    for idx in range(1, len(W) - 1):
        solve(W[:idx] + W[idx+1:], sum + W[idx-1] * W[idx+1])


solve(W)
print(answer[0])
