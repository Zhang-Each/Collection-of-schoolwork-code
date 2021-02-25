# miniSQL 开发日志	
#### 注：一些暂定的代码规范

- 大括号**不换行**
- Clion作为开发工具
- 每个模块要有一个文件夹，不然代码太乱
- 函数名小驼峰法，中间变量自己编



【zyc】2020.05.23 创建了开发日志，准备开始写miniSQL

【zyc】2020.05.23 又更新了一次试试git怎么使用

【zyc】2020.05.24 添加了一些Interpreter模块的功能，主要是读取输入的指令和一些字符串处理的功能，注释里都有，基本上都参考了https://github.com/Unispac/miniSQL  上面的内容，后面又加了一些处理函数，目前已经做到语义分割部分，刚开始，今天写了半天不想写了

【zyc】2020.05.25继续添加**语义分割**的相关功能，包括select，delete和drop，写了一些基本的SQL语法错误判断，但是正式调用API的部分还没有开始写，后面先继续完成create

【zyc】2020.05.26完成了create和insert语句的初步检查，修复了前面几天出现的一些bug，但可能还有不少bug存在，接下来的工作是要对语句进行进一步的语法分割

【zyc】2020.05.29 更新了二级语法处理的相关代码，下面可以开始写API调用了，同时我改掉了所有的括号换行，不过select部分由于比较麻烦先没有写，等以后慢慢补充，接下来可以先开始准备API调用的编写了，而且table的数据结构之类的东西需要注意一下，这个好像比较麻烦，要先写一个table的数据结构

【zyc】2020.05.30 添加一个table的数据结构，事实上基本都是照搬**参考文献**里的数据结构的，不得不说那个人是真的🐂

【zyc】2020.05.31添加了一个logic的模块，用于比较数据表中数据的大小

【zyc】2020.06.01 添加了几个文件夹，表示整个系统的基本结构，添加了API模块的基本结构，把interpreter中所有调用来调用去的接口全部调通了，**interpreter模块基本完成**，接下来需要写调用API的模块，这牵涉到其他更多的manager模块，非常麻烦，我已经被绕晕了，后面又加了一个block的模块

【zyc】2020.06.06 半夜更新了一点catalog manager的基本框架

【zyc】2020.06.07 晚上出去吃了一顿鸡翅，所以今天更新的不是很多，主要是catalog mamager里面写了几个函数

【zyc】2020.06.08 主要在写catalog Manager，注意table信息表和index信息表中的信息的顺序。应该是这样的

> table：由若干行table的属性组成，每一行中的属性的内容和顺序如下：属性的数据类型，数据长度(主要针对char*类型，数字型的都是4)，属性名，是否unique，是否为主键，是否有索引
>
> index：所有的表共享一个文件，里面每行写的内容是索引名+表名+属性名，文件名是indexNameList.db
>
> 此外所有的表名都写在文件tableNameList.db文件里

今天一天下来catalog模块基本完成，明天把最后一个函数写好应该就可以用了

【zyc】2020.06.09 写完了catalog manager，添加了一个file manager的模块，下属于buffer manager模块

【zyc】2020.06.13 写了一大堆bullshit code完成了一个delete语句的语法二次分解，感觉有点麻烦，语法分解的地方还差最后一个select的语法分解，不过select的地方代码可以复用，预计明天考完证券可以继续搞，问题是好像不容易进行测试，我也不知道有没有bug-free

【zyc】2020.06.14 写了一个create table的语法分割，但是**还没有经过测试**，不知道能不能用

### 6.16 更新 现在miniSQL的状况简要介绍

- 现在已经能完整运行的部分有interpreter部分，每种语句的语法检查和语义分解已经做的差不多了，**整个系统需要完成的逻辑是**
  - main函数里调用interpreter类对输入的SQL指令进行初步的处理，然后大致分成create table， create index，select，delete，drop等若干类，
  - 然后用callAPI类对这些语句进行第二次语法分割(第一次主要是要分割出SQL操作类型，第二次主要是把insert，delete，select等有条件和数值的语句的条件和数值分解出来)，
  - 然后callAPI把规定格式的数据作为参数调用对应的API，
  - API里调用各种manager进行一系列操作，然后返回结果true or false，API需要调用的模块有
    - buffer manager 用来读取数据表
    - catalog manager 需要记录每张表和index的信息，以及一个表名的合集和一个索引的合集，都用文件存储
    - index manager 用来在create index等操作调用的API里生成/更新/删除索引，具体要求看老师发的
    - record manager 主要负责数据表的更新创建等操作
  - 最后再调用showResult类来展示一系列结果
- 几个特殊的类，不属于功能模块但是有自己的作用
  - globalvariable，主要写了一些全局都用得上的数据结构和**宏定义(这一部分可以自己看一下)**，包括用于存储where语句后面的逻辑关系的类logicCompare和数值类型tableValue，具体的定义可以看代码文件
  - table和tableFile，主要涉及二进制数据**表文件的数据结构**和**读写**操作，table类中包含了一个表所拥有的信息，tableFile用于二进制文件的读写，也就是读取表的数据，**tableFile还没写**
  - stringProcessor 主要是一些字符串处理的函数，这个主要是在interpreter里面用

- 现在的完成情况是

  - interpreter部分基本完成，已经没有大bug，可以把SQL语句进行初步判断发给callAPI，已经进行了多次测试，基本没啥问题，**这一部分基本可以略去不看了**

  - callAPI里的**二次分割**也没有大问题了，我测试了很多次，只需要再完善API里各个模块的调用即可

  - showResult已经没有问题了，只要API返回成功的结果就可以显示

  - API的具体调用还没写，可以留到几个manager模块基本完成后再写对每个模块进行测试

  - 几个manager的完成情况

    - ### buffer 除了一个类定义什么都没有

    - ### index 除了一个类定义什么都没有

    - catalog **基本写完了**，但是没有经过具体的测试，因为不好测试

    - record manager 本来想写，但是发现需要和buffer进行联动还比较棘手，暂时没想好怎么处理

- 几个特殊类的完成情况
  - logicCompare 写完了，照抄的，应该没啥问题
  - tableValue 就是一个有三种值(int, float, char*)的结构，这么写主要是可以用一种类型存储表中出现的任何数据，然后取用数据的时候根据属性里定义的类型来取出结构体中对应的内容就可以了
  -  dataType 表示表中的一种属性的类型，写完了，应该没有大问题
  - table 表示一张表的类，有若干dataType的index，以及表中的一些关键信息，写完了
  - tableFile 数据表文件，还没写，要和record manager进行联动，然后record manager要和buffer进行联动
  - stringProcessor 字符串处理的一些东西，写完了，主要是在interpreter里调用，没有大问题

- 具体的内容可以看代码文件，我也尽量写了注释，另外就是多看看上面的**参考网址** 
- 目前剩下的主要问题
  - 有几个模块没有进行debug，比如catalog，可能需要和别的模块一起进行debug
  - record + buffer + tableFile的联动
  - index manager建立B+树索引
 
【zq】2020.06.20 更新了一下recordManager.h，写了几个函数。发现涉及到tableFile.h里的几个函数，但里面还是空的，就对tableFile类进行了声明。顺手改了几个让我不爽的缩进。
