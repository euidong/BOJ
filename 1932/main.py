import sys
row = int(sys.stdin.readline())
tri = [[0]]
for _ in range(row):
    tri.append([0] + [int(i) for i in sys.stdin.readline().split()] + [0])

cache = [[0 for _ in range(row + 1)] for _ in range(row + 1)]

for i in range(1, row+1):
    for j in range(1, i+1):
        cache[i][j] = max([cache[i-1][j-1], cache[i-1][j]]) + tri[i][j]

print(max(cache[row]))
