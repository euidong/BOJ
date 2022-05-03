import sys
input = sys.stdin.readline

sys.setrecursionlimit(10000)

T = int(input())
n = int(input())
A = [int(i) for i in input().split()]
m = int(input())
B = [int(i) for i in input().split()]

result = []


def get_all_cases(arr, idx=0, prev=0):
    if len(arr) == idx:
        return
    cur = prev + arr[idx]
    result.append(cur)
    get_all_cases(arr, idx+1, cur)


for i in range(len(A)):
    get_all_cases(A, i)
subA = sorted(result[:])
result = []

for i in range(len(B)):
    get_all_cases(B, i)
subB = sorted(result)


def upper_bound(v):
    start = 0
    end = len(subB) - 1

    while end > start:
        mid = (start + end) // 2
        if subB[mid] > v:
            end = mid
        else:
            start = mid + 1
    if v == subB[end]:
        return len(subB)
    return end


def lower_bound(v):
    start = 0
    end = len(subB) - 1

    while end > start:
        mid = (start + end) // 2
        if subB[mid] >= v:
            end = mid
        else:
            start = mid + 1
    if v != subB[end]:
        return -1
    return end


answer = 0
for v in subA:
    target = T - v
    lb = lower_bound(target)
    if lb != -1:
        answer += upper_bound(target) - lb

print(answer)
