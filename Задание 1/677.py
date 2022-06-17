import mod
import numpy as np

# 677а

n = int(input("Введите n = "))

print("\nДля заполнения матрицы введите:")
print("\n \"1\" для случайных чисел")
print("\n \"2\" для заполнения единицами")
print("\n \"0\" для ручного заполнения\n")
flag = int(input("flag = "))

if flag == 1:
    a = np.array(np.random.randint(1, 20, (n, n)))
elif flag == 0:
    a = np.zeros((n, n))
    a = mod.input_matr(a)
elif flag == 2:
    a = np.ones((n, n))
else:
    print("Вы ввели некорректное значение, было решено заполнить массив случайными числами")
    a = arr = np.array(np.random.rand(1, 20, (n, n)))

b = mod.calc6772(a, n)
print(a)
print(b)
