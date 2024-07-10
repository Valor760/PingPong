#!/bin/python3
from sys import argv


def parse_args() -> dict:
	files = {} # var_name : path
	# argv 0 - program name
	# argv 1 - shaders directory path
	for i in range(2, len(argv)):
		args = argv[i].split('=')
		files[args[0]] = args[1]

	return files


def combine(entries: dict) -> str:
	str = "#pragma once\n\n"
	for variable, path in entries.items():
		lines = []
		with open(path, 'r') as f:
			lines += f.readlines()
			f.close()

		str += f"const char* {variable} =\n"
		for l in lines:
			if l[-1] == '\n':
				l = l[:-1]
			str += f"\t\"{l}\\n\"\n"
		str += f";\n\n"
	return str


def main() -> None:
	print("SHADER MERGER: Start")
	shaders_dir = argv[1]
	entries = parse_args()
	str = combine(entries)
	with open(f"{shaders_dir}/shaders.h", "w") as f:
		f.write(str)
		f.close()
	print("SHADER MERGER: End")


if __name__ == '__main__': main()