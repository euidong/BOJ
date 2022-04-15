dwarf = []

tot = 0
for i in range(9):
    dwarf.append(int(input()))
    tot += dwarf[i]


for i in range(9):
    for j in range(i + 1, 9):
        if tot - dwarf[i] - dwarf[j] == 100:
            dwarf.pop(j)
            dwarf.pop(i)
            break
    if len(dwarf) == 7:
        break

dwarf.sort()

for d in dwarf:
    print(d)
