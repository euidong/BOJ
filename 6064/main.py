T = int(input())
for i in range(T):
    M, N, x, y = [int(i) for i in input().split()]
    k = [0, 0]

    first_result = y - x
    same_cnt = 0
    while True:
        Y1 = k[0] * M + x
        Y2 = k[1] * N + y
        if Y1 == Y2:
            print(Y1)
            break
        elif Y1 > Y2:
            k[1] += 1
        else:
            k[0] += 1
        if first_result == Y2 - Y1:
            same_cnt += 1
            if same_cnt > 2:
                print(-1)
                break
