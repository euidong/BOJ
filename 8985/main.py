lines = []

N = int(input())
input()
for _ in range((N-2) // 2):
    dot1 = [int(i) for i in input().split()]
    dot2 = [int(i) for i in input().split()]
    lines.append(dot1 + dot2 + [0])
input()

K = int(input())
for _ in range(K):
    hole = [int(i) for i in input().split()] + [0]
    lines[lines.index(hole)][4] = 1


class Tree:
    def __init__(self, width, height, hole):
        self.width = width
        self.height = height
        self.hole = hole
        self.parent = None
        self.children = []

    def add_child(self, tree: 'Tree'):
        self.children.append(tree)
        tree.parent = self
        me = self
        while me != None:
            me.hole += tree.hole
            me = me.parent

    def remove_water(self):
        if self.hole == 0:
            time = 0
            remain = self.width * self.height
        else:
            time = self.width * self.height / self.hole
            remain = 0
        if len(self.children) == 0:
            return time, remain
        else:
            max_c_time = 0
            for child in self.children:
                c_time, c_remain = child.remove_water()
                if max_c_time < c_time:
                    max_c_time = c_time
                remain += c_remain
            time += max_c_time
        return time, remain


def make_tree(start, end, now_width, prev_height):
    if start >= end:
        return None
    min_line = min(lines[start:end], key=lambda x: x[1])
    idx = lines.index(min_line)

    t = Tree(
        now_width,
        min_line[1] - prev_height,
        min_line[4]
    )

    left = make_tree(start, idx, min_line[0] - lines[start][0], min_line[1])
    right = make_tree(idx+1, end, lines[end - 1][2] - min_line[2], min_line[1])
    if left != None:
        t.add_child(left)
    if right != None:
        t.add_child(right)
    return t


t = make_tree(0, len(lines), lines[-1][2], 0)

time, remain = t.remove_water()

print(round(time, 2))
print(remain)
