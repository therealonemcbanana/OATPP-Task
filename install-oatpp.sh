BUILD_TYPE="Debug"
jobs_num=4

wget https://github.com/oatpp/oatpp/archive/refs/tags/1.3.0-latest.tar.gz
tar -xf 1.3.0-latest.tar.gz
rm 1.3.0-latest.tar.gz
cd oatpp-1.3.0-latest/
mkdir build 
cd build
cmake -DCMAKE_BUILD_TYPE="Debug" -DOATPP_BUILD_TESTS=OFF .. -GNinja
cmake --build . --parallel $jobs_num
cmake --install .
cd ../..

wget https://github.com/oatpp/oatpp-swagger/archive/refs/tags/1.3.0-latest.tar.gz
tar -xf 1.3.0-latest.tar.gz
rm 1.3.0-latest.tar.gz
cd oatpp-swagger-1.3.0-latest/
mkdir build 
cd build
cmake -DCMAKE_BUILD_TYPE="Debug" -DOATPP_BUILD_TESTS=OFF .. -GNinja
cmake --build . --parallel $jobs_num
cmake --install .
cd ../..

wget https://github.com/oatpp/oatpp-sqlite/archive/refs/tags/1.3.0-latest.tar.gz
tar -xf 1.3.0-latest.tar.gz
rm 1.3.0-latest.tar.gz
cd oatpp-sqlite-1.3.0-latest/
mkdir build 
cd build
cmake -DCMAKE_BUILD_TYPE="Debug" -DOATPP_BUILD_TESTS=OFF -DOATPP_SQLITE_AMALGAMATION=ON .. -GNinja
cmake --build . --parallel $jobs_num
cmake --install .
cd ../..