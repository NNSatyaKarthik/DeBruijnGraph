#/bin/bash
git config --global http.sslVerify false
cd cppCode/
cmake . && make && ./cppCode