from riscvmodel.code import decode
from argparse import ArgumentParser
import os.path

parser = ArgumentParser(description="RISC-V Hexer")
parser.add_argument("-o", dest="output_filename", required=True,
                    help="output asm file")
parser.add_argument("-i", dest="input_filename", required=True,
                    help="input hex file")
args = parser.parse_args()

print("hexing file " + args.input_filename + " -> " + args.output_filename)

if not os.path.exists(args.input_filename):
    print("ERROR: file not found!")
    exit()

asm_file = open(args.input_filename, 'r') 
hex_file = open(args.output_filename, 'w')

hex_lines = []
for line in asm_file.readlines(): 
    if line.startswith("1c08") and line.find(":") == 8:
        hex_lines.append(line[10:18])

hex_file.write("\r\n".join(hex_lines))

hex_file.close()
asm_file.close()
