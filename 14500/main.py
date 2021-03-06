N, M = [int(i) for i in input().split()]

pap = []
for _ in range(N):
    pap.append([int(i) for i in input().split()])

flts = [
    # [][][][]
    [(0, 0), (0, 1), (0, 2), (0, 3)],
    [(0, 0), (1, 0), (2, 0), (3, 0)],

    # []
    # [][]
    #   []
    [(0, 0), (1, 0), (1, 1), (2, 1)],
    [(0, 0), (0, 1), (-1, 1), (-1, 2)],
    [(0, 0), (0, 1), (1, 1), (1, 2)],
    [(0, 0), (1, 0), (0, 1), (-1, 1)],

    # []
    # []
    # [][]
    [(0, 0), (1, 0), (2, 0), (2, 1)],
    [(0, 0), (1, 0), (0, 1), (0, 2)],
    [(0, 0), (0, 1), (1, 1), (2, 1)],
    [(0, 0), (0, 1), (0, 2), (-1, 2)],
    [(0, 0), (0, 1), (1, 0), (2, 0)],
    [(0, 0), (1, 0), (1, 1), (1, 2)],
    [(0, 0), (0, 1), (-1, 1), (-2, 1)],
    [(0, 0), (0, 1), (0, 2), (1, 2)],

    # [][]
    # [][]
    [(0, 0), (0, 1), (1, 0), (1, 1)],

    # [][][]
    #   []
    [(0, 0), (0, 1), (0, 2), (1, 1)],
    [(0, 0), (0, 1), (-1, 1), (1, 1)],
    [(0, 0), (0, 1), (0, 2), (-1, 1)],
    [(0, 0), (1, 0), (2, 0), (1, 1)],
]

result = 0
for i in range(N):
    for j in range(M):
        for flt in flts:
            tot = 0
            for d in flt:
                p = (i + d[0], j + d[1])
                if 0 <= p[0] < N and 0 <= p[1] < M:
                    tot += pap[p[0]][p[1]]
                else:
                    break
            result = max([tot, result])

print(result)
