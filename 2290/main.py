s, n = input().split()
s = int(s)

width = s+2
height = 2 * s + 3

board = ["" for _ in range(height)]


parts = [
    ["".rjust(width)],
    [" " + "".rjust(width-2, "-") + " "],
    ["|" + "".rjust(width - 2) + "|"] * s,
    ["|".rjust(width)] * s,
    ["|".ljust(width)] * s
]


def append(num):
    if num == 1:
        series = [0, 3, 0, 3, 0]
    elif num == 2:
        series = [1, 3, 1, 4, 1]
    elif num == 3:
        series = [1, 3, 1, 3, 1]
    elif num == 4:
        series = [0, 2, 1, 3, 0]
    elif num == 5:
        series = [1, 4, 1, 3, 1]
    elif num == 6:
        series = [1, 4, 1, 2, 1]
    elif num == 7:
        series = [1, 3, 0, 3, 0]
    elif num == 8:
        series = [1, 2, 1, 2, 1]
    elif num == 9:
        series = [1, 2, 1, 3, 1]
    else:
        series = [1, 2, 0, 2, 1]
    cnt = 0
    for s in series:
        for i in parts[s]:
            board[cnt] += i
            cnt += 1


for i in n:
    append(int(i))
    for j in range(height):
        board[j] += " "

for line in board:
    print(line)
