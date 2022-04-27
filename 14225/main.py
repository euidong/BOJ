N = input()
S = [int(i) for i in input().split()]

checker = [False] * 2_000_001
checker[0] = True


def make_ss(S, sum=0):
    for i in range(len(S)):
        checker[sum+S[i]] = True
        make_ss(S[i+1:], sum + S[i])


make_ss(S)

print(checker.index(False))
