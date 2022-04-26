import sys
input = sys.stdin.readline

N, R = map(int, input().split())
size = 2 ** N
arr = []
for _ in range(size):
    arr.append([int(i) for i in input().split()])
cmds = []
for _ in range(R):
    cmds.append([int(i) for i in input().split()])

while len(cmds) > 0:
    k, e = cmds.pop(0)
    s_size = 2 ** e
    ss_arr = []
    for i in range(size // s_size):
        ss_line = []
        for j in range(size // s_size):
            ss = []
            for n in range(s_size):
                line = []
                for m in range(s_size):
                    line.append(arr[i * s_size + n][j * s_size + m])
                ss.append(line)
            ss_line.append(ss)
        ss_arr.append(ss_line)
    if k == 1:
        for i in range(size // s_size):
            for j in range(size // s_size):
                for n in range(s_size // 2):
                    ss_arr[i][j][n], ss_arr[i][j][-n - 1] = \
                        ss_arr[i][j][-n-1][:], ss_arr[i][j][n][:]
    elif k == 2:
        for i in range(size // s_size):
            for j in range(size // s_size):
                for n in range(s_size):
                    for m in range(s_size // 2):
                        ss_arr[i][j][n][m], ss_arr[i][j][n][-m-1] = \
                            ss_arr[i][j][n][-m-1], ss_arr[i][j][n][m]
    elif k == 3:
        for i in range(size // s_size):
            for j in range(size // s_size):
                temp = [[0 for _ in range(s_size)] for _ in range(s_size)]
                for n in range(s_size):
                    for m in range(s_size):
                        temp[n][m] = ss_arr[i][j][s_size - 1 - m][n]
                ss_arr[i][j] = temp
    elif k == 4:
        for i in range(size // s_size):
            for j in range(size // s_size):
                temp = [[0 for _ in range(s_size)] for _ in range(s_size)]
                for n in range(s_size):
                    for m in range(s_size):
                        temp[n][m] = ss_arr[i][j][m][s_size - 1 - n]
                ss_arr[i][j] = temp
    elif k == 5:
        for i in range(size // s_size // 2):
            ss_arr[i], ss_arr[-i-1] = ss_arr[-i-1][:], ss_arr[i][:]
    elif k == 6:
        for i in range(size // s_size):
            for j in range(size // s_size // 2):
                ss_arr[i][j], ss_arr[i][-j -
                                        1] = ss_arr[i][-j-1], ss_arr[i][j]
    elif k == 7:
        temp = [[None for _ in range(size // s_size)]
                for _ in range(size // s_size)]
        for n in range(size // s_size):
            for m in range(size // s_size):
                temp[n][m] = ss_arr[size // s_size - 1 - m][n]
        ss_arr = temp
    elif k == 8:
        temp = [[None for _ in range(size // s_size)]
                for _ in range(size // s_size)]
        for n in range(size // s_size):
            for m in range(size // s_size):
                temp[n][m] = ss_arr[m][size // s_size - 1 - n]
        ss_arr = temp
    for i in range(size // s_size):
        for j in range(size // s_size):
            for n in range(s_size):
                for m in range(s_size):
                    arr[i * s_size + n][j * s_size + m] = ss_arr[i][j][n][m]


for i in range(size):
    print(" ".join([str(num) for num in arr[i]]))
