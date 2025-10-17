from typing import Tuple, List

from PIL.GifImagePlugin import GifImageFile
from PIL.ImageFile import ImageFile


def gif2frames(image: GifImageFile) -> Tuple[int, List[ImageFile]]:
    n_frames = image.n_frames
    duration = image.info.get("duration", 100)
    frames = []
    for frame_index in range(n_frames):
        image.seek(frame_index)
        frame = image.copy()
        frames.append(frame)
    return duration, frames
