#include "alloc.h"


namespace STL{

	char *alloc::start_free = 0;
	char *alloc::end_free = 0;
	size_t alloc::heap_size = 0;

	alloc::obj *alloc::free_list[alloc::__NFREELISTS] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	void * alloc::allocate(size_t n) {

		if (n > (size_t)__MAX_BYTES) {
			return (malloc(n));
		}
		//寻找16个 free_lists 中适当大小的一个去取空间
		size_t index = FREELIST_INDEX(n);
		obj *my_free_list = free_list[index];
		
		if (my_free_list == 0) {//没有适合大小的空间，需要从内存池里面取空间
			void * r = refill(ROUND_UP(n));
			return r;
		}
		//有可用空间，从free_list中取出适合大小的区块
		free_list[index] = my_free_list->free_list_link;
		return my_free_list;
	}

	void alloc::deallocate(void *p,size_t n){
		if (n > __MAX_BYTES) {//大于128
			free(p);
		}
		else {//收回到free_lists 中，
			size_t index = FREELIST_INDEX(n);
			obj *node = static_cast<obj *>(p);
			node->free_list_link = free_list[index];
			free_list[index] = node;
		}
	}
	void *alloc::reallocate(void *p, size_t old_sz, size_t new_sz) {
		deallocate(p, old_sz);
		p = allocate(new_sz);

		return p;
	}
	//void* refill(size_t bytes);
	//bytes 已经被上调到8的倍数
	void* alloc::refill(size_t bytes)
	{
		size_t nobjs = 20;
		//chunk_alloc(size_t bytes, size_t& nobjs)，从内存池内取出内存块
		char *chunk = chunk_alloc(bytes, nobjs);
		obj **my_fre_list;
		obj *result;
		obj *current_obj, *next_obj;
		if (1 == nobjs) {
			return chunk;
		}
		my_fre_list = free_list + FREELIST_INDEX(bytes);

		result = (obj*)(chunk);
		*my_fre_list = next_obj = (obj*)(chunk + bytes);
		//将取出的多余的空间加入到相应的free list里面去
		for (int i = 1;; ++i) {
			current_obj = next_obj;
			next_obj = (obj *)((char *)next_obj + bytes);
			if (nobjs - 1 == i) {
				current_obj->free_list_link = 0;
				break;
			}
			else {
				current_obj->free_list_link = next_obj;
			}
		}
		return result;
	}
	char *alloc::chunk_alloc(size_t bytes, size_t& nobjs) {
		char *result = 0;
		size_t need_bytes = bytes * nobjs;
		size_t bytes_left = end_free - start_free;

		if (bytes_left >= need_bytes) {//内存池剩余空间完全满足需要
			result = start_free;
			start_free = start_free + need_bytes;
			return result;
		}
		else if (bytes_left >= bytes) {//内存池剩余空间不能完全满足需要，但足够供应一个或以上的所需求大小区块
			nobjs = bytes_left / bytes;
			need_bytes = nobjs * bytes;
			result = start_free;
			start_free += need_bytes;
			return result;
		}
		else {//内存池剩余空间连一个区块的大小都无法提供
			size_t bytes_to_get = 2 * need_bytes + ROUND_UP(heap_size >> 4);
			if (bytes_left > 0) {
				obj **my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj *)start_free)->free_list_link = *my_free_list;
				*my_free_list = (obj *)start_free;
			}
			start_free = (char *)malloc(bytes_to_get);
			if (!start_free) {//malloc都找不到空间，寻找大小相近的空间
				obj **my_free_list = 0, *p = 0;
				for (int i = 0; i <= __MAX_BYTES; i += __ALIGN) {
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if (p != 0) {
						*my_free_list = p->free_list_link;
						start_free = (char *)p;
						end_free = start_free + i;
						return chunk_alloc(bytes, nobjs);
					}
				}
				end_free = 0;
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(bytes, nobjs);
		}
	}
}