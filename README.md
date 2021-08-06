# NDK_jni_makefile
a JNI project in Android.mk
__________________________________________________

#### 一、C编译流程：
<br/>*test.c :*
```c
#include <stdio.h>

int main(){
printf("hello w\n");
return 0;
}
```
* 1.预处理： `gcc -E test.c -o test.i`
   * 预处理命令的处理，如宏替换，文件引入，头文件包含
* 2.编译: `gcc -S test.i -o test.s`
   * 将预编译代码处理成汇编代码，检查代码规范性，即语法语义分析

* 3.汇编: `gcc -c test.s -o test.o`
   * 将.s汇编代码转换成二进制目标机器代码
* 4.链接：`gcc test.o -o test`
   * 将多个目标文件和头文件打包成可执行文件

编译完成，生成的可执行文件可以直接执行：
./test
*******
#### 二、静态库与动态库：
* 静态库：
   * 若干目标文件.o文件的集合，以.a文件格式结尾，只用于生成可执行文件阶段。
      
       * 1.先生成目标文件：
         <br/> `gcc -c test.c -o test.o`
      * 2.使用ar命令将目标文件打包成静态库
         <br/> `ar rcs libtest.a test.o` or
         <br/>`ar:creating libtest.a`
          
   * 查看静态库包含内容：
         <br/>`ar t libtest.a`
         <br/>此处只包含 test.o 


* 动态库：
   * 动态库在链接阶段没有被复制到程序中，而是在运行时由系统加载到内存供程序调用。
系统只需要载入一次，不同的程序可以在内存中得到相同动态库的副本，可以节省内存。

      * 1.先生成目标文件：
      <br/> `gcc -c test.c -o test.o`
      * 2.使用-fPIC 和 -shared生成动态库：
      <br/> `gcc -shared -fPIC -o libtest.so test.o`

   * 假设三个文件：* main.c tool.c tool.h*
main.c:
```c
#include <stdio.h>
#include "tool.h"

int main(){
	int arr[] = {1,3,5,8};
	int max = find_max(arr,5);
	printf("max = %d\n", max);
	return 0;
}
```
tool.c:
```c
#include "tool.h"

int find_max(int arr[], int n){
	int max = arr[0];
	int i;
	for(i = 0; i< n; i++){
		if(arr[i] > max){
			max = arr[i];
		}
	}
	return max;
}
```
tool.h:
```c
#ifndef MAIN
#define MAIN

#include <stdio.h>

int find_max(int arr[], int n);

#endif
```
 ** 步骤 **：

   * `gcc -c tool.c` 生成tool.o

   * `ar rcs libtool.a tool.o` 生成libtool.a

   * `gcc -o main main.c -L. -ltool` 生成可执行main(L表示搜寻目录，点表示当前目录)

   * `./main` 执行

   * `ls -lh` 查看大小
   * `ldd main` 查看包含的库文件

   * 根据.o文件生成.so文件：
   <br/> `gcc -shared -fPIC -o libtool.so tool.o`
   <br/> `gcc -o main main.c -L. -ltool`

   <br/> 如果直接./main会报错，设置查找库的环境变量，
   LD_LIBRARY_PATH =../main

   * 静态库与动态不同：

> 静态库：在编译时会链接到目标代码中，程序运行时不再需要静态库，每次编译都要载入静态代码，内存开销大。
动态库：编译时不会连接到目标代码中，而是程序运行时载入，只需载入一次，内存开销小。



#### 三、makefile文件
      makefile定义了编译规则，哪些先编译，哪些重新编译，如何链接等规则。makefile就是自动化编译，告诉make命令如何编译链接。

> 默认在当前目录下寻找文件。
文件内容包含：
1）显示规则：生成一个或多个目标文件
2）隐晦规则：
3）变量定义：
4）文件指示：
5）注释：

> target:目标文件
prerequisites:依赖文件
command:make要执行的命令
反斜杠可以作为换行符

```make
main: main.o tool.o
gcc main.o tool.o -o main
.PHONY:clean
clean:
-rm main *.o
```
* makefile中的变量：
```make
objects = main.o tool.o
main: $(objects)
gcc $(objects) -o main
.PHONY:clean
clean:
-rm main $(objects)
```

*  makefile中引入其他的makefile:
```cmake
   #[[假设有:
   a.mk, b.mk, c.mk
   foo.make
   bar = e.mk f.mk]]

include foo.make *.mk $(bar) #等价于：
include foo.make a.mk b.mk c.mk e.mk f.mk

#如果文件找不到依然继续执行，可以在include前加'-':
-include <filename>
```

* makefile预定义变量
![makefile预定义变量](https://user-images.githubusercontent.com/36436771/128516079-85e7b97e-0aa8-4a34-af1f-2529016ce3b2.png)

* makefile自定变量
![makefile自定变量](https://user-images.githubusercontent.com/36436771/128516165-09150d71-071b-44ae-8c42-b5554c7cdccd.png)

* 普通用法：
```
gcc -c 代表 tool.c ---> tool.o
gcc -c 代表 main.c ----> main.o
gcc -o main main.o tool.o ----> main
./main-------->执行文件
```
* 在makefile中的用法：
      vim makefile
      编辑：
 ```
main: main.o tool.o
gcc main.o tool.o -o main
.PHONY:clean
clean:
-rm main *.o
```
 命令窗口执行：
```
make clean
make
./main
```

* 使用变量：
```make
objects = main.o tool.o
main: $(objects)
gcc $(objects) -o main
.PHONY:clean
clean:
-rm main $(objects)
```

* 使用函数：
```make
# 函数名是func
define func
$(info "hello")
endef

# 调用函数
$(call func)

objects = main.o tool.o
main: $(objects)
gcc $(objects) -o main
.PHONY:clean
clean:
-rm main $(objects)
```

* 带参数函数：
```make
define func1
$(info $(1) $(2))
endef

$(call func1, hello, world)

objects = main.o tool.o
main: $(objects)
gcc $(objects) -o main
.PHONY:clean
clean:
-rm main $(objects)
```

#### 四、 Android.mk

是一个向Android NDK 构建系统描述项目的GNU makefile片段，可编译生成：
apk,java库(.jar),c/c++应用程序，c/c++静态库(.a), c/c++动态库(.so)

	** 规则：**
 	定义模块当前路径（必须定义在文件开头，只需定义一次，my-dir是规定写法） 
```make
LOCAL_PATH := $(call my-dir)
```
 	清空当前环境变量（ LOCAL_PATH 除外）
```make
include $(CLEAR_VARS)
```
 ＃当前模块名（这里会生成 libhello-jni.so)
```make
LOCAL_MODULE := hello-jni
```

 ＃当前模块包含的源代码文件
```make
LOCAL_SRC_FILES := hello-jni.c  poll.c xxx.c
```
 ＃表示当前模圳容被编译成一个共享库
```make
include $(BUILD_SHARED_LIBRARY)
```
![示例](https://user-images.githubusercontent.com/36436771/128515655-191e9aa5-d0bd-4830-884c-38ae690dbebd.png)

#### 四、其他
![多模块共享库](https://user-images.githubusercontent.com/36436771/128515779-5dd869df-d137-4fb1-947b-bebcc48c11f1.png)

![共享模块](https://user-images.githubusercontent.com/36436771/128515901-4e334303-52f2-40d8-bd9b-e843b4e28caa.png)

![预编译库](https://user-images.githubusercontent.com/36436771/128515949-2efa8795-25b5-4681-89f8-14c460012a10.png)












