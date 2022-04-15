heights = []
results = []


def area(start, end):
    if start >= end:
        return 0
    mid = (start + end) // 2
    min_h = heights[mid]
    mid_area = min_h
    l = mid - 1
    r = mid + 1

    while l >= start or r < end:
        # 왼쪽이 끝인 경우
        if l < start:
            min_h = min(min_h, heights[r])
            r += 1
        # 오론쪽이 끝인 경우
        elif r >= end:
            min_h = min(min_h, heights[l])
            l -= 1
        elif heights[l] > heights[r]:
            min_h = min(min_h, heights[l])
            l -= 1
        else:
            min_h = min(min_h, heights[r])
            r += 1
        mid_area = max(mid_area, (r - l - 1) * min_h)

    return max(area(start, mid), mid_area, area(mid+1, end))


while True:
    heights = [int(i) for i in input().split()]
    if heights[0] == 0:
        break
    else:
        heights.pop(0)
        results.append(area(0, len(heights)))


for r in results:
    print(r)
