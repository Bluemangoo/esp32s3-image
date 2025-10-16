from typing import List


class PixelData:
    data: List[int]

    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.data = [0] * (x * y)

    def push(self, x: int, y: int, red: int, green: int, blue: int):
        color = ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3)
        self.data[y * self.x + x] = color

    def to_string(self) -> str:
        return "{" + ','.join([str(d) for d in self.data]) + "}"
