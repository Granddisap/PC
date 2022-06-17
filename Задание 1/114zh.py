n = 100

res = 3 / 2

for i in range(3, n + 1):
    res *= (i + 1) / (i + 2)

print(f"Произведение: {res:.5f}")
