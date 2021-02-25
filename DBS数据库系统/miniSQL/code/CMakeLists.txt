cmake_minimum_required(VERSION 3.16)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code main.cpp Interpreter/Interpreter.cpp Interpreter/Interpreter.h StringProcessor/StringProcessor.cpp StringProcessor/StringProcessor.h Interpreter/showResult.h Interpreter/callAPI.h Table/Table.cpp Table/Table.h GlobalVariable/GlobalVariable.h GlobalVariable/GlobalVariable.cpp CatalogManager/catalogManager.cpp CatalogManager/catalogManager.h BufferManager/bufferManager.cpp BufferManager/bufferManager.h IndexManager/indexManager.cpp IndexManager/indexManager.h IndexManager/BPTreeNode.h IndexManager/BPTreeNode.cpp IndexManager/BPTree.h IndexManager/BPTree.cpp RecordManager/recordManager.cpp RecordManager/recordManager.h API/API.cpp API/API.h IndexManager/index.cpp IndexManager/index.h Table/tableFile.cpp Table/tableFile.h BufferManager/fileManager.cpp BufferManager/fileManager.h Interpreter/callAPI.cpp Interpreter/showResult.cpp)