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
### Notes:
 4_C_FOR_ADA and 7_C_FOR_GO do not work.

