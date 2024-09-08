# Python C++ 扩展模块模板

使用 conan + cmake 构建项目。

构建指令：
    cmake -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake

conan_proveder.cmake 的修改
    添加了对应的conan_install以支持MinSizeRel和RelWithDebInfo
