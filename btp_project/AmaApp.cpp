
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include "iProduct.h"
#include "Product.h"
#include "AmaApp.h"
#include "Utilities.h"
#include "Sort.h"



using namespace ama;
using namespace std;

namespace ama
{
	AmaApp::AmaApp(const char charArray[14])
	{
		strcpy(m_filename, charArray);
		for (int i = 0; i < iProductArrayNum; i++)
		{
			m_products[i] = nullptr;
		}
		m_noOfProducts = 0;
		loadProductRecords();
	}

	AmaApp::~AmaApp()
	{
		for (int i = 0; i < 100; i++)
		{
			delete m_products[i];
		}
	}

	void AmaApp::pause() const
	{
		do
		{
			std::cout << "Press Enter to continue..." << endl;
		} while (std::cin.get() != '\n');
	}

	int AmaApp::menu()const
	{
		int selection;
		std::cout << "Disaster Aid Supply Management Program" << endl;
		std::cout << "--------------------------------------" << endl;
		std::cout << "1- List products" << endl;
		std::cout << "2- Search product" << endl;
		std::cout << "3- Add non-perishable product" << endl;
		std::cout << "4- Add perishable product" << endl;
		std::cout << "5- Add to product quantity" << endl;
		std::cout << "6- Delete product" << endl;
		std::cout << "7- Sort products" << endl;
		std::cout << "0- Exit program" << endl;
		std::cout << "> ";
		std::cin >> selection;
		//std::cin.ignore(100, '\n');
		if (std::cin.fail() || selection <0 || selection >7)
		{
			
			selection = -1;
		}
		std::cin.ignore(100,'\n');
		std::cin.clear();
		
		return selection;
	}

	void AmaApp::loadProductRecords()
	{
		/*fstream theFile(m_filename, ios::in);*/
		fstream theFile;
		theFile.open(m_filename,ios::in);
		if (theFile.is_open())
		{
			int count = 0;
			char typeOfProduct;
			for (int i = 0; i < iProductArrayNum; i++)
			{
				if (m_products[i] != nullptr)
				{
					delete m_products[i];
					m_products[i] = nullptr;
				}
			}
			while (!theFile.eof())
			{
				typeOfProduct = '\0';
				theFile.get(typeOfProduct);
				theFile.ignore();
				iProduct* prodProd = createInstance(typeOfProduct);
				if (prodProd != nullptr)
				{
					m_products[count] = prodProd;
					prodProd->read(theFile, false);
					count++;
					/*theFile.ignore(100, '\n');*/
				}
			}
			m_noOfProducts = count;
			theFile.close();
		}
		else
		{
			ofstream createFile("inventory.txt");
			createFile.close();
		}	
	}

	void AmaApp::saveProductRecords() const
	{
		fstream theFile;
		theFile.open(m_filename,ios::out);
		if (theFile.is_open())
		{
			for (int i = 0; i < m_noOfProducts; i++)
			{
				m_products[i]->write(theFile, write_condensed);
				theFile << endl;
			}
		}
		theFile.close();
		
	}

	void AmaApp::listProducts() const
	{
		double cost_support = 0;
		fstream theFile(m_filename, ios::in);
		/*if (theFile.is_open())
		{*/
			std::cout << "------------------------------------------------------------------------------------------------" << endl;
			std::cout << "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl;
			std::cout << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;
			for (int i = 0; i < m_noOfProducts; i++)
			{

				std::cout << "|";
				std::cout.setf(ios::right);
				std::cout << setw(4) << i + 1;
				std::cout << " |";
				m_products[i]->write(std::cout, write_table);
				cost_support += m_products[i]->total_cost();
				std::cout << endl;

			}
			std::cout << "------------------------------------------------------------------------------------------------" << endl;
			std::cout << "|                                                      Total cost of support ($): | ";
			std::cout.setf(ios::right);
			std::cout.precision(2);
			std::cout << setw(10) << cost_support;
			std::cout << " |" << endl;
			std::cout << "------------------------------------------------------------------------------------------------" << endl<<endl;
			pause();
		/*}
		theFile.close();*/
	}

	void AmaApp::deleteProductRecord(iProduct* product)
	{
		fstream theFile(m_filename, ios::out);
		
		if (theFile.is_open())
		{
			for (int i = 0; i < m_noOfProducts; i++)
			{
				if (!(m_products[i]->name() == product->name()))
				{
					m_products[i]->write(theFile, write_condensed);
					theFile << endl;
				}
			}
		}
		theFile.close();
	}

	void AmaApp::sort()
	{
		sict::sort(m_products, m_noOfProducts);
	}
	
	iProduct* AmaApp::find(const char* sku) const
	{
		for (int i = 0; i < m_noOfProducts; i++)
		{
			
			if (*m_products[i] == sku)
			{
				return m_products[i];
			}
		}
		return nullptr;
	}
	void AmaApp::addQty(iProduct * product)
	{
		int prodInHandToAdd;
		int qtyHandVar, qtyNeededVar;
		std::cout << *product;
		std::cout << endl << endl;
		std::cout << "Please enter the number of purchased items: ";
		std::cin >> prodInHandToAdd;
		if (std::cin.fail())
		{
			
			std::cin.clear();
			std::cout << "Invalid quantity value!" <<endl<< endl;
			std::cin.ignore(100, '\n');

		}
		else
		{
			qtyHandVar = product->qtyAvailable();
			qtyNeededVar = product->qtyNeeded();
			
			if (qtyNeededVar - qtyHandVar >= prodInHandToAdd)
			{
				*product += prodInHandToAdd;

			}
			else
			{
				*product += (qtyNeededVar - qtyHandVar);
				std::cout << "Too many items; only " << qtyNeededVar - qtyHandVar << " is needed. Please return the extra "
					<< prodInHandToAdd - (qtyNeededVar - qtyHandVar) << " items." << endl;
			}
			saveProductRecords();
			std::cout << endl << "Updated!" << endl<<endl;
			std::cout << flush;
		}

	}

	void AmaApp::addProduct(char tag)
	{
		iProduct* prodProd = createInstance(tag);
		if (prodProd != nullptr)
		{
			std::cin >> *prodProd;
			if (std::cin.fail())
			{
				std::cin.clear();
				cin.ignore(100,'\n');
				std::cout <<endl << *prodProd << endl << endl;
				delete prodProd;
			}
			else
			{
				m_products[m_noOfProducts] = prodProd;
				m_noOfProducts++;
				saveProductRecords();
				std::cout << endl << "Success!" << endl << endl;
			}
		}
	}

	int AmaApp::run()
	{
		bool game = true;
		char skuInput[max_length_sku + 1];
		skuInput[0] = '\0';
		while (game)
		{

			int optionSelected = menu();
			switch (optionSelected)
			{
			case 1:
				listProducts();
				//std::cin.ignore(100, '\n');
				break;
			case 2:
				std::cout << "Please enter the product SKU: ";
				/*std::cin.ignore(100,'\n');*/
				std::cin.getline(skuInput, '\n');
				if (std::cin.good())
				{

					iProduct* prodProd = find(skuInput);
					if (prodProd != nullptr)
					{
						fstream theFile(m_filename, ios::in);
						{
							if (theFile.is_open())
							{
								prodProd->write(std::cout, write_human);
								std::cout << endl;
							}
						}
						theFile.close();
					}
					else
					{
						/*cin.ignore(100, '\n');*/
						std::cout <<endl<< "No such product!" << endl;
					}
					skuInput[0] = '\0';
					pause();
					break;
				}

			case 3:
				//std::cin.ignore(100, '\n');
				addProduct('n');
				if (!std::cin.fail())
				{
					loadProductRecords();
				}
				/*else
				{
					cin.ignore(100, '\n');
				}*/
				break;
			case 4:
				addProduct('p');
				if (!std::cin.fail())
				{
					loadProductRecords();
				}
				else
				{
					cin.ignore(100, '\n');
				}
				break;
			case 5:
				//std::cin.ignore(100, '\n');
				std::cout << "Please enter the product SKU: ";
				std::cin.getline(skuInput, '\n');
				if (std::cin.good())
				{

					iProduct* prodProd = find(skuInput);
					if (prodProd != nullptr)
					{
						/*prodProd->write(std::cout, write_human);*/
						/*std::cout << endl << endl;*/
						/*fstream theFile(m_filename, ios::in);
						{
							if (theFile.is_open())
							{
								
							}
						}
						theFile.close();*/
						addQty(prodProd);
					}
					else
					{
						std::cout << endl<< "No such product!" << endl << endl;
					}
				}
				skuInput[0] = '\0';
				std::cin.clear(); //things to check first
				break;
			case 6:
				std::cout << "Please enter the product SKU: ";
				
				std::cin.getline(skuInput, '\n');
				if (std::cin.good())
				{

					iProduct* prodProd = find(skuInput);
					if (prodProd != nullptr)
					{
						/*fstream theFile(m_filename, ios::in);
						{
							if (theFile.is_open())
							{
								
							}
						}
						theFile.close();*/
						deleteProductRecord(prodProd);
						loadProductRecords();
						std::cout << endl<< "Deleted!" << endl;
						
					}
					else
					{
						std::cout << endl <<"No such product!" << endl;
					}
				}
				skuInput[0] = '\0';
				break;
			case 7:
				sort();
				saveProductRecords();
				std::cout << "Sorted!" << endl << endl;
				//std::cin.ignore(100, '\n');
				break;
			case 0:
				game = false;
				std::cout << "Goodbye!" << endl;
				//std::cin.ignore(100, '\n');
				break;
			default:
				std::cout << "~~~Invalid selection, try again!~~~" << endl;
				/*std::cin.ignore(100, '\n');*/
				pause();
				break;
			}
		}
		return 0;
	}
}