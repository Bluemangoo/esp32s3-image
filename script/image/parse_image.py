from PIL import ImageFile

from .pixel_data import PixelData


def parse_image(img: ImageFile, x: int, y: int) -> PixelData:
    data = PixelData(x, y)
    for i in range(x):
        for j in range(y):
            r, g, b = img.getpixel((i, j))
            data.push(i, j, r, g, b)

    return data
