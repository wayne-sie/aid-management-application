
#pragma once
#include <iostream>
#include "ErrorState.h"
#include "iProduct.h"
#ifndef AMA_PROUCT_H
#define AMA_PRODUCT_H

namespace ama
{

	class Product : public iProduct
	{
		const char productType;
		char sku[max_length_sku + 1];
		char productDesc[max_length_unit + 1];
		char* productName;
		int productQuantityInHand;
		int productQuantityNeeded;
		double unitPrice;
		bool taxable;
		ErrorState errorStatus;

	protected:
		void message(const char* pText);
		bool isClear() const;

	public:
		Product(const char pType='N');
		Product(const char* skuNum, const char* name, const char* unit, double price = 0,
			int quantityNeeded = 0, int quantityOnHand = 0, bool canTax = true);
		~Product();
		Product(const Product& other);
		Product& operator=(const Product& other);
		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator>(const char* sku) const;
		bool operator>(const iProduct& prod) const;
		int qtyAvailable() const;
		const char* name() const;
		int qtyNeeded() const;
		double total_cost() const;
		bool isEmpty() const;
		std::istream& read(std::istream& in, bool interactive);
		std::ostream& write(std::ostream& out, int writeMode) const;
	};
}

#endif