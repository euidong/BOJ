N = int(input())
parents = [int(i) for i in input().split(' ')]

tree = [[] for _ in range(N)]

for idx, parent in enumerate(parents):
    if parent == -1:
        continue
    tree[parent].append(idx)

k = int(input())
print(tree)

tree = [list(filter(lambda x: x != k, t)) for t in tree]

print(tree)
q = []
q.append(k)
while len(q) != 0:
    k = q[0]
    q.pop(0)
    for i in tree[k]:
        q.append(i)
    tree[k] = None

print(tree)
leaf = 0
for t in tree:
    if t != None and len(t) == 0:
        leaf += 1

print(leaf)
