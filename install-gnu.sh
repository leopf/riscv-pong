# install dependencies
sudo apt update
sudo apt -y upgrade
sudo apt-get -y install git python3-pip autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev

# install python packages for helpers
pip3 install riscv-model argparse

# clone gnu toolchain
mkdir -p ~/build
cd ~/build
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain
cd riscv-gnu-toolchain/
mkdir build
cd build

# make gnu toolchain
sudo ../configure --prefix=/opt/riscv32 --with-arch=rv32im --with-abi=ilp32
sudo make