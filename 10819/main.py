input()
arr = [int(i) for i in input().split()]
max_num = [0]


def solve(remain, prev=[]):
    if len(remain) == 0:
        num = 0
        for idx in range(len(prev) - 1):
            num += abs(prev[idx] - prev[idx+1])
        max_num[0] = max([num] + max_num)
        return
    for idx in range(len(remain)):
        solve(remain[:idx] + remain[idx+1:], prev + [remain[idx]])


solve(arr)
print(max_num[0])
