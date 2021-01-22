from riscvmodel.code import decode
from argparse import ArgumentParser
import os.path

parser = ArgumentParser(description="RISC-V Decompiler")
parser.add_argument("-o", dest="output_filename", required=True,
                    help="output asm file")
parser.add_argument("-i", dest="input_filename", required=True,
                    help="input hex file")
args = parser.parse_args()

print("reassembling file " + args.input_filename + " -> " + args.output_filename)

if not os.path.exists(args.input_filename):
    print("ERROR: file not found!")
    exit()

hex_file = open(args.input_filename, 'r') 
asm_file = open(args.output_filename, 'w')

asm_lines = []
for line in hex_file.readlines(): 
    line_n = line.replace("\n", "")
    cmd = None
    try:
        cmd = str(decode(int(line, 16)))
    except:
        cmd = "unknown"
    asm_lines.append(line_n + ": " + cmd)

asm_file.write("\n".join(asm_lines))

hex_file.close()
asm_file.close()
