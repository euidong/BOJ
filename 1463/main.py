N = int(input())
MAX_NUM = 1_000_001
cache = [MAX_NUM] * MAX_NUM
cache[0] = 0
cache[1] = 0
cache[2] = 1
cache[3] = 1

stack = [N]
while len(stack) != 0:
    now = stack.pop()
    if cache[now] != MAX_NUM:
        continue
    stack.append(now)
    cand = []
    if now % 3 == 0:
        if cache[now//3] == MAX_NUM:
            stack.append(now//3)
            continue
        cand.append(cache[now//3])
    if now % 2 == 0:
        if cache[now//2] == MAX_NUM:
            stack.append(now//2)
            continue
        cand.append(cache[now//2])
    if cache[now - 1] == MAX_NUM:
        stack.append(now-1)
        continue
    cand.append(cache[now-1])
    cache[now] = min(cand) + 1

print(cache[N])
