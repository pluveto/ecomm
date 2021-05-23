# e_comm

## For vscode users

Recommended vscode settings for workspace:

```json
{
    "cmake.buildArgs": [  "-DCMAKE_TOOLCHAIN_FILE:FILEPATH=/app/vcpkg/scripts/buildsystems/vcpkg.cmake"],
    "cmake.configureArgs": [  "-DCMAKE_TOOLCHAIN_FILE:FILEPATH=/app/vcpkg/scripts/buildsystems/vcpkg.cmake"],
    "C_Cpp.default.includePath": [
        "/app/vcpkg/installed/x64-linux/include",
        "~/proj/e_comm/include/e_comm"
    ],
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
    "cmake.configureOnOpen": true,
    // ...
}
```

## Requirements

1. unofficial-sqlite3
2. spdlog
3. nlohmann_json
4. OpenSSL
5. SQLITE_MODERN_CPP

## Build

> *Note*: You are expected to have installed requirements which are listed in `CMakeLists.txt`.

For linux users, add execution permission to `./make_run.sh`.

```bash
chmod +x ./make_run.sh
```

And run it:

```bash
./make_run.sh
```