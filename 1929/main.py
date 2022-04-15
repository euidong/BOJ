from math import sqrt

vars = [int(i) for i in input().split()]

primes = []
cnt = 0
min_idx = 0

for v in range(2, vars[1]+1):
    is_prime = True
    sqrt_v = sqrt(v)
    for p in primes:
        if p > sqrt_v:
            break
        if v % p == 0:
            is_prime = False
            break
    if is_prime:
        primes.append(v)
        if vars[0] > primes[min_idx]:
            min_idx += 1

for idx in range(min_idx, len(primes)):
    print(primes[idx])
