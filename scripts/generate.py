import argparse
from argparse import ArgumentParser

from image.image_to_code import image_to_code


def image(args: argparse.Namespace):
    if not args.size:
        raise RuntimeError("Size is required, options: [0.96, 1.44, 1.8]")
    code = image_to_code(args.image, args.size, args.rotate)
    with open(args.output, "w") as f:
        f.write(code)


def main():
    parser = ArgumentParser(description="Generate files for this project.")
    sub_parsers = parser.add_subparsers(dest="subcommand")
    image_parser = sub_parsers.add_parser("apply", description="apply a image")
    image_parser.add_argument("image", help="input image")
    image_parser.add_argument("-s", "--size", help="input size (0.96, 1.44, 1.8)")
    image_parser.add_argument("-r", "--rotate", action="store_true", help="rotate the image")
    image_parser.add_argument("-o", "--output", help="output file", default="src/image_data.h")

    args = parser.parse_args()

    if args.subcommand == "apply":
        image(args)


if __name__ == "__main__":
    main()
