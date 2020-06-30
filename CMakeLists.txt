project(Sound_compression) 

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall" )
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3" )

set(CMAKE_BUILD_TYPE Debug)
add_executable(dctcompression main.cpp dct.cpp handle_wav.cpp compress.cpp)
target_link_libraries( dctcompression boost_program_options sndfile )
