# cmake 所 需 的 最 低 版 本 要 求
cmake_minimum_required ( VERSION 2.8 )
# 设置项目名称
project ( 1 )
# 设 置 C++11支 持
set ( CMAKE_CXX_STANDARD 11)
# 寻 找 OpenCV 库
find_package ( OpenCV REQUIRED )
# 加 入 OpenCV 头 文 件 目 录
include_directories ( ${OpenCV_INCLUDE_DIRS})
# 添加项目的输出程序和所需源代码
add_executable ( jisuan jisuan.cc )
# 将 OpenCV 库 链 接 到 程 序 中
target_link_libraries ( jisuan ${OpenCV_LIBS})
