import sys
input = sys.stdin.readline

N = int(input())

gears = [None]

for _ in range(N):
    gears.append([int(i) for i in input().rstrip()])

K = int(input())
cmds = []
for _ in range(K):
    cmds.append([int(i) for i in input().split()])


def rotate(gear, direction=1):
    if direction == 1:
        temp = [gear[-1]] + gear[0:-1]
    else:
        temp = gear[1:] + [gear[0]]
    return temp


for cmd in cmds:
    targetIdx, direction = cmd
    candi = [(targetIdx, direction)]
    cursor = targetIdx + 1
    temp_direction = -direction
    while cursor < len(gears):
        if gears[cursor][-2] == gears[cursor-1][2]:
            break
        candi.append((cursor, temp_direction))
        temp_direction *= -1
        cursor += 1
    cursor = targetIdx - 1
    temp_direction = -direction
    while cursor > 0:
        if gears[cursor][2] == gears[cursor+1][-2]:
            break
        candi.append((cursor, temp_direction))
        temp_direction *= -1
        cursor -= 1
    for cand in candi:
        gears[cand[0]] = rotate(gears[cand[0]], cand[1])

answer = 0
for gear in gears[1:]:
    if gear[0] == 1:
        answer += 1

print(answer)
