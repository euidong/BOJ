N = int(input())

p = [0] * (N + 1)
t = [0] * (N + 1)

for i in range(N):
    t[i], p[i] = [int(i) for i in input().split()]


def solve(now_time, prev_job_end_time, tot_profit=0):
    if now_time == N + 1:
        return tot_profit
    a = tot_profit
    b = tot_profit

    if now_time >= prev_job_end_time and now_time + t[now_time] <= N:
        a = solve(now_time + 1, now_time +
                  t[now_time], tot_profit + p[now_time])
    b = solve(now_time + 1, prev_job_end_time, tot_profit)
    return max([a, b])


print(solve(0, 0))
