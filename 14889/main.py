N = int(input())
half = N//2
stats = [[0]*N]
for _ in range(N):
    stats.append([0] + [int(i) for i in input().split()])


comb = []


def combination(n, k, s=1, prev=[], first=False):
    if k == 0:
        comb.append(prev)
        return

    for i in range(s, n + 1 if not first else n//2):
        combination(n, k-1, i + 1, prev + [i])


combination(N, half, first=True)

min_diff = 100 * 2 * 10
for set in comb:
    other_set = []
    cnt = 0
    for i in range(1, N + 1):
        if cnt == half or set[cnt] != i:
            other_set.append(i)
        else:
            cnt += 1
    tot = [0, 0]
    for i in range(0, len(set)-1):
        for j in range(i+1, len(set)):
            tot[0] += stats[set[i]][set[j]] + stats[set[j]][set[i]]
            tot[1] += stats[other_set[i]][other_set[j]] + \
                stats[other_set[j]][other_set[i]]
    min_diff = min([min_diff, abs(tot[1] - tot[0])])

print(min_diff)
