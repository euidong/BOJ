import sys
input = sys.stdin.readline
N, S = map(int, input().split())
series = [int(i) for i in input().split()]
answer = 0
case = [[], []]


def solve(case, max, idx=0, acc=0):
    global answer
    if idx == max:
        return
    solve(case, max, idx+1, acc)
    temp = acc + series[idx]
    case.append(temp)
    if temp == S:
        answer += 1
    solve(case, max, idx+1, temp)


solve(case[0], N // 2)
solve(case[1], N, N//2)

case[0] = sorted(case[0])
case[1] = sorted(case[1])

cursor = 0

if len(case[0]) == 0 or len(case[1]) == 0:
    print(answer)
    sys.exit()

while case[1][cursor] <= S - case[0][0]:
    cursor += 1
    if len(case[1]) == cursor:
        break
if cursor == len(case[1]):
    cursor -= 1


for idx in range(len(case[0])):
    target = S - case[0][idx]
    while case[1][cursor] > target:
        if cursor == 0:
            break
        cursor -= 1
    if case[1][cursor] == target:
        answer += 1
        # 중복 수가 있다면, 그것도 카운팅
        if idx > 0 and case[0][idx] == case[0][idx - 1]:
            answer += same_cnt
        else:
            next = cursor - 1
            while next > -1 and case[1][cursor] == case[1][next]:
                next -= 1
            same_cnt = cursor - next - 1
            answer += same_cnt
            cursor = next + 1


print(answer)

# 40 0
# 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

# 40 50
# -19 -18 -17 -16 -15 -14 -13 -12 -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

# 30 40
# -14 -13 -12 -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

# 20 20
# -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10
