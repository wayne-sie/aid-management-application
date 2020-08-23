//Wayne Sie 139951180 BTP200SCC Cornel Barna
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Product.h"
#include "iProduct.h"
#include "Utilities.h"
#include "ErrorState.h"

using namespace std;
using namespace ama;

namespace ama
{
	Product::Product(const char pType) : productType(pType) //use initialization list for constants and references
	{
		this->sku[0] = '\0';
		this->productDesc[0] = '\0';
		this->productName = nullptr;
		this->productQuantityInHand = 0;
		this->productQuantityNeeded = 0;
		this->unitPrice = 0;
		this->taxable = true;
		errorStatus.message(nullptr);
	}

	Product::Product(const char* skuNum, const char* name, const char* unit, double price,
		int quantityNeeded, int quantityOnHand, bool canTax) : productType('N')
	{
		if (name == nullptr)
		{
			*this = Product(productType);
		}
		else
		{
			this->productName = new char[max_length_name + 1];
			int length = strlen(name);
			strcpy(this->sku, skuNum);
			strncpy(this->productName, name,length);
			productName[length] = '\0';
			strcpy(this->productDesc, unit);
			this->unitPrice = price;
			this->productQuantityNeeded = quantityNeeded;
			this->productQuantityInHand = quantityOnHand;
			this->taxable = canTax;
			this->errorStatus.message(nullptr);
		}

	}

	//copy constructor
	Product::Product(const Product& other) : productType('N')
	{

		this->productName = nullptr;
		*this = other;
	}

	Product & Product::operator=(const Product & other)
	{
		if (this!=&other)
		{
			delete[] productName;
			strcpy(sku, other.sku);
			strcpy(productDesc, other.productDesc);
			productQuantityInHand = other.productQuantityInHand;
			productQuantityNeeded = other.productQuantityNeeded;
			unitPrice = other.unitPrice;
			taxable = other.taxable; 
			errorStatus.message(other.errorStatus.message());
			int length = strlen(other.productName);
			if (other.productName != nullptr)
			{
				
				this->productName = new char[max_length_name + 1];
				for (int i = 0; i < length; i++)
				{
					this->productName[i] = other.productName[i];
				}
			}
			productName[length] = '\0';
		}
		else
		{
			this->productName = nullptr;
		}
		return *this;

	}



	Product::~Product()
	{
		delete[] productName;
		productName = nullptr;
	}

	int Product::operator+=(int cnt)
	{
		if (cnt > 0)
		{
			this->productQuantityInHand += cnt;
		}
		return this->productQuantityInHand;


	}

	void Product::message(const char* pText)
	{
		this->errorStatus.message(pText);
	}

	bool Product::isClear() const
	{
		return !(this->errorStatus);
	}

	bool Product::operator==(const char* sku) const
	{
		return(strcmp(this->sku, sku) == 0);
	}

	bool Product::operator>(const char* sku) const
	{
		return strcmp(this->sku, sku) > 0;
	}

	bool Product::operator>(const iProduct& prod) const
	{
		return(strcmp(this->name(), prod.name()) > 0);
	}

	int Product::qtyAvailable() const
	{
		return this->productQuantityInHand;
	}

	int Product::qtyNeeded() const
	{
		return this->productQuantityNeeded;
	}

	const char* Product::name() const
	{
		return this->productName;
	}

	double Product::total_cost() const
	{ 
		if (taxable)
		{
			return (unitPrice * qtyAvailable()) * (1 + tax_rate);
		}
		else
		{
			return (unitPrice * qtyAvailable());
		}
		
	}

	bool Product::isEmpty() const
	{
		return (this->productName==nullptr);
	}

	std::istream& Product::read(std::istream& in, bool interactive)
	{
		char skuNum[max_length_sku+1];
		char prodName[max_length_name+1];
		char prodDesc[max_length_unit + 1];
		int prodNeeded, prodInHand;
		char properTaxResponse;
		double thePrice=0;
		bool boolCanTax = false;
		/*bool game = true;*/

		if (!interactive)
		{
			in.getline(skuNum, max_length_sku+1, ',');
			in.getline(prodName, max_length_name+1, ',');
			in.getline(prodDesc, max_length_unit+1, ',');
			if (in.good())
			{
				in >> thePrice;
				if (thePrice < 0)
				{
					this->errorStatus.message("Invalid Price Entry!");
					in.setstate(ios::failbit);
				}
				in.ignore();
				in >> boolCanTax;
				in.ignore();
				in >> prodInHand;
				if (prodInHand < 0)
				{
					this->errorStatus.message("Invalid Quantity Available Entry!");
					in.setstate(ios::failbit);
				}
				in.ignore();
				in >> prodNeeded;
				if (prodNeeded < 0)
				{
					this->errorStatus.message("Invalid Quantity Needed Entry!");
					in.setstate(ios::failbit);
				}
				if (in.peek() == '\n')
				{
					in.ignore(100,'\n');
				}
				Product tmp(skuNum, prodName, prodDesc, thePrice, prodNeeded, prodInHand, boolCanTax);
				*this = tmp;
				
			}
			
		}
		else
		{
			cout.setf(ios::right);
			cout << setw(max_length_label) << "Sku: ";
			in.getline(skuNum, max_length_sku + 1, '\n');
			cout << setw(max_length_label) << "Name (no spaces): ";
			in.getline(prodName, max_length_name + 1, '\n');
			cout << setw(max_length_label) << "Unit: ";
			in.getline(prodDesc, max_length_unit + 1, '\n');
			//	while (game)
			//	{
			//		cout << setw(max_length_label) << "Taxed? (y/n): ";
			//		in >> properTaxResponse;
			//		
			//		if (properTaxResponse == 'y' || properTaxResponse == 'Y' || properTaxResponse == 'n' || properTaxResponse == 'N')
			//		{
			//			boolCanTax = properTaxResponse == 'y' || properTaxResponse == 'Y';
			//		}
			//		else
			//		{
			//			this->errorStatus.message("Only (Y)es or (N)o are acceptable!");
			//			/*cout << endl<<this->errorStatus.message();*/
			//			in.setstate(ios::failbit);
			//			game = false;
			//			break;
			//		}
			//		in.ignore();
			//		cout << setw(max_length_label) << "Price: ";
			//		in >> thePrice;
			//		
			//		if (thePrice < 0 || in.fail())
			//		{
			//			this->errorStatus.message("Invalid Price Entry!");
			//			/*cout << endl<<this->errorStatus.message();*/
			//			/*in.ignore(100, '\n');*/
			//			in.setstate(ios::failbit);
			//			game = false;
			//			break;
			//		}
			//		in.ignore();
			//		cout << setw(max_length_label) << "Quantity on hand: ";
			//		in >> prodInHand;
			//		
			//		if (prodInHand < 0 || in.fail())
			//		{
			//			this->errorStatus.message("Invalid Quantity Available Entry!");
			//			/*in.ignore(100, '\n');*/
			//			/*cout << endl<< this->errorStatus.message();*/
			//			in.setstate(ios::failbit);
			//			game = false;
			//			break;

			//		}
			//		in.ignore();
			//		cout << setw(max_length_label) << "Quantity needed: ";
			//		in >> prodNeeded;
			//		
			//		if (prodNeeded < 0 || in.fail())
			//		{
			//			this->errorStatus.message("Invalid Quantity Needed Entry!");
			//			/*in.ignore(100, '\n');*/
			//			/*cout << endl<<this->errorStatus.message();*/
			//			in.setstate(ios::failbit);
			//			game = false;
			//			break;
			//		}
			//		in.ignore();
			//		Product tmp(skuNum, prodName, prodDesc, thePrice, prodNeeded, prodInHand, boolCanTax);
			//		*this = tmp;
			//		game = false;
			//	}
			//	//cout.unsetf(ios::right);
			//}
			cout << setw(max_length_label) << "Taxed? (y/n): ";
			in >> properTaxResponse;
			if (properTaxResponse != 'y' && properTaxResponse != 'Y' && properTaxResponse != 'n' && properTaxResponse != 'N')
			{
				/*in.ignore(100, '\n');*/
				in.setstate(ios::failbit);
				this->errorStatus.message("Only (Y)es or (N)o are acceptable!");
			}
			else
			{
				cout << setw(max_length_label) << "Price: ";
				in >> thePrice;
				if (thePrice < 0 || in.fail())
				{
					/*in.ignore(100, '\n');*/
					in.setstate(ios::failbit);
					this->errorStatus.message("Invalid Price Entry!");
				}
				else
				{
					cout << setw(max_length_label) << "Quantity on hand: ";
					in >> prodInHand;
					if (prodInHand < 0 || in.fail())
					{
						/*in.ignore(100, '\n');*/
						in.setstate(ios::failbit);
						this->errorStatus.message("Invalid Quantity Available Entry!");
					}
					else
					{
						cout << setw(max_length_label) << "Quantity needed: ";
						in >> prodNeeded;
						if (prodNeeded < 0 || in.fail())
						{
							/*in.ignore(100, '\n');*/
							in.setstate(ios::failbit);
							this->errorStatus.message("Invalid Quantity Needed Entry!");
						}
					}
				}
			}
			if (!in.fail())
			{
				boolCanTax = properTaxResponse == 'y' || properTaxResponse == 'Y';
				Product tmp(skuNum, prodName, prodDesc, thePrice, prodNeeded, prodInHand, boolCanTax);
				*this = tmp;
			}
		}

		return in;
	}

	ostream& Product::write(std::ostream& out, int writeMode) const
	{
		if (this->errorStatus)
		{
			out << this->errorStatus.message();
		}
		else
		{
			if (this->isClear() && !(this->isEmpty()))
			{
				if (writeMode == write_condensed)
				{
					out << this->productType << "," << this->sku << "," << this->productName << "," << this->productDesc << "," << this->unitPrice
						<< "," << this->taxable << "," << this->productQuantityInHand << "," << this->productQuantityNeeded;
				}
				else if (writeMode == write_table)
				{
					out << " ";
					out.setf(ios::right);
					out <<setw(max_length_sku)<< this->sku;
					out << " | ";
					out.unsetf(ios::right);
					out.setf(ios::left);
					//char buf[17];
					//strncpy(buf, productName, 16);
					//buf[16] = '\0';
					//if (/*...*/)
					//{
					//	buf[15] = buf[14] = buf[13] = '.';
					//}
					//cout << setw(16) << buf;
					if (strlen(this->productName) > 16)
					{
						for (int i = 0; i < 13; i++)
						{
							out << this->productName[i];
						}
						out << "...";
					}
					else
					{
						out << setw(16)<<this->productName;

					}
					out << " | ";
					out << setw(10) << this->productDesc;
					out << " | ";
					out.unsetf(ios::left);
					out.setf(ios::fixed);
					out << setw(7)<< setprecision(2)<< this->unitPrice;
					out << " | ";
					if (taxable)
					{
						out <<setw(3)<< "yes";
					}
					else
					{
						out <<setw(3)<< "no";
					}
					out << " | ";
					out<<setw(6)<< this->productQuantityInHand;
					out << " | ";
					out << setw(6)<< this->productQuantityNeeded;
					out << " |";

				}
				else if (writeMode == write_human)
				{
					out << endl;
					out.setf(ios::right);
					out.width(max_length_label);
					out << "Sku: ";
					out << this->sku << endl;;
					out.width(max_length_label);
					out << "Name: ";
					out << this->productName << endl;;
					out.width(max_length_label);
					out << "Price: ";
					out.setf(ios::fixed);
					out.precision(2);
					out << this->unitPrice << endl;
					out.width(max_length_label);
					out << "Price after Tax: ";
					out.precision(2);
					if (taxable)
					{
						out << this->unitPrice *(1 + tax_rate) << endl;
					}
					else
					{
						out << this->unitPrice << endl;
					}
					//out.unsetf(ios::fixed);
					out.width(max_length_label);
					out << "Quantity Available: ";
					out << this->productQuantityInHand << " " << this->productDesc << endl;
					out.width(max_length_label);
					out << "Quantity Needed: ";
					out << this->productQuantityNeeded << " " << this->productDesc << endl;
				}
			}
		}
		return out;
	}
}