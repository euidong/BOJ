from math import sqrt

N = int(input())

MAX_N = 4_000_000


primes = []
is_primes = [True] * (N+1)

for num in range(2, N+1):
    if not is_primes[num]:
        continue
    primes.append(num)
    for j in range(2 * num, N+1, num):
        is_primes[j] = False
answer = 0
for idx in range(len(primes)):
    cursor = idx
    acc = 0
    while acc < N:
        if cursor == len(primes):
            break
        acc += primes[cursor]
        cursor += 1
    if acc == N:
        answer += 1

print(answer)
