
# Build

Need relatively newer toolchain, as library uses C++ modules.

- cmake (v3.31+)
- clang (v19+)
- ninja

```
<shell>
cmake -B build -S . -DCMAKE_CXX_COMPILER="clang++" -G "Ninja Multi-Config"
cmake --build build --config Release
cmake --install build
```

# Usage

The installed library provides a `uzleo::la` cmake package that can be 
find-packaged at client end.

```
<CMakeLists>
find_package(la REQUIRED)

target_link_libraries(client_ex PRIVATE uzleo::la)
```

The library provides a module `la` that could be imported in source-code.

```
<cpp>
import la;

auto main() {
  la::Matrix<int, 4, 3> matrix{};
}
```
