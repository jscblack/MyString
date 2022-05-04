已知未实现完全的部分：endl，只能允许 ostrStream << s1 << oMyStringstream::endl; 的写法。技术不足以实现 ostrStream << s1 << std::endl; 的写法
其余应以尽力实现，并且支持了迭代器与自动类型推导for(auto ch:str)的写法
打包内的main.cpp来自老师提供的word文档内的说明材料与测试内容，可供参考。