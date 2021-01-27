mkdir -p ~/build
cd ~/build
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain
cd riscv-gnu-toolchain/
mkdir build
cd build
sudo apt-get -y install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev
sudo ../configure --prefix=/opt/riscv32 --with-arch=rv32im --with-abi=ilp32
sudo make