N = int(input())

cache = [-1] * 91

cache[1] = 1
cache[2] = 1


def pibo(a):
    if cache[a] == -1:
        cache[a] = pibo(a-1) + pibo(a-2)
    return cache[a]


print(pibo(N))
