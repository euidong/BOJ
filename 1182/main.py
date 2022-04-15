N, S = [int(i) for i in input().split()]

es = [int(i) for i in input().split()]


def comb(remain, cur=0):
    tot = 0
    if len(remain) == 0:
        return 0
    for idx in range(len(remain)):
        if cur + remain[idx] == S:
            tot += 1
        tot += comb(remain[idx+1:], cur + remain[idx])
    return tot


print(comb(es))
