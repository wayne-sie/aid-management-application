//Wayne Sie 139951180 BTP200SCC Cornel Barna
#pragma once
#include <iostream>
#include "Product.h"
#include "Perishable.h"
#include "iProduct.h"
#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H

namespace ama
{
	double& operator+=(double& total, const iProduct& prod);
	std::ostream& operator<<(std::ostream& out, const iProduct& prod);
	std::istream& operator>>(std::istream& in, iProduct& prod);
	iProduct* createInstance(char tag);
}
#endif