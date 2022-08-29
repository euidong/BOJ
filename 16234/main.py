import sys
from collections import deque
input = sys.stdin.readline

N, M, K = map(int, input().split())


A = []
for _ in range(N):
    A.append([int(i) for i in input().split()])

trees = []
for _ in range(M):
    trees.append([int(i) for i in input().split()])

# state = {
#     trees: [age: number, ...],
#     feeds: number
# }

stats = [[{"trees": deque(), "feeds": 5} for _ in range(N)] for _ in range(N)]

for i in range(M):
    stats[trees[i][0] - 1][trees[i][1] - 1].get("trees").append(trees[i][2])


dy = [-1, -1, -1, 0, 0, 1, 1, 1]
dx = [-1, 0, 1, -1, 1, -1, 0, 1]


while K > 0:
    # spring & summer
    for i in range(N):
        for j in range(N):
            new_trees = deque()
            added_feeds = 0
            feed = stats[i][j].get("feeds")
            for idx, age in enumerate(stats[i][j].get("trees")):
                if age > feed:
                    added_feeds += age // 2
                else:
                    new_trees.append(age + 1)
                    feed -= age
            stats[i][j].update({
                "trees": new_trees,
                "feeds": feed + added_feeds
            })

    for i in range(N):
        for j in range(N):
            # fall
            for idx, age in enumerate(stats[i][j].get("trees")):
                if age % 5 == 0:
                    for a in range(8):
                        y = i + dy[a]
                        x = j + dx[a]
                        if -1 < y < N and -1 < x < N:
                            stats[y][x].get("trees").appendleft(1)
            # winter
            feed = stats[i][j].get("feeds")
            stats[i][j].update({"feeds": feed + A[i][j]})

    K -= 1

answer = 0
for i in range(N):
    for j in range(N):
        answer += len(stats[i][j].get("trees"))

print(answer)
