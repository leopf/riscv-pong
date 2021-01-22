mkdir -p ./build
rm -r ./build/*
export PATH=/opt/riscv32/bin/:$PATH
riscv32-unknown-elf-gcc  -o ./build/main.o -g -ffreestanding -O0 -Wl,--gc-sections \
    -nostartfiles -nostdlib -nodefaultlibs -Wl,-T,riscv32-virt.ld \
    crt0.s ./src/main.c
riscv32-unknown-elf-objdump -d ./build/main.o > ./build/main-disasm.hex
python3 extract-hex.py -i ./build/main-disasm.hex -o ./build/main.hex
python3 decompile.py -i ./build/main.hex -o ./build/main.S