import sys
input = sys.stdin.readline

N, K = map(int, input().split())
words = []

# "antic" 5개는 반드시 포함
prefix = [ord(i)-97 for i in ['a', 'n', 't', 'i', 'c']]
for _ in range(N):
    words.append([ord(i)-97 for i in input().rstrip()][4:-4])

answer = 0


def comb(remain, target, cursor, mask):
    if cursor == target:
        global answer
        now = 0
        for word in words:
            ok = True
            for e in word:
                if not mask[e]:
                    ok = False
                    break
            if ok:
                now += 1
        answer = max([answer, now])
        return
    for idx in range(len(remain)):
        mask[remain[idx]] = True
        comb(remain[idx+1:], target, cursor + 1, mask)
        mask[remain[idx]] = False


if K < 5:
    print(0)
else:
    mask = [False] * 26
    remain = [i for i in range(26)]
    for i in prefix:
        mask[i] = True
        remain.remove(i)
    comb(remain, K-5, 0, mask)
    print(answer)
