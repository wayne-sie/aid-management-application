//Wayne Sie 139951180 BTP200SCC Cornel Barna

#include <iostream>
#include "Product.h"
#include "Perishable.h"
#include "Utilities.h"


namespace ama
{
	double& operator+=(double& total, const iProduct& prod)
	{
		total += prod.total_cost();
		return total;
	}

	std::ostream& operator<<(std::ostream& out, const iProduct& prod)
	{
		prod.write(out, write_human);
		return out;
	}

	std::istream& operator>>(std::istream& in, iProduct& prod)
	{
		prod.read(in, true);
		return in;
	}

	iProduct* createInstance(char tag)
	{
		iProduct* newAcc = nullptr;
		if (tag == 'N' || tag == 'n')
		{
			newAcc = new Product();
		}
		else if (tag == 'p' || tag == 'P')
		{
			newAcc = new Perishable();
		}
		return newAcc;
	}
}