target = int(input())
now = 100
num_lost = int(input())
lost_btns = []
if num_lost != 0:
    lost_btns = [int(i) for i in input().split()]
btns = [True] * 10
for i in lost_btns:
    btns[i] = False

q = []
q.append((target, 0))

now_dist = abs(target - now)
if len(lost_btns) == 10:
    print(now_dist)
else:
    while True:
        num, cnt = q.pop(0)
        is_eq = True
        for i in str(num):
            if not btns[int(i)]:
                is_eq = False
                break
        if is_eq:
            print(min([cnt + len(str(num)), now_dist]))
            break
        else:
            if 0 < num <= target:
                q.append((num - 1, cnt + 1))
            if num >= target:
                q.append((num + 1, cnt + 1))
