#pragma once
#include <iostream>
#include <cstring>
#include "iProduct.h"


#ifndef AMA_AMAAPP_H
#define AMA_AMAAPP_H

namespace ama
{
	const int iProductArrayNum = 100;
	class AmaApp
	{
		char m_filename[26];
		iProduct* m_products[iProductArrayNum];
		int m_noOfProducts;
		void pause() const;
		int menu() const;
		void loadProductRecords();
		void saveProductRecords() const;
		void listProducts() const;
		void deleteProductRecord(iProduct* product);
		void sort();
		iProduct* find(const char* sku) const;
		void addQty(iProduct* product);
		void addProduct(char tag);
	public:
		AmaApp(const char charArray[14]);
		int run();
		~AmaApp();
	};
	


}

#endif