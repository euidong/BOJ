N = int(input())
pap = []

# 0(-1 + 1), 1(0 + 1), 2(1 + 1)
count = [0, 0, 0]

for i in range(N):
    line = []
    for inp in input().split(' '):
        line.append(int(inp))
        count[int(inp)] += 1
    pap.append(line)

while len(pap) != 1:
    size = len(pap)
    new_pap = [[None for _ in range(size//3)]
               for _ in range(size // 3)]
    for n in range(size // 3):
        for m in range(size // 3):
            b = n * 3
            a = m * 3
            v = pap[b][a]
            diff = False
            for i in range(3):
                for j in range(3):
                    if pap[b+i][a+j] != v:
                        diff = True
            if not diff and v != None:
                new_pap[n][m] = v
                count[v] -= 8
    pap = new_pap

for i in range(-1, 2):
    print(count[i])
