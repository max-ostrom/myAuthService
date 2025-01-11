sudo apt update
sudo apt install libboost-all-dev
sudo apt install libssl-dev


mkdir third_party
cd third_party


# GRPC
if [ ! -d "grpc" ]; then 
    git clone --recurse-submodules -b v1.56.0 https://github.com/grpc/grpc
fi
cd grpc
mkdir build
cd build
cmake ..
make -j 4
sudo make install
cd ../../