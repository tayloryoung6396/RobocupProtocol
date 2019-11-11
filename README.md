# RobocupProtocol
Protobuf message protocol for the Robocup Humanoid league.

This repository contains example protobuf messages and some code examples for encoding/decoding the different messages.

## Files
```bash
RobocupProtocol/
├── CMakeLists.txt                   # CMake project file
├── encode_base.cpp                  # Encode the official message, decode extended message
├── encode_extended.cpp              # Encode the extended message, decode official message
├── robocup.proto                    # The official message
├── robocup_extension.proto          # The extended message
└── utils.hpp                        # Utility functions for interpreting message contents
```

## Compiling
```bash
mkdir build
cd build
cmake ..
make
```

## Running
There are two binaries that are built `encode_base` and `encode_extended`. 

`encode_base` will create a message conforming to the official standard and save it to a file named `base_message.pb`. 
If a file named `extended_message.pb` exists it will open that file and try to parse it using the official message format, and it will then print its contents to the screen.

`encode_extended` will create a message with non-standard information in it and save it to a file named `extended_message.pb`. 
If a file named `base_message.pb` exists it will open that file and try to parse it using the extended message format, and it will then print its contents to the screen.

