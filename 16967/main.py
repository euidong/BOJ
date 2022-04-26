import sys
input = sys.stdin.readline

H, W, X, Y = map(int, input().split())

B = []
for _ in range(H+X):
    B.append([int(i) for i in input().split()])

A = [[-1 for _ in range(W)] for _ in range(H)]

for i in range(X):
    for j in range(W):
        A[i][j] = B[i][j]

for i in range(H):
    for j in range(Y):
        A[i][j] = B[i][j]

for i in range(X, H):
    for j in range(W, W+Y):
        A[i-X][j-Y] = B[i][j]

for i in range(H, H+X):
    for j in range(Y, W+Y):
        A[i-X][j-Y] = B[i][j]

for i in range(X, H-X):
    for j in range(Y, W-Y):
        A[i][j] = B[i][j] - A[i-X][j-Y]

for line in A:
    print(" ".join([str(i) for i in line]))
