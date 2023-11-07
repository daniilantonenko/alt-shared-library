# Building and installing on ALT-Linux 

All build dependencies can be installed with following command:

```
apt-get install cmake git gcc-c++ curl libcurl-devel nlohmann-json-devel cli11-devel
```

## Install with CMake (local)

Building a project from source files and installing it **locally**:

```
cmake -B build -DLIB_BUILD_INSTALL=ON
cd build
sudo make install
```

**1-st access option:** using the temporary command:
```
export LD_LIBRARY_PATH=/usr/local/lib64:$LD_LIBRARY_PATH
```

**2-nd access option**

Constantly use local libraries by adding the following lines to the /etc/ld.so.conf.d/local.conf file:
```
/usr/local/lib64
```

Run the command to define the libraries:
```
sudo ldconfig
```