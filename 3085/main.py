N = int(input())
board = []
for _ in range(N):
    board.append(list(input()))

dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]


max_value = 0
for y in range(N):
    for x in range(N):
        for j in range(4):
            b = y + dy[j]
            a = x + dx[j]
            if 0 <= a < N and 0 <= b < N:
                temp = board[y][x]
                board[y][x] = board[b][a]
                board[b][a] = temp
                for k in range(N):
                    prev_x = None
                    x_cnt = 0
                    prev_y = None
                    y_cnt = 0
                    for h in range(N):
                        if prev_x == board[k][h]:
                            x_cnt += 1
                        else:
                            x_cnt = 1
                            prev_x = board[k][h]

                        if prev_y == board[h][k]:
                            y_cnt += 1
                        else:
                            y_cnt = 1
                            prev_y = board[h][k]
                        max_value = max([x_cnt, y_cnt, max_value])
                    if x_cnt == N or y_cnt == N:
                        break
                board[b][a] = board[y][x]
                board[y][x] = temp

print(max_value)
