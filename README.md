# mySTL

这是一个对于STL库的学习和模仿，主要是为了学习泛型编程和算法以及数据结构。  
这个项目会实现STL的大部分算法和大部分容器  
- - -

## 主要会实现的组件如下：
* STL中的几个基本容器
  * vector
  * list
  * deque
  * queue
  * stack
  * map
* alloc              （以字节为单位的空间配置器，为allocator提供底层空间配置方案）
* allocator          （以对象为基本单位的空间配置器）
* iterator
* type_traits
* Functions
* AVL Tree
* rb tree
* bitmap
* smart pointer
* heap
* constructor
* 大部分的算法（如sort、swap、find、count、max等等）

- - - 
## 实现进度

* STL中的基本容器进度
  * vector 100%
  * list  100%
  * deque 100%
  * queue 100%
  * stack 100%
  * map 10%
  
* STL中的基本组件进度
  * allocator 100%
  * alloc 100%
  * iterator 100%
  * type_traits 100%
* STL算法进度
  * max
  * min
  * fill
  * fill_n
  * distance
  * copy_backward
  * copy
  * find
  * find_if
  * accumulate
  * swap
  * 待完善
  - - -
## 单元测试覆盖率
 * vector 100%
 * list  100%
 * deque 100%
 * queue 100%
 * stack 100%
 
## 性能测试
  以下的所有性能测试都是在Vs2017，release 模式下进行
### vector 性能测试
*测试代码*
```
//myVector  10^5,普通类型，复杂类型大致也是如此
STL::Timer::start();
STL::vector<int> myIntVec;
for (int i = 0; i < 100000; i++) {
   myIntVec.push_back(i);
}
STL::Timer::finish();
STL::Timer::PrintUsedTimeOnStream(std::cout);

```

*性能测试数据如下 单位: ms*

|类型| 数量级 | std::vector | STL::vector
| ------ | -------- | ----- | ------|
|int |10万|1|1
|int |100万|12|11
|int |1000万|137|120
|std::string |10万|5|10
|std::string |100万|78|81
|std::string |1000万|804|925

### vector 性能测试总结
可以看到，我实现的vector面对普通类型的时候，性能是略高于std的vector的，但是在面对复杂类型string等的时候，就出现了性能问题，后面将会对这个问题进行分析


### list 性能测试
*测试代码*
```
stdList<Str> stdStrLis;
myList<Str> myStrLis;
//普通类型  10^5  std
Timer::start();
for (int i = 0; i < 100000; ++i) {
		stdStrLis.insert(stdStrLis.begin(), testStr);
}
Timer::finish();
Timer::PrintUsedTimeOnStream(std::cout);

```

*性能测试数据如下 单位: ms*

|类型| 数量级 | std::list | STL::list
| ------ | -------- | ----- | ------|
|int |10万|4|1
|int |100万|59|12
|int |1000万|546|132
|std::string |10万|9|4
|std::string |100万|78|37
|std::string |1000万|744|296

### list 性能测试总结
