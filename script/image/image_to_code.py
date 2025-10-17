from PIL import Image

from .parse_image import parse_image


def image_to_code(image_path: str, size: str, rotate: bool) -> str:
    x = 0
    y = 0
    size_name = ""
    match size:
        case "0.96":
            x = 80
            y = 160
            size_name = "1x2"
        case "1.44":
            x = 128
            y = 128
            size_name = "1x1"
        case "1.8":
            x = 128
            y = 160
            size_name = "4x5"
        case _:
            raise RuntimeError("Unsupported size")

    img = Image.open(image_path)

    if rotate:
        img = img.transpose(Image.Transpose.TRANSPOSE)

    (original_width, original_height) = img.size
    if abs((original_width / original_height) / (x / y) - 1) > 0.02:
        raise RuntimeError(
            f"Image size does not match the target size, need {size_name}, but got {original_width}x{original_height}")
    img = img.resize((x, y))

    data = parse_image(img, x, y)

    return f"""#ifndef ESP_IMAGE_IMAGE_DATA_H
#define ESP_IMAGE_IMAGE_DATA_H

constexpr uint16_t image_data[]{data.to_string()};
constexpr int16_t image_width = {x};
constexpr int16_t image_height = {y};

#endif ///ESP_IMAGE_IMAGE_DATA_H"""
