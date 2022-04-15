L, C = [int(i) for i in input().split()]

vow = []
cons = []

flt = [False] * 26
flt[0] = True
flt[4] = True
flt[8] = True
flt[14] = True
flt[20] = True

for letter in input().split():
    if flt[ord(letter) - 97]:
        vow.append(letter)
    else:
        cons.append(letter)

vow_ss = {i: [] for i in range(1, 6)}

cons_ss = {i: [] for i in range(1, 22)}


def subset(ss, arr, cur=[]):
    for i in range(len(arr)):
        new = cur + [arr[i]]
        ss[len(new)].append(new)
        subset(ss, arr[i+1:], new)


subset(vow_ss, sorted(vow))
subset(cons_ss, sorted(cons))

result = []
for i in range(1, 6):
    if L - i < 2:
        break
    m = 0
    n = 0
    for v in vow_ss[i]:
        for c in cons_ss[L-i]:
            result.append(''.join(sorted(v + c)))

for i in sorted(result):
    print(i)
