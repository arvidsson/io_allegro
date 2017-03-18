# generates a single header from all header and source files

header_files = [
    "Core.h"
    "Transform.h",
    "Game.h"
]

source_files = [
    "Transform.cpp",
    "Game.cpp"
]

def process_file(path):
    data = ""
    found_begin = false
    found_end = false
    with open(template_file, "r") as infile
        for line in infile:
            if found_begin is True and found_end is False:
                data += line
            elif line.strip() == "/*BEGIN*/":
                found_begin = True
            elif line.strip() == "/*END*/":
                found_end = True
    return data

def process_files(files):
    data = ""
    for file in files:
        data += process_file("../src/" + file)
    return data

def generate_single_header(interface_source, implementation_sorce):
    with open("template.h", "r") as infile, open("../io.h", "w") as outfile:
        data = infile.read().replace("/*INTERFACE*/", interface_source)
        data = data.replace("/*IMPLEMENTATION*/", implementation_sorce)
        outfile.write(data)

def generate():
    generate_single_header(process_files(header_files), process_files(source_files))
    
if __name__ == '__main__':
    generate()