primes = [True] * 1000001
primes[0] = False
primes[1] = False
for i in range(4, 1000001, 2):
    primes[i] = False
cache = [0] * 2000001

cnt = 3
odd_primes = []
while cnt < len(primes):
    if primes[cnt]:
        idx = 2
        num = cnt * idx
        while num < len(primes):
            primes[num] = False
            idx += 1
            num = cnt * idx
        odd_primes.append(cnt)
    cnt += 2

while True:
    N = int(input())
    if N == 0:
        break
    for p in odd_primes:
        if primes[N-p]:
            print('{} = {} + {}'.format(str(N), str(p), str(N-p)))
            break
