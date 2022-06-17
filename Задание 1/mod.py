from numpy import random as rn
import numpy as np


def calc6772(m, n):
    """
    Решение 677 задачи, вариант 2

    :param m: матрица
    :param n: размерность матрицы
    """

    allSumm = m.sum()
    b = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            summ = allSumm - m[i, 0:n].sum() - m[0:n, j].sum() + m[i][j]
            b[i][j] = summ
    return b


def calc677(n):
    """
    Решение 677 задачи

    :param n: размерность матрицы
    """
    a = np.ones((n, n))
    b = np.zeros((n, n))

    for i in range(n):
        for j in range(n):
            summ = 0
            summ += a[0:i, 0:j].sum()  # вверхний левый
            summ += a[0:i, j + 1:n].sum()  # вверхний правый
            summ += a[i + 1:n, 0:j].sum()  # нижний левый
            summ += a[i + 1:n, j + 1:n].sum()  # нижний правый
            b[i][j] = summ
    return b


def calc335(n):
    """
    Решение 335 задачи под буквой A
    :param n:
    :return:
    """
    s = 0
    c = 1
    for k in range(1, n + 1):
        c = c * (k + n)
        s += c

    return s


def calc136l(arr):
    """
    Решение 136 задачи под буквлй L
    :param arr:
    :return:
    """
    res = arr[0]
    for i in range(1, len(arr)):
        res *= arr[i]

    res = abs(res)
    return res ** .5


def calc178e(arr):
    """
    Решение 178 задачи под буквой Е
    """
    res = 0
    for i in range(len(arr)):
        if i % 2 == 0 and arr[i] % 2 != 0:
            res += 1

    return res


def input_array(arr):
    """
    Заполнение матрицы вручную
    :param arr:
    :return:
    """
    for i in range(len(arr)):
        arr[i] = float(input("a[{}] = ".format(i + 1)))

    return arr


def random_array(arr):
    """
    Заполнение матрицы слуйными числами
    :param arr:
    :return:
    """
    arr = rn.randint(1, 10, len(arr))
    return arr


def init_array(arr):
    """
    Заполнение матрицы на выбор
    :param arr:
    :return:
    """
    print("\nЗаполнить массив случайными числами? Введите \"1\", если да или \"0\", если нет!")
    flag = int(input("flag = "))

    if flag == 1:
        arr = rn.randint(1, 10, len(arr), )
        # arr = rn.random(len(arr),)
        print("\na =", arr)
        return arr

    elif flag == 0:
        print()
        for i in range(len(arr)):
            arr[i] = float(input("a[{}] = ".format(i + 1)))
        return arr

    else:
        print("Вы ввели неккоректное значение, было решено заполнить массив случайными числами")
        arr = rn.randint(1, 10, len(arr), )
        # arr = rn.random(len(arr),)
        print("\na =", arr)
        return arr


def input_matr(a):
    for i in range(len(a)):
        j: int
        for j in range(len(a[i])):
            a[i][j] = float(input(f"a[{i}][{j}] = "))
    return a
