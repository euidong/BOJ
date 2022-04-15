T = int(input())


def checker(remain):
    cnt = 0
    for i in range(1, 4):
        if remain - i > 0:
            cnt += checker(remain - i)
        elif remain - i == 0:
            cnt += 1
    return cnt


for _ in range(T):
    N = int(input())
    print(checker(N))
