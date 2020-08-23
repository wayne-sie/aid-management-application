//Wayne Sie 139951180 BTP200SCC Cornel Barna
#include <iostream>
#include <iomanip>
#include "Perishable.h"

using namespace ama;
using namespace std;
namespace ama
{
	Perishable::Perishable() : Product('P')
	{

	};

	std::ostream& Perishable::write(std::ostream& out, int writeMode) const
	{
		Product::write(out, writeMode);
		if (!(this->isClear()) || this->isEmpty())
		{
			return out;
		}
		else
		{
			out.setf(ios::right);
			if (writeMode == write_human)
			{
				out << setw(max_length_label) << "Expiry Date: " << this->expiryDate<<endl;
			}
			else if (writeMode == write_table)
			{
				out << " " << this->expiryDate << " |";
			}
			else if (writeMode == write_condensed)
			{
				out << "," << this->expiryDate;
			}
		}
		return out;
	}

	std::istream& Perishable::read(std::istream& in, bool interactive)
	{
		Product::read(in, interactive);
		if (interactive && this->isClear())
		{	
			cout << setw(max_length_label) << "Expiry date (YYYY/MM/DD): ";
			in >> expiryDate;
			if (this->expiryDate.status() != no_error)
			{
				in.setstate(ios::failbit);
				if (this->expiryDate.status() == error_year)
				{
					this->message("Invalid Year in Date Entry");
					/*cout <<endl<<"Invalid Year in Date Entry";*/
				}
				else if (this->expiryDate.status() == error_mon)
				{
					this->message("Invalid Month in Date Entry");
					/*cout <<endl<< "Invalid Month in Date Entry";*/
				}
				else if (this->expiryDate.status() == error_day)
				{
					this->message("Invalid Day in Date Entry");
					/*cout << endl<<"Invalid Day in Date Entry";*/
				}
				else if (this->expiryDate.status() == error_input)
				{
					this->message("Invalid Date Entry");
					/*cout << endl<<"Invalid Date in Date Entry";*/
				}
			}
		}
		else if(!interactive && this->isClear())
		{
			/*char buff[100];
			in.getline(buff, 100);*/
			in.ignore();
			this->expiryDate.read(in);
			in.ignore(100,'\n');
		}

		return in;
	}
}