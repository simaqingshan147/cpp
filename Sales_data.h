#ifndef SALE_DATA_H  //判断变量是否未定义
#define SALE_DATA_H  
#include <string>
struct Sale_data {
	std::string bookNo;
	unsigned units_sold = 0;  //默认初始化
	double revenue = 0.0;
};
#endif

