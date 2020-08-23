#pragma once
#ifndef SICT_SORT_H
#define SICT_SORT_H

namespace sict
{
	template<typename T>
	void sort(T a[], int size)
	{
		T temp;
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (*a[i] > *a[j])
				{
					temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
		}
	}

}

#endif