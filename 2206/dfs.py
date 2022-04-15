
MAX_DIST = 1000 * 1000

map = []
cache = []

target = (0, 0)


directions = {
    0: [0, -1],  # left
    1: [-1, 0],  # up
    2: [0, 1],  # right
    3: [1, 0],  # down
}


def dfs(cur_x, cur_y, num_wall, block_direc):
    min_dist = MAX_DIST
    if cur_x == 0 and cur_y == 0:
        return 1

    if map[cur_y][cur_x] == '1':
        if num_wall > 0:
            num_wall -= 1
        else:
            return -1

    for k, v in directions.items():
        if k == block_direc:
            continue
        if  \
                (k == 0 and 0 < cur_x) \
                or (k == 1 and 0 < cur_y) \
                or (k == 2 and len(map[0]) - 1 > cur_x) \
                or (k == 3 and len(map) - 1 > cur_y):
            if cache[cur_y + v[0]][cur_x + v[1]][num_wall][k] != 0:
                dist = cache[cur_y + v[0]][cur_x + v[1]][num_wall][k]
            else:
                dist = dfs(cur_x + v[1], cur_y + v[0], num_wall, (k + 2) % 4)
            if dist != -1 and dist < min_dist:
                min_dist = dist
    if min_dist == MAX_DIST:
        result = -1
    else:
        result = min_dist + 1
    cache[cur_y][cur_x][num_wall][k] = result
    return result


[size_y, size_x] = [int(i) for i in input().split(' ')]

for _ in range(size_y):
    map.append(input())

cache = [[[[0] * 4] * 2] * size_x] * size_y

print(dfs(size_x - 1, size_y - 1, 1, 3))
