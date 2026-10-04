from math import sqrt

a, b, c = sorted(map(int, input().split()))

if a*a+b*b<=c*c:
    print(a*b/2)
else:
    s = (a+b+c)/2
    print(sqrt(s*(s-a)*(s-b)*(s-c)))