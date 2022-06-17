import mod

n = int(input("Введите n = "))
a = [0] * n

print("\nЗаполнить массив случайными числами? Введите \"1\", если да или \"0\", если нет!")
flag = int(input("flag = "))

if flag == 1:
    a = mod.random_array(a)
elif flag == 0:
    a = mod.input_array(a)

res = mod.calc136l(a)

print("\nRes = ", res)
