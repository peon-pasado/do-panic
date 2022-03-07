t = int(input())

C = [1]

for i in range(1, 5001):
    C.append(C[i - 1] * 2 * (2 * i - 1) // (i + 1))

for _ in range(t):
    n = int(input())
    print(C[n])
