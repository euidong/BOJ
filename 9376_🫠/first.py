# 각 prison에 대해서 각 각 아래 과정을 수행
# 1. 현재 두 prisoner가 탈출로를 찾을 수 있는지 확인
# => dfs (visited는 별도로 사용하여 수행, 이 과정에서 벽이 있는 리스트도 저장)
# 2. 찾을 수 없다면, 각자 벽을 하나 뚫는 경우의 수를 모두 bfs queue에 저장

from collections import deque
import sys
input = sys.stdin.readline

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]


def find_door(prisoner, board):
    h = len(board)
    w = len(board[0])
    doors = []
    q = deque([prisoner])
    visited = [[False for _ in range(w)] for _ in range(h)]
    visited[prisoner[0]][prisoner[1]] = True
    while len(q) > 0:
        y, x = q.popleft()
        for i in range(4):
            a = y + dy[i]
            b = x + dx[i]
            if -1 < a < h and -1 < b < w and not visited[a][b]:
                visited[a][b] = True
                if board[a][b] == '#':
                    doors.append((a, b))
                elif board[a][b] == '.' or board[a][b] == '$':
                    if a == 0 or a == h-1 or b == 0 or b == w - 1:
                        return None
                    q.append((a, b))
    return doors


T = int(input())
answers = []
for _ in range(T):
    h, w = map(int, input().split())
    board = []
    prisoner = []
    for i in range(h):
        board.append([i for i in input().rstrip()])
        for j in range(w):
            if board[i][j] == '$':
                prisoner.append((i, j))

    # 번갈아가면서, 이동시켜본다.
    q = deque([([])])
    visited = {}
    while len(q) > 0:
        opend_doors = q.popleft()
        new_board = [line[:] for line in board]
        for y, x in opend_doors:
            new_board[y][x] = '.'
        adj_doors = set()
        doors1 = find_door(prisoner[0], new_board)
        if doors1 != None:
            adj_doors = set(doors1)
        doors2 = find_door(prisoner[1], new_board)
        if doors2 != None:
            adj_doors = adj_doors.union(doors2)
        if doors1 is None and doors2 is None:
            answers.append(len(opend_doors))
            break
        for door in adj_doors:
            next = sorted(opend_doors + [door])
            key = ''.join([str(y) + '-' + str(x) for y, x in next])
            if visited.get(key) == None:
                visited.update({key: True})
                q.append(next)

for answer in answers:
    print(answer)
