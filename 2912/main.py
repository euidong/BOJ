def upperbound(arr, target):
    start = 0
    end = len(arr)
    while start != end:
        mid = (end + start) // 2
        if arr[mid] > target:
            end = mid
        elif arr[mid] < target:
            start = mid + 1
        else:
            return mid + 1
    return start


def lowerbound(arr, target):
    start = 0
    end = len(arr)
    while start != end:
        mid = (end + start) // 2
        if arr[mid] > target:
            end = mid
        elif arr[mid] < target:
            start = mid + 1
        else:
            return mid
    return start


N, C = [int(i) for i in input().split()]
dwarfs = [int(i) for i in input().split()]
colors = [[] for _ in range(C + 1)]

for dwarf_idx, color in enumerate(dwarfs):
    colors[color].append(dwarf_idx)

for color in colors:
    color.sort()

seg_tree = [-1] * (N * 4)


def make(idx, left, right):
    if left == right:
        seg_tree[idx] = dwarfs[left]
        return

    mid = (left+right) // 2
    make(idx*2, left, mid)
    make(idx*2+1, mid+1, right)
    lc = seg_tree[idx*2]
    cnt = upperbound(colors[lc], right) - lowerbound(colors[lc], left) + 1
    if cnt > (right-left+1) // 2:
        seg_tree[idx] = lc
        return

    lc = seg_tree[idx*2+1]
    cnt = upperbound(colors[lc], right) - lowerbound(colors[lc], left) + 1
    if cnt > (right-left+1) // 2:
        seg_tree[idx] = lc
        return
    seg_tree[idx] = -1


def segTree(idx, left, right, start, end):
    if right < start or end < left:
        return 0
    if start >= left and right >= end:
        cnt = upperbound(colors[seg_tree[idx]], right) - \
            lowerbound(colors[seg_tree[idx]], left)
        if cnt > (right-left+1) // 2:
            return seg_tree[idx]
        else:
            return 0
    mid = (start + end) // 2
    one = segTree(idx*2, left, right, start, mid)
    if one > 0:
        return one
    two = segTree(idx*2+1, left, right, mid+1, end)
    if two > 0:
        return two
    return 0


make(1, 0, N-1)

result = []
M = int(input())

for _ in range(M):
    a, b = [int(i) for i in input().split()]
    result.append(segTree(1, a-1, b-1, 0, N-1))

for r in result:
    if r > 0:
        print("yes", r)
    else:
        print("no")


# def make(t_st, t_ed, s_st=0, s_ed=N-1, idx=1):
#     if s_st == s_ed:
#         seg_tree[idx] = dwarfs[s_st]
#         return seg_tree[idx]

#     mid = (s_st + s_ed) // 2
#     left = make(t_st, t_ed, s_st, mid, idx * 2)
#     if left != None:
#         cnt = upperbound(colors[left][s_st:s_ed], t_ed) - \
#             lowerbound(colors[left][s_st:s_ed], t_st)
#         if cnt > (s_ed - s_st + 1) // 2:
#             seg_tree[idx] = left
#             return seg_tree[idx]
#     right = make(t_st, t_ed, mid + 1, s_ed, idx * 2 + 1)
#     if right != None:
#         cnt = upperbound(colors[right][s_st:s_ed], t_ed) - \
#             lowerbound(colors[right][s_st:s_ed], t_st)
#         if cnt > (s_ed - s_st + 1) // 2:
#             seg_tree[idx] = right
#             return seg_tree[idx]


# def query(t_st, t_ed, s_st=0, s_ed=N-1, idx=1):
#     if t_st > s_ed or t_ed < s_st:
#         return -1
#     if t_st <= s_st and t_ed >= s_ed:
#         return seg_tree[idx]

#     mid = (s_st + s_ed) // 2
#     left = query(t_st, t_ed, s_st, mid, idx * 2)
#     if left != -1:
#         cnt = upperbound(colors[left][s_st:s_ed], t_ed) - \
#             lowerbound(colors[left][s_st:s_ed], t_st)
#         if cnt > (t_ed - t_st + 1) // 2:
#             return left
#     right = query(t_st, t_ed, mid + 1, s_ed, idx * 2 + 1)
#     if right != -1:
#         cnt = upperbound(colors[right][s_st:s_ed], t_ed) - \
#             lowerbound(colors[right][s_st:s_ed], t_st)
#         if cnt > (t_ed - t_st + 1) // 2:
#             return right
#     return -1


# make(0, N-1)

# M = int(input())
# result = []
# for _ in range(M):
#     a, b = [int(i) for i in input().split()]
#     result.append(query(a-1, b-1))

# for r in result:
#     if r != -1:
#         print("yes", r)
#     else:
#         print("no")
