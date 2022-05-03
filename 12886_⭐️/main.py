import sys

A, B, C = map(int, sys.stdin.readline().split())

if A == B == C:
    print(1)
    sys.exit()

SUM = A+B+C

visited = [[False for _ in range(SUM + 1)] for _ in range(SUM + 1)]

q = [(A, B)]
visited[A][B] = True
visited[A][C] = True
visited[B][C] = True


def op(a, b):
    if a > b:
        return a - b, b * 2
    elif a < b:
        return a * 2, b - a
    else:
        return None


def check(a, b, c):
    if a == b == c:
        print(1)
        sys.exit()
    else:
        if not visited[a][b]:
            visited[a][b] = True
            visited[a][c] = True
            visited[b][c] = True
            q.append((a, b))


while len(q) > 0:
    A, B = q.pop(0)
    C = SUM - A - B
    if A != B:
        a, b = op(A, B)
        c = SUM - a - b
        check(a, b, c)

    if A != C:
        a, c = op(A, C)
        b = SUM - a - c
        check(a, b, c)

    if B != C:
        b, c = op(B, C)
        a = SUM - b - c
        check(a, b, c)

print(0)
