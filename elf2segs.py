import os
import os.path
import sys
import binascii
from elftools.elf.elffile import ELFFile
from struct import pack, unpack
from elftools.common.py3compat import ifilter, byte2int, bytes2str, itervalues, str2bytes	
from argparse import ArgumentParser
import os.path

parser = ArgumentParser(description="RISC-V Hexer")
parser.add_argument("-o", dest="output_dir", required=True,
                    help="output dir")
parser.add_argument("-i", dest="input_filename", required=True,
                    help="input elf file")
args = parser.parse_args()

input_filename_base = os.path.splitext(os.path.basename(args.input_filename))[0]

with open(args.input_filename, 'rb') as file:
		elffile = ELFFile(file)
		addresses = ""
		idx = 0
		bytes_per_word = 4
		for segment in elffile.iter_segments():
			if segment['p_type'] == 'PT_LOAD':
				with open(os.path.join(args.output_dir, input_filename_base + " - seg" + str(idx) + ".hex"), 'w') as seg:
					data = segment.data()
					addr = segment['p_paddr']
					size = len(data)				
					addresses += "{0:#0{1}x} ".format(addr, 10)
					for i in range(0, len(data), bytes_per_word):
						word0 = unpack('I',data[i:i+bytes_per_word])
						word0str = "{0:0{1}x}".format(int(word0[0]), bytes_per_word * 2)
						if(i+bytes_per_word == len(data)):
							seg.write(word0str)
						else:
							seg.write(word0str + "\n")				
					idx += 1