N, M = [int(i) for i in input().split()]
kit = sorted([int(i) for i in input().split()])


def solve(kit, nums=[]):
    if len(nums) == M:
        print(' '.join(str(i) for i in nums))
        return
    for idx in range(len(kit)):
        solve(kit[idx:], nums + [kit[idx]])


solve(kit)
