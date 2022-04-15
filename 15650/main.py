N, M = [int(i) for i in input().split()]
kit = [i for i in range(1, N + 1)]


def solve(kit, nums=[]):
    if len(nums) == M:
        print(' '.join(str(i) for i in nums))
        return
    for idx in range(len(kit)):
        solve(kit[idx + 1:], nums + [kit[idx]])


solve(kit)
