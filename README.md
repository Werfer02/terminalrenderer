# terminalrenderer

wip mini library for terminal software rendering for use in my own projects.

## Building

### building library

```
cmake -S . -B build
```
```
cmake --build build
```

### building demo
```
cmake -S . -B build -Dtrlib_BUILD_DEMO
```
```
cmake --build build
```
demo in build/demo

## Including in another cmake project

1. Obtain in some way, e.g. FetchContent
```
FetchContent_Declare(
    terminalrenderer
    GIT_REPOSITORY https://github.com/Werfer02/terminalrenderer.git
    GIT_TAG master
)
FetchContent_MakeAvailable(terminalrenderer)
```
2. Link library
```
target_link_libraries(app PRIVATE trlib)
```
