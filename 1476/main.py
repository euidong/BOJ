E, S, M = [int(i) for i in input().split()]

k = [0, 0, 0]
while True:
    y = [k[0] * 15 + E - 1, k[1] * 28 + S - 1, k[2] * 19 + M - 1]
    if y[0] == y[1] == y[2]:
        break
    k[y.index(min(y))] += 1
print(y[0]+1)
