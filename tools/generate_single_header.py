# generates a single header from all header and source files

header_files = [
    "Core.h",
    "Math.h",
    "VectorBase.h",
    "Vector.h",
    "Size.h",
    "Region.h",
    "Transform.h",
    "Random.h",
    "Input.h",
    "Resources.h",
    "Color.h",
    "Camera2D.h",
    "Game.h",
    "GameServices.h"
]

source_files = [
    "Core.cpp",
    "Transform.cpp",
    "Random.cpp",
    "Input.cpp",
    "Resources.cpp",
    "Color.cpp",
    "Game.cpp"
]

def process_file(path):
    lines = []
    with open(path, "r") as infile:
        found_marker = False
        for line in infile:
            if line.strip() == "/*BEGIN*/":
                found_marker = True
            elif line.strip() == "/*END*/":
                break
            elif found_marker is True:
                lines += line
    lines = lines[1:-2]
    lines += "\n"
    lines += "\n"
    return lines

def process_files(files):
    data = []
    for file in files:
        data.extend(process_file("src/" + file))
    data = data[:-1]
    return "".join(data)

def generate_single_header(interface_source, implementation_source):
    with open("tools/template.h", "r") as infile, open("io.h", "w") as outfile:
        data = infile.read().replace("/*INTERFACE*/\n", interface_source)
        data = data.replace("/*IMPLEMENTATION*/\n", implementation_source)
        outfile.write(data)

def generate():
    generate_single_header(process_files(header_files), process_files(source_files))
    
if __name__ == '__main__':
    generate()