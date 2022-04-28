import sys
input = sys.stdin.readline

N = int(input())
words = []

charset = set()
for i in range(N):
    words.append(input().rstrip())
    for c in words[i]:
        charset.add(c)
charlist = list(charset)
charlist = [ord(c) for c in charlist]

answer = 0


def make_case(list=[i for i in range(10 - len(charlist), 10)], result=[]):
    if len(list) == 0:
        global answer
        sum = 0
        for word in words:
            for idx in range(len(word)):
                sum += result[charlist.index(ord(word[idx]))] * \
                    (10 ** (len(word) - 1 - idx))
        answer = max([answer, sum])
        return
    for idx in range(len(list)):
        make_case(list[:idx] + list[idx+1:], result + [list[idx]])


make_case()

print(answer)
