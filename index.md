---
layout: default
---

# libll++ blog

我是一个40多岁的程序员，生活在中国，北京。在1998-2013年之间，我一直用c语言开发类unix系统的服务器应用。2013年，我打算陪我儿子度过一个夏季，有点空闲时间，我突然想试试c++。由于以前的开发背景，我没有boost相关的知识背景，但是c++11已经被标准化了。我想我没必要从最原始开始，就从c++11开始吧。c++的思维模式跟c语言有很大的差别，在此期间我经历了很长时间的思维冲突，反复的思考和困惑，甚至现在有时候也是这样。

libll++是我这段时间学习开发库，发布在：https://github.com/storming/libllpp.git.

如果你对libll++有任何建议，可以发email给我：storm@vip.163.com

2013-9-1
<hr>  
##2013-9-1 member

对于c语言工程师来说，使用内存池和嵌入式的数据结构还有宏是相当习惯的事情。某种意义上，这种语法上的缺失保障了c语言程序的高效，就像拥有越少的人越努力。
下面的例子是个很标准的c语言链表声明。

	struct foo {
		LIST_ENTRY(foo) _entry
	}
	
	LIST_HEAD(, foo) alist;

这种链表相关宏，在linux的queue.h中。这跟STL的方式有较大的不同，STL是数据算法分离模式，而在c中往往是融合模式。
这在内存处理上有较大的优势。而STL则显得更加学术性。
这种模式阐述了一种本质，代码是静态的，只有数据是动态的。静态说明本质。如果你曾经属于某个容器，你就具有这个容器的特质。
在现实的开发中，这屡屡被验证，甚至几乎不会出现偏差。

如果要在c++中实现c的这种模式，难度是很大的。offsetof在g++中需要编译选项，container_of(这是linux kernel的宏)就更加困难了。

好在c++模板支持类成员地址，这给我的想法提供了一线生机。
对于开发者意图来说，如果用c++，我就不太情愿用宏，除非在语法上无法再简化了。
效率不是我担心的问题，到语法树级别，c和c++可能会有差别，但是差距不大。

为此，我在libll++里写的第一个文件就是member.h，它是一切class member相关操作的基础。
考虑到c++是个多重继承语言，在做这方面的操作的时候，需要有个清晰的认识。

	/* typeof_member */
	template <typename _T, typename _C>
	_T typeof_member_helper(_T _C::*member);
	#define typeof_member(x) decltype(ll::typeof_member_helper(x))


	/* typeof_container */
	template <typename _T, typename _C>
	_C typeof_container_helper(_T _C::*member);
	#define typeof_container(x) decltype(ll::typeof_container_helper(x))

