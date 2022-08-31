import sys
input = sys.stdin.readline

R, C, M = map(int, input().split())

sharks = {}
for _ in range(M):
    shark = input().split()
    key = ' '.join(shark[:2])
    sharks[key] = [int(i) for i in shark]

answer = 0

cur = 1
while cur <= C:
    for i in range(1, R+1):
        key = ' '.join([str(i), str(cur)])
        catched_shark = sharks.get(key)
        if catched_shark != None:
            answer += catched_shark[4]
            sharks.pop(key)
            break
    new_sharks = {}
    for key, shark in sharks.items():
        r, c, s, d, z = shark
        if d == 1:
            if r - s < 1:
                remain = s - (r - 1)
                remain %= 2*(R-1)
                if remain == 0:
                    d = 1
                    r = 1
                elif remain // (R-1) == 1:
                    d = 1
                    r = R - (remain % (R-1))
                else:
                    d = 2
                    r = 1 + (remain % (R-1))
            else:
                r -= s
        elif d == 2:
            if r + s > R:
                remain = s - (R - r)
                remain %= 2*(R-1)
                if remain == 0:
                    d = 2
                    r = R
                elif remain // (R-1) == 1:
                    d = 2
                    r = 1 + (remain % (R-1))
                else:
                    d = 1
                    r = R - (remain % (R-1))
            else:
                r += s
        elif d == 3:
            if c + s > C:
                remain = s - (C - c)
                remain %= 2*(C-1)
                if remain == 0:
                    d = 3
                    c = C
                elif remain // (C-1) == 1:
                    d = 3
                    c = 1 + (remain % (C-1))
                else:
                    d = 4
                    c = C - (remain % (C-1))
            else:
                c += s
        else:
            if c - s < 1:
                remain = s - (c - 1)
                remain %= 2*(C-1)
                if remain == 0:
                    d = 4
                    c = 1
                elif remain // (C-1) == 1:
                    d = 4
                    c = C - (remain % (C-1))
                else:
                    d = 3
                    c = 1 + (remain % (C-1))
            else:
                c -= s

        new_key = ' '.join([str(r), str(c)])
        prev_shark = new_sharks.get(new_key)
        if prev_shark != None and prev_shark[4] > z:
            pass
        else:
            new_sharks[new_key] = [r, c, s, d, z]

    sharks = new_sharks
    cur += 1

print(answer)
