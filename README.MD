# Start of slicer v1
- Start with basic project structure

- Command for build
``` bash
cd ~/slicer
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)
```