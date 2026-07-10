add_executable(translation_sim
    src/main.cpp
    src/model/VirtualAddress.cpp
    src/model/PhysicalAddress.cpp
    src/model/Frame.cpp
    src/model/Page.cpp
    src/model/Segment.cpp
    src/algorithms/TranslationStrategy.cpp
    src/algorithms/PagingStrategy.cpp
    src/algorithms/SegmentationStrategy.cpp
    src/core/PageTable.cpp
    src/core/SegmentTable.cpp
    src/core/MemoryTranslator.cpp
    src/exceptions/TranslatorException.cpp
    src/exceptions/InvalidAddressException.cpp
    src/exceptions/PageFaultException.cpp
    src/exceptions/SegmentationFaultException.cpp
    src/exceptions/InvalidCommandException.cpp
    src/io/TranslationCommand.cpp
    src/io/TranslationFileReader.cpp
    src/ui/CliMenu.cpp
)

target_include_directories(translation_sim PRIVATE include)