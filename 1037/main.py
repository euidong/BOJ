import sys

input = sys.stdin.readline

num = int(input())
nums = [int(i) for i in input().split(' ')]
nums.sort()

print(nums[0] * nums[-1])
