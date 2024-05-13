# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("JsonCodeGenerator")

add_executable(JsonGenerator)

target_sources(JsonGenerator PRIVATE src/JsonCodeGenerator.cpp "src/main.cpp")

target_compile_features(JsonGenerator PUBLIC cxx_std_20)

target_include_directories(JsonGenerator PRIVATE src PUBLIC include)
