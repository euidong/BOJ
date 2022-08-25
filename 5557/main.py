import sys

input = sys.stdin.readline

N = int(input().rstrip())
nums = [int(i) for i in input().split()]

cache = [[0 for _ in range(21)] for _ in range(N - 1)]

cache[0][nums[0]] = 1

for i in range(1, N-1):
    for j in range(21):
        if j - nums[i] > -1:
            cache[i][j] += cache[i-1][j-nums[i]]
        if j + nums[i] < 21:
            cache[i][j] += cache[i-1][j+nums[i]]

print(cache[-1][nums[-1]])

