#!/usr/bin/env python3

from pathlib import Path
from PIL import Image
import argparse


# -------------------------------------------------
# RGB888 -> RGB565
# -------------------------------------------------

def rgb888_to_rgb565(r, g, b):
    return ((r & 0xF8) << 8) | \
           ((g & 0xFC) << 3) | \
           (b >> 3)


# -------------------------------------------------
# Convert filename
# home.png
# ->
# Home
# -------------------------------------------------

def cpp_name(path: Path):

    words = path.stem.replace("-", "_").split("_")

    return "".join(word.capitalize() for word in words)


# -------------------------------------------------
# Generate HPP
# -------------------------------------------------

def generate_header(image_path: Path,
                    output_path: Path,
                    size: int):

    img = Image.open(image_path).convert("RGBA")

    if size > 0:
        img = img.resize((size, size), Image.NEAREST)

    width, height = img.size

    pixels = []

    for y in range(height):

        for x in range(width):

            r, g, b, a = img.getpixel((x, y))

            if a == 0:
                rgb565 = 0x0000
            else:
                rgb565 = rgb888_to_rgb565(r, g, b)

            pixels.append(rgb565)

    name = cpp_name(image_path)

    array_name = name.lower() + "_pixels"

    with open(output_path, "w") as f:

        f.write("#pragma once\n\n")

        f.write("#include <stdint.h>\n")
        f.write("#include \"graphics/Graphics.hpp\"\n\n")

        f.write("namespace launcher::assets::icons\n")
        f.write("{\n\n")

        f.write(
            f"static constexpr uint16_t {array_name}[] =\n{{\n")

        for i, pixel in enumerate(pixels):

            if i % width == 0:
                f.write("    ")

            f.write(f"0x{pixel:04X}")

            if i != len(pixels)-1:
                f.write(", ")

            if (i+1) % width == 0:
                f.write("\n")

        f.write("};\n\n")

        f.write(
            f"inline constexpr launcher::graphics::Bitmap {name}\n")

        f.write("{\n")

        f.write(f"    .width = {width},\n")
        f.write(f"    .height = {height},\n")
        f.write(f"    .pixels = {array_name},\n")

        f.write("};\n\n")

        f.write("}\n")


# -------------------------------------------------
# Main
# -------------------------------------------------

def main():

    parser = argparse.ArgumentParser()

    parser.add_argument(
        "input",
        help="Input folder")

    parser.add_argument(
        "output",
        help="Output folder")

    parser.add_argument(
        "--size",
        type=int,
        default=16,
        help="Resize icon")

    args = parser.parse_args()

    input_dir = Path(args.input)

    output_dir = Path(args.output)

    output_dir.mkdir(parents=True,
                     exist_ok=True)

    png_files = list(input_dir.glob("*.png"))

    if len(png_files) == 0:
        print("No PNG found.")
        return

    print("----------------------------------")
    print(f"Input : {input_dir}")
    print(f"Output: {output_dir}")
    print("----------------------------------")

    for png in png_files:

        out = output_dir / (png.stem + ".hpp")

        print(f"Convert {png.name}")

        generate_header(
            png,
            out,
            args.size)

    print("----------------------------------")
    print(f"Done ({len(png_files)} files)")
    print("----------------------------------")


if __name__ == "__main__":
    main()