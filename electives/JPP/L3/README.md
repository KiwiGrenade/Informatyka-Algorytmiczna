#### Build
```
cmake -B <build_directory> && cd <build_directory>
make -j 8
```
#### Test
```
ctest
```
#### Clean 
```
make clean
cd .. && rm -rf <build_directory>
```
