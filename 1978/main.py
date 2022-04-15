NUM = int(input())
vars = [int(i) for i in input().split()]

cnt = 0
for v in vars:
    if v == 2:
        cnt += 1
        continue
    if v % 2 == 0 or v == 1:
        continue
    is_prime = True
    for i in range(3, v, 2):
        if v % i == 0:
            is_prime = False
            break
    if is_prime:
        cnt += 1
print(cnt)
