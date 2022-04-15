def gcd(a, b):
    if b > a:
        a, b = b, a
    if b == 0:
        return a
    return gcd(a % b, b)


A, B = [int(i) for i in input().split()]

r1 = gcd(A, B)
print(r1)
print(A * B // r1)
