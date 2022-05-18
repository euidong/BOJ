# cache[1] = 1
# cache[2] = 2
# cache[3] = 3
# cache[4] = 4
# cache[5] = 5
# cache[6] = 6
# cache[7] = 9
# cache[8] = 12
# cache[9] = 15
# cache[10] = 18
# cache[11] = 27
# cache[12] = 36
# cache[13] = 45
# cache[14] = 54

# clipboard = 1
# cache[n] = max([cache[n-1] + clipboard, cache[n-3] * 2, cache[n-4] * 3, cache[n-5] * 4, ...])


N = int(input())
clipboard = 1
cache = [0] * 101
cache[0] = (0, 0)
cache[1] = (1, 0)
cache[2] = (2, 0)
cache[3] = (3, 0)
cache[4] = (4, 0)
cache[5] = (5, 0)
cache[6] = (6, 0)
for i in range(6, N+1):
    max_j = 2
    for j in range(3, i):
        if cache[i-max_j-1][0] * max_j < cache[i-j-1][0] * j:
            max_j = j
    
    if cache[i-1][0] + cache[i-1][1] >= cache[i-2][0] + cache[i-2][1] * 2:
        cand = (cache[i-1][0] + cache[i-1][1], cache[i-1][1])
    else:
        cand = (cache[i-2][0] + cache[i-2][1] * 2, cache[i-2][1])  
    if cand[0] <= cache[i-max_j-1][0] * max_j:
        cache[i] = (cache[i-max_j-1][0] * max_j, cache[i-max_j-1][0])
    else:
        cache[i] = cand
print(cache[N][0])
