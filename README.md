# mixvm

[![Build Status](https://travis-ci.org/Alexander-Ignatyev/mixvm.svg?branch=master)](https://travis-ci.org/Alexander-Ignatyev/mixvm)

Implementation of MIX Virtual Machine.

## building

Easy way to build using cmake and nothing more:

```
mkdir build
cd build
cmake ..
make
```

and run the application

```
./mix_vm
```

## macOS

### initial setup

```
brew install cmake clang-format
```

### XCode project

```
mkdir build
cd build
cmake -G XCode ..
```

### development

Do not forget to run `git clang-format` before `git commit`
