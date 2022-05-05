import sys
input = sys.stdin.readline
N, M, R = map(int, input().split())
arr = []

for i in range(N):
    arr.append([int(i) for i in input().split()])

cmds = [int(i) for i in input().split()]


def op1(arr):
    temp = [[-1 for _ in range(len(arr[0]))] for _ in range(len(arr))]
    for i in range(len(arr)):
        temp[-i-1] = arr[i][:]
    return temp


def op2(arr):
    temp = [[-1 for _ in range(len(arr[0]))] for _ in range(len(arr))]
    for i in range(len(arr)):
        for j in range(len(arr[0])):
            temp[i][-j-1] = arr[i][j]
    return temp


def op3(arr):
    temp = [[-1 for _ in range(len(arr))] for _ in range(len(arr[0]))]
    for i in range(len(arr)):
        for j in range(len(arr[0])):
            temp[j][-i-1] = arr[i][j]
    return temp


def op4(arr):
    temp = [[-1 for _ in range(len(arr))] for _ in range(len(arr[0]))]
    for i in range(len(arr)):
        for j in range(len(arr[0])):
            temp[-j-1][i] = arr[i][j]
    return temp


def op5(arr):
    N = len(arr)
    M = len(arr[0])
    temp = [[-1 for _ in range(M)] for _ in range(N)]
    sub = []
    sub.append([arr[i][0:M//2] for i in range(N//2, N)])  # 2
    sub.append([arr[i][0:M//2] for i in range(N//2)])  # 0
    sub.append([arr[i][M//2:M] for i in range(N//2, N)])  # 3
    sub.append([arr[i][M//2:M] for i in range(N//2)])  # 1
    for i in range(N//2):
        for j in range(M//2):
            temp[i][j] = sub[0][i][j]
            temp[i][j + M//2] = sub[1][i][j]
            temp[i + N//2][j] = sub[2][i][j]
            temp[i + N//2][j + M//2] = sub[3][i][j]
    return temp


def op6(arr):
    N = len(arr)
    M = len(arr[0])
    temp = [[-1 for _ in range(M)] for _ in range(N)]
    sub = []
    sub.append([arr[i][M//2:M] for i in range(N//2)])  # 1
    sub.append([arr[i][M//2:M] for i in range(N//2, N)])  # 3
    sub.append([arr[i][0:M//2] for i in range(N//2)])  # 0
    sub.append([arr[i][0:M//2] for i in range(N//2, N)])  # 2
    for i in range(N//2):
        for j in range(M//2):
            temp[i][j] = sub[0][i][j]
            temp[i][j + M//2] = sub[1][i][j]
            temp[i + N//2][j] = sub[2][i][j]
            temp[i + N//2][j + M//2] = sub[3][i][j]
    return temp


for cmd in cmds:
    if cmd == 1:
        arr = op1(arr)
    elif cmd == 2:
        arr = op2(arr)
    elif cmd == 3:
        arr = op3(arr)
    elif cmd == 4:
        arr = op4(arr)
    elif cmd == 5:
        arr = op5(arr)
    else:
        arr = op6(arr)

for i in range(len(arr)):
    print(' '.join([str(k) for k in arr[i]]))
