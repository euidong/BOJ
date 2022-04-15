N = int(input())
words = []
for _ in range(N):
    words.append(input())

count = 0

words = [(word, idx)
         for idx, word in enumerate(sorted(words, key=lambda x: x[::-1]))]

words = sorted(words)

fenwick_tree = [0 for _ in range(N + 1)]


def query(idx=1):
    tot = 0
    while(idx > 0):
        tot += fenwick_tree[idx]
        idx = idx - (idx & -idx)
    return tot


def update(value, idx=1):
    while (idx < len(fenwick_tree)):
        fenwick_tree[idx] = fenwick_tree[idx] + value
        idx = idx + (idx & -idx)


for word, idx in words:
    count += query(N) - query(idx)
    update(1, idx + 1)

print(count)
