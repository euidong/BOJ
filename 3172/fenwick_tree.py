arr = [2, 1, 7, 4, 3, 8, 4, 9, 1]
fenwick_tree = [0 for _ in range(len(arr) + 1)]


# num & (-num) = 1의 최하위 bit 위치만 켜짐
def update(idx, value):
    while (idx < len(fenwick_tree)):
        fenwick_tree[idx] = fenwick_tree[idx] + value
        idx = idx + (idx & -idx)


def make_fenwick_tree():
    for idx in range(len(arr)):
        update(idx + 1, arr[idx])


def sum(idx):
    tot = 0
    while(idx > 0):
        tot += fenwick_tree[idx]
        idx = idx - (idx & -idx)
    return tot
