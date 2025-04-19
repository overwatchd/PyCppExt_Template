# Python C++ 扩展模块模板

一个使用 pybind11、CMake 和 Conan 创建 Python C++ 扩展的现代模板。

## 特性
- 支持现代 C++17
- 支持 Python 3.x
- 使用 pybind11 创建 Python 绑定
- 使用 CMake 构建系统
- 使用 Conan 包管理器
- 集成 fmt 库用于格式化
- 使用 pytest 进行自动化测试
- 跨平台支持 (Windows, Linux, macOS)

## 环境要求
- CMake >= 3.26
- Python 3.x
- Conan 包管理器
- 支持 C++17 的编译器

## 快速开始

1. 克隆此模板
```bash
git clone https://github.com/overwatchd/PyCppExt_Template.git
cd PyCppExt_Template
```

2. 安装 Python 依赖
```bash
pip install pytest
```

3. 构建项目
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

构建完成后会自动运行测试。

## 项目结构
```
.
├── src/                # C++ 源文件
├── test/              # Python 测试文件
├── CMakeLists.txt     # CMake 配置
├── conanfile.txt      # Conan 依赖配置
└── README.md          # 本文档
```

## 开发说明

### 调试模式
- 使用 `-DCMAKE_BUILD_TYPE=Debug` 构建调试版本
- 调试版本会自动链接 Python 调试库
- 测试时会使用 `python_d` 而不是 `python`

### 发布模式
- 使用 `-DCMAKE_BUILD_TYPE=Release` 构建发布版本
- 发布版本会进行优化
- 测试时使用 `python`

### 测试
- 测试文件位于 `test` 目录
- 使用 pytest 运行测试
- 构建完成后会自动运行测试
