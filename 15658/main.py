N = input()
A = [int(i) for i in input().split()]
ops = [int(i) for i in input().split()]
# 0 = +, 1 = -, 2 = x, 3 = /

answer = []


def solve(idx, ops, prev_result):
    if idx == len(A):
        answer.append(prev_result)
        return
    for i in range(4):
        if ops[i] > 0:
            if i == 0:
                result = prev_result + A[idx]
            elif i == 1:
                result = prev_result - A[idx]
            elif i == 2:
                result = prev_result * A[idx]
            else:
                if prev_result < 0:
                    result = -((-prev_result) // A[idx])
                else:
                    result = prev_result // A[idx]
            next_ops = ops[:]
            next_ops[i] -= 1
            solve(idx + 1, next_ops, result)


solve(1, ops, A[0])

print(max(answer))
print(min(answer))
