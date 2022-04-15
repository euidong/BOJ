arr = [2, 1, 7, 4, 3, 8, 4, 9, 1]
seg_tree = []


def init_seg_tree():
    pow2 = 1
    while pow2 < len(arr):
        pow2 <<= 1
    return [0 for _ in range(pow2 * 2 - 1)]


def fill_seg_tree(start=0, end=len(arr) - 1, idx=1):
    if start == end:
        seg_tree[idx] = arr[start]
        return seg_tree[idx]

    mid = (start + end) // 2
    left = fill_seg_tree(start, mid, idx * 2)
    right = fill_seg_tree(mid + 1, end, idx * 2 + 1)
    seg_tree[idx] = left + right
    return seg_tree[idx]


# seg_start, seg_end 는 현재 index에서 갖고있는 데이터의 범위를 의미합니다.
# target_start, target_end는 호출자가 찾고 싶은 데이터의 범위를 의미합니다.
def find_sum(target_start, target_end, seg_start=0, seg_end=len(arr) - 1, idx=1):
    # out of bound
    if target_start > seg_end or target_end < seg_start:
        return 0
    # include all element
    if target_start <= seg_start and target_end >= seg_end:
        return seg_tree[idx]

    mid = (seg_start + seg_end) // 2
    left = find_sum(target_start, target_end, seg_start, mid, idx * 2)
    right = find_sum(target_start, target_end, mid + 1, seg_end, idx * 2 + 1)
    return left + right


def update(target_idx, diff, start=0, end=len(arr) - 1, idx=1):
    if target_idx < start or target_idx > end:
        return
    seg_tree[idx] += diff
    if start != end:
        mid = (start + end) // 2
        update(target_idx, diff, start, mid, idx * 2)
        update(target_idx, diff, mid + 1, end, idx * 2 + 1)


seg_tree = init_seg_tree()
fill_seg_tree()
print(seg_tree)
print(find_sum(5, 8))
update(3, 5)
print(seg_tree)
