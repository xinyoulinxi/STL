#ifndef _ALLOC_H_
#define _ALLOC_H_

#include<cstdlib>
namespace STL{
	/*
	** 空间配置器，以字节数为单位去分配内存空间
	** 供Allocator内部使用
	*/

	
	class alloc{
	private:
		enum { __ALIGN = 8 };//小型区块的上调边界
		enum { __MAX_BYTES = 128 };//小型区块的上限,超过 __MAX_BYTES 则直接由malloc分配
		enum { __NFREELISTS = __MAX_BYTES / __ALIGN };//free_lists 个数
		enum { NOBJS = 20 };//每次增加的节点数


	private:
		static size_t ROUND_UP(size_t bytes) {//将 bytes 上调至8的倍数
			return (((bytes)+__ALIGN - 1)&~(__ALIGN - 1));
		}

	private:
		union obj {// free_lists 的节点
			union obj* free_list_link;
			char client_data[1];
		};

		//16个  free_list
		static obj* free_list[__NFREELISTS];
	private:
		//自建内存池
		static char *start_free;//内存池起始位置
		static char *end_free;//内存池结束位置
		static size_t heap_size;

	private://内用函数
		
		//根据区块大小，决定使用第n号free_list。 n 从 0 算起 
		static size_t FREELIST_INDEX(size_t bytes) {
			return (((bytes)+__ALIGN - 1)/__ALIGN - 1);
		}
		//返回一个大小为n的对象，并可能加入大小为n的其他区块到free_list
		static void *refill(size_t n);
		//配置一大块空间，可容纳nobjs个大小为size的区块
		//如果配置nobjs个区块有所不便，nobjs可能会降低
		static char *chunk_alloc(size_t size, size_t& nobjs);

	public:
		static void *allocate(size_t bytes);
		static void deallocate(void *ptr, size_t bytes);
		static void *reallocate(void *ptr, size_t old_sz, size_t new_sz);
	public:
		alloc() {};
		~alloc() {};
		
	};
}

#endif