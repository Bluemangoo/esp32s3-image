from PIL import Image

from .gif import gif2frames
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

    (original_width, original_height) = img.size
    if rotate:
        (original_width, original_height) = (original_height, original_width)
    if abs((original_width / original_height) / (x / y) - 1) > 0.05:
        raise RuntimeError(
            f"Image size does not match the target size, need {size_name}, but got {original_width}x{original_height}")

    is_animated = hasattr(img, "is_animated") and img.is_animated

    data = []
    delay = 0

    if is_animated:
        delay, frames = gif2frames(img)
        for frame in frames:
            data.append(parse_image(frame, x, y, rotate))
    else:
        data = [parse_image(img, x, y, rotate)]

    extra_defines = ""
    if is_animated:
        extra_defines = f"""
#define IMAGE_ANIMATED
#define image_frame_delay {delay}
"""

    return f"""#ifndef ESP_IMAGE_IMAGE_DATA_H
#define ESP_IMAGE_IMAGE_DATA_H

#include <vector>

static const {"std::vector<" if is_animated else ""}std::vector<uint16_t>{">" if is_animated else ""} image_data = {f"{"{" + ",".join([d.to_string() for d in data]) + "}"}" if is_animated else f"{data[0].to_string()}"};
#define image_width {x}
#define image_height {y}{extra_defines}

#endif ///ESP_IMAGE_IMAGE_DATA_H"""
