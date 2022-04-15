def permutation_helper(k, arr=[], prev=[]):
    if len(prev) == k:
        return [prev]
    ss = []
    for idx in range(len(arr)):
        ss += permutation_helper(k, arr[:idx] + arr[idx+1:], prev + [arr[idx]])
    return ss


def permutation(n, k):
    arr = [i for i in range(1, n+1)]
    return permutation_helper(k, arr, [])


def combination_helper(k, arr=[], prev=[]):
    if len(prev) == k:
        return [prev]
    ss = []
    for idx in range(len(arr)):
        ss += combination_helper(k, arr[idx+1:], prev + [arr[idx]])
    return ss


def combination(n, k):
    arr = [i for i in range(1, n+1)]
    return combination_helper(k, arr, [])


def subset_helper(k, arr=[], prev=[]):
    if len(prev) == k:
        return []
    ss = []
    for idx in range(len(arr)):
        ss.append(prev + [arr[idx]])
        ss += subset_helper(k, arr[idx+1:], prev + [arr[idx]])
    return ss


def subset(n, k):
    arr = [i for i in range(1, n+1)]
    return subset_helper(k, arr, [])


print(permutation(10, 5))
print(combination(10, 5))
print(subset(4, 2))
