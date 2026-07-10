add_executable(allocation_sim
    src/main.cpp
    src/model/MemoryBlock.cpp
    src/model/Process.cpp
    src/algorithms/Allocation.cpp
    src/algorithms/FirstFit.cpp
    src/algorithms/BestFit.cpp
    src/algorithms/WorstFit.cpp
    src/core/MemoryManager.cpp
    src/exceptions/SimulatorException.cpp
    src/exceptions/InsufficientMemoryException.cpp
    src/exceptions/ProcessNotFoundException.cpp
    src/exceptions/InvalidSizeException.cpp
    src/exceptions/InvalidCommandException.cpp
    src/io/Command.cpp
    src/io/SimulationFileReader.cpp
    src/ui/CliMenu.cpp
    src/ui/WebServer.cpp 
)

target_include_directories(allocation_sim PRIVATE include)
target_link_libraries(allocation_sim PRIVATE Threads::Threads)