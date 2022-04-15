N = int(input())
sign = input()
matrix = []
cnt = 0
matrix.append([0] * (N + 1))
for i in range(N):
    line = []
    for j in range(i, N):
        line.append(sign[cnt])
        cnt += 1
    matrix.append(([0] * (i + 1)) + line)


def solve(sequence=[], guess=[[None for _ in range(N+1)] for _ in range(N+1)]):
    seq_len = len(sequence)
    idx = N - seq_len
    if seq_len == N:
        print(' '.join([str(i) for i in sequence]))
        return True
    sign = matrix[idx][idx]
    if sign == '-':
        possibles = [-10, 0]
        for i in range(idx+1, N + 1):
            if matrix[idx][i] == '-':
                if guess[idx+1][i] > 9:
                    return False
                possibles[1] = min([0, -guess[idx+1][i], possibles[1]])
            elif matrix[idx][i] == '+':
                if guess[idx+1][i] < 2:
                    return False
                possibles[0] = max([-guess[idx+1][i] + 1, -10, possibles[0]])
            else:
                if guess[idx+1][i] > 10 or guess[idx+1][i] < 0:
                    return False
                if -guess[idx+1][i] < possibles[0] or -guess[idx+1][i] > possibles[1]:
                    return False
                possibles = [-guess[idx+1][i], -guess[idx+1][i]+1]
        for i in range(possibles[0], possibles[1]):
            # guess 계산
            guess[idx][idx] = i
            for j in range(idx+1, N+1):
                guess[idx][j] = guess[idx+1][j] + i
            if solve([i] + sequence, guess):
                return True
    elif sign == '+':
        possibles = [1, 11]
        for i in range(idx+1, N + 1):
            if matrix[idx][i] == '-':
                if guess[idx+1][i] > -2:
                    return False
                possibles[1] = min([-guess[idx+1][i], 11, possibles[1]])
            elif matrix[idx][i] == '+':
                if guess[idx+1][i] < -9:
                    return False
                possibles[0] = max(1, -guess[idx+1][i] + 1, possibles[0])
            else:
                if guess[idx+1][i] < -10 or guess[idx+1][i] > 0:
                    return False
                if -guess[idx+1][i] < possibles[0] or -guess[idx+1][i] > possibles[1]:
                    return False
                possibles = [-guess[idx+1][i], -guess[idx+1][i]+1]
        for i in range(possibles[0], possibles[1]):
            # guess 계산
            guess[idx][idx] = i
            for j in range(idx+1, N+1):
                guess[idx][j] = guess[idx+1][j] + i
            if solve([i] + sequence, guess):
                return True
    else:
        guess[idx][idx] = 0
        for i in range(idx+1, N+1):
            guess[idx][i] = guess[idx+1][i]
        return solve([0] + sequence, guess)
    return False


solve()
