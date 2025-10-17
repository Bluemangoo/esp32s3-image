from PIL import Image
from PIL.ImageFile import ImageFile

from .pixel_data import PixelData


def parse_image(img: ImageFile, x: int, y: int, rotate: bool) -> PixelData:
    data = PixelData(x, y)
    if rotate:
        img = img.transpose(Image.Transpose.TRANSPOSE)

    img = img.resize((x, y)).convert("RGB")
    for i in range(x):
        for j in range(y):
            r, g, b = img.getpixel((i, j))

            data.push(i, j, r, g, b)

    return data
