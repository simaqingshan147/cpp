#ifndef SALE_DATA_H  //�жϱ����Ƿ�δ����
#define SALE_DATA_H  
#include <string>
struct Sale_data {
	std::string bookNo;
	unsigned units_sold = 0;  //Ĭ�ϳ�ʼ��
	double revenue = 0.0;
};
#endif

