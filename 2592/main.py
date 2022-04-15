input()
sign = ['<'] + input().split()

# max, min
answer = ['0', '9876543211']


def find_num(num_list, now_idx=0, prev_num='/', prev_tot=''):
    if len(prev_tot) == len(sign):
        answer[0] = max(answer[0], prev_tot)
        answer[1] = min(answer[1], prev_tot)
        return
    for i in range(len(num_list)):
        if sign[now_idx] == '>' and prev_num > num_list[i]:
            find_num(num_list[:i] + num_list[i+1:], now_idx +
                     1, num_list[i], prev_tot + num_list[i])
        if sign[now_idx] == '<' and prev_num < num_list[i]:
            find_num(num_list[:i] + num_list[i+1:], now_idx +
                     1, num_list[i], prev_tot + num_list[i])


find_num([str(i) for i in range(10)])

print(answer[0])
print(answer[1])
