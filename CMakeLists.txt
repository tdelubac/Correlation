project(Correlation)

set(CMAKE_BUILD_TYPE Release)

add_executable(
  correlation
  src/main.cpp
  )

add_executable(
  bruteforce
  src/bruteforce.cpp
  )

add_executable(
  tree
  src/tree.cpp
  )
