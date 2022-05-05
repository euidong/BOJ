N = int(input())
series = [int(i) for i in input().split()]


unused_num = []

while True:
    if len(series) == 1:
        print(-1)
        break
    unused_num.append(series.pop(-1))
    unused_num.sort()
    is_finish = False
    for idx in range(len(unused_num)):
        if unused_num[idx] > series[-1]:
            cur_num = series.pop(-1)
            pop_num = unused_num.pop(idx)
            unused_num.append(cur_num)
            remain = sorted(unused_num)
            print(' '.join([str(i) for i in series + [pop_num] + remain]))
            is_finish = True
            break
    if is_finish:
        break
