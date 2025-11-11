# Add FindBlosc.cmake to module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

find_package(Boost REQUIRED
    COMPONENTS
        iostreams
    )

find_package(TBB REQUIRED
    COMPONENTS
        tbb
    )

find_package(Blosc REQUIRED)