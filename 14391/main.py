import sys

N, M = [int(i) for i in sys.stdin.readline().split()]
pap = []
for _ in range(N):
    pap.append([int(i) for i in list(sys.stdin.readline().rstrip())])


def solve(remain):
    if len(remain) == 0 or len(remain[0]) == 0:
        return 0
    max_num = 0
    # 가로로 자르기
    for idx in range(len(remain)):
        num = int(''.join([str(i) for i in remain[idx]]))
        num += solve(remain[idx + 1:]) + solve(remain[:idx])
        max_num = max([max_num, num])
    # 세로로 자르기
    for idx in range(len(remain[0])):
        num = ''
        left = []
        right = []
        for j in range(len(remain)):
            left.append(remain[j][:idx])
            right.append(remain[j][idx+1:])
            num += str(remain[j][idx])
        num = int(num)
        num += solve(left) + solve(right)
        max_num = max([max_num, num])
    return max_num


print(solve(pap))
