# XGC-MGARD

How to build the code on Rhea.

1. mkdir build

2. cd build

3. Point the CMake to the ADIOS and MGARD installation.

export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/ccs/proj/e2e/qliu/ADIOS2_install/
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/ccs/proj/e2e/qliu/mgard_install/

4. Load the ZSTD.

module load zstd

5. cmake ..

6. make


