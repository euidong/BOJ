import sys

while True:
    try:
        input = sys.stdin.readline()
        A = int(input.rstrip())
    except ValueError:
        break
    cnt = 1
    remain = 0
    while True:
        remain = remain * 10 + 1
        remain %= A
        if remain == 0:
            print(cnt)
            break
        cnt += 1
