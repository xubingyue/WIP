#include <iostream>
#include <ctime>

#include "WPMap.h"
#include "WPVector.h"
#include "WPHash_Map.h"
#include "WPList.h"
#include <map>
//测试四种map性能
enum EA
{
	A,
	B,
	C,
	D
};
//use [] operator to set value not to insert element.
int main()
{
	Hash_Map<EA,int> amap;
	Hash_Map<EA,int> hash_map;
	//Hash_Map<EA,int> hash_map;
	time_t st = 0,et = 0;
	int s = 0;
	std::cin>>s;
	hash_map[A] = 0x00000001;
	hash_map[B] = 0x00000003;
	hash_map[C] = 0xffffffff;
	hash_map[D] = 0x00fecdee;
	st = clock();

	for(int i=0;i<s;++i)
	{
	

	//std::cout<<hash_map[A]<<","<<hash_map[B]<<","<<hash_map[C]<<","<<hash_map[D]<<std::endl;
	//getchar();
	hash_map[A] = 0xffffffff;
	hash_map[B] = 0xffffffff;
	hash_map[C] = 0xffffffff;
	hash_map[D] = 0xffffffff;
	//std::cout<<hash_map[A]<<","<<hash_map[B]<<","<<hash_map[C]<<","<<hash_map[D]<<std::endl;
	//getchar();
	}
	et = clock();
	std::cout<<et - st<<std::endl;
	amap[A] = 0x00000001;
	amap[B] = 0x00000003;
	amap[C] = 0xffffffff;
	amap[D] = 0x00fecdee;
	st = clock();

	for(int i=0;i<s;++i)
	{

		amap[A] = 0xffffffff;
		amap[B] = 0xffffffff;
		amap[C] = 0xffffffff;
		amap[D] = 0xffffffff;
	}
	et = clock();
	std::cout<<et - st<<std::endl;
	std::cin>>s;
	return 0;
}