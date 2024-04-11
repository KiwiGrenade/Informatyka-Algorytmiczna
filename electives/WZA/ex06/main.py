import sys

from itertools import product
from typing import List
from random import shuffle
from copy import deepcopy


class Set:
    def __init__(self, expo: int, value_func, border_func) -> None:
        self.expo = expo
        self.border_func = border_func
        self.value_func = value_func

    def gen_points(self, low_border: int, high_border: int) -> List:
        ranges_list = [range(low_border, high_border) for _ in range(self.expo)]
        all_points = list(product(*ranges_list))
        set_points = [point for point in all_points if self.border_func(self.value_func(point))]
        shuffle(set_points)
        return set_points


def evaluate(point1: List[int], point2: List[int]) -> bool:
    for (x, y) in zip(point1, point2):
        if x > y:
            return False
    return True


def find_minimal(points: List[List[int]]) -> List[List[int]]:
    minimal = []
    flag = True
    for a in points:
        for m in list(minimal):
            if evaluate(m, a):
                flag = False
                break
            if evaluate(a, m):
                minimal.remove(m)
        if flag:
            minimal.append(deepcopy(a))
        else:
            flag = True

    return minimal


def func1(point: List[int]) -> int:
    return point[0] * point[1]


def func2(point: List[int]) -> int:
    return (point[0] - 10) ** 2 + (point[1] - 10) ** 2


def border(value: int) -> bool:
    return value >= 11


def border2(value: int) -> bool:
    return value <= 25


def main() -> int:
    s = Set(2, func1, border)
    points = s.gen_points(0, 15)
    minimal = find_minimal(points)
    print(minimal)
    return 0


if __name__ == '__main__':
    sys.exit(main())
