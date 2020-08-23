
#pragma once

#include <iostream>
#include "Product.h"
#include "Date.h"

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

namespace ama
{
	class Perishable : public Product
	{
		Date expiryDate;
	public:
		Perishable();
		std::ostream& write(std::ostream& out, int writeMode) const;
		std::istream& read(std::istream& in, bool interactive);
	};
}

#endif