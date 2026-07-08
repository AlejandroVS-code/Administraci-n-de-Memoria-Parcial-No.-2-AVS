add_executable(allocation_sim
    src/main.cpp
    src/model/Block.cpp
    src/model/Process.cpp
    src/strategy/FirstFit.cpp
    src/strategy/BestFit.cpp
    src/strategy/WorstFit.cpp
    src/core/MemoryManager.cpp
    src/ui/MenuCLI.cpp
)

target_include_directories(allocation_sim PRIVATE include)