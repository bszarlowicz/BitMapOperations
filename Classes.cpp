#include "Classes.h"

unsigned BitmapaExt::length() const
{
	return Length;
}

unsigned BitmapaExt::width() const
{
	return Width;
}

bool& BitmapaExt::operator()(unsigned x, unsigned y)
{
	return array[x][y];
}

bool BitmapaExt::operator()(unsigned x, unsigned y) const
{
	return array[x][y];
}

BitmapaExt::BitmapaExt(unsigned L, unsigned W)
{
	try
	{
		if(L<=0 || W <= 0)
			throw MyExceptionErrors::WrongValueError();
		else
		{
			Length = L;
			Width = W;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what();
		exit(0);
	}

	try
	{
		array = new bool* [L];
	}
	catch (const std::bad_alloc)
	{
		std::cerr << "\n Error with creating an array" << std::endl;
		std::cin.ignore();
		exit(0);
	}
	for (unsigned i = 0; i < L; i++)
	{
		try
		{
			array[i] = new bool[W];

		}
		catch (const std::bad_alloc)
		{
			std::cerr << "\n Error with creating an array" << std::endl;
			std::cin.ignore();
			exit(0);
		}
	}

	for (unsigned i = 0; i < L; i++)
	{
		for (unsigned j = 0; j < W; j++)
		{
			array[i][j] = false;
		}
	}

}

std::ostream& operator<<(std::ostream& os, const BitmapaExt& mapa)
{
	for (unsigned i = 0; i < mapa.length(); i++)
	{
		for (unsigned j = 0; j < mapa.width(); j++)
		{
			os << mapa(i, j) << " ";
		}
		os << std::endl;
	}

	return os;
}

void Inwersja::przeksztalc(Bitmapa& mapa)
{
	for (unsigned i = 0; i < mapa.length(); i++)
	{
		for (unsigned j = 0; j < mapa.width(); j++)
		{
			if (mapa(i, j) == false)
				mapa(i, j) = true;
			else
				mapa(i, j) = false;
		}
	}
}

void Erozja::przeksztalc(Bitmapa& mapa)
{
	bool** help = fun_create2DimArray(mapa.length(), mapa.width());

	for (unsigned i = 0; i < mapa.length(); i++)
	{
		for (unsigned j = 0; j < mapa.width(); j++)
		{
			if (checkNeighboursErozja(mapa, i, j) == true)
			{
				help[i][j] = true;
			}
			else
				help[i][j] = false;
		}
	}

	for (unsigned i = 0; i < mapa.length(); i++)
	{
		for (unsigned j = 0; j < mapa.width(); j++)
		{
			mapa(i, j) = help[i][j];
		}
	}
}

void Dylatacja::przeksztalc(Bitmapa& mapa)
{
	bool** help = fun_create2DimArray(mapa.length(), mapa.width());

	for (unsigned i = 0; i < mapa.length(); i++)
	{
		for (unsigned j = 0; j < mapa.width(); j++)
		{
			if (checkNeighboursDylatacja(mapa, i, j) == true)
			{
				help[i][j] = true;
			}
			else
				help[i][j] = false;
		}
	}

	for (unsigned i = 0; i < mapa.length(); i++)
	{
		for (unsigned j = 0; j < mapa.width(); j++)
		{
			mapa(i, j) = help[i][j];
		}
	}
}

void Zerowanie::przeksztalc(Bitmapa& mapa)
{
	for (unsigned i = 0; i < mapa.length(); i++)
	{
		for (unsigned j = 0; j < mapa.width(); j++)
		{
			mapa(i, j) = false;
		}
	}
}

void Usrednianie::przeksztalc(Bitmapa& mapa)
{
	bool** help = fun_create2DimArray(mapa.length(), mapa.width());

	for (unsigned i = 0; i < mapa.length(); i++)
	{
		for (unsigned j = 0; j < mapa.width(); j++)
		{
			help[i][j] = checkNeighboursUsrdenianie(mapa, i, j);
		}
	}

	for (unsigned i = 0; i < mapa.length(); i++)
	{
		for (unsigned j = 0; j < mapa.width(); j++)
		{
			mapa(i, j) = help[i][j];
		}
	}
}

void ZlozeniePrzeksztalcen::dodajPrzeksztalcenie(Przeksztalcenie* p)
{
	container.push_back(p);
}

void ZlozeniePrzeksztalcen::przeksztalc(Bitmapa& mapa)
{
	for (int i = 0; i < container.size(); i++)
	{
		container[i]->przeksztalc(mapa);		//przykład: inwersja -> przekszałć (aa)
	}
}

bool checkNeighboursErozja(Bitmapa& mapa, unsigned i, unsigned j)
{
	if (mapa(i, j) == false)
		return false;
	else
	{
		/*----------------Sprawdzenie narożników---------------------*/
		if (i == 0 && j == 0)
		{
			if (mapa(i, j + 1) == false || mapa(i + 1, j) == false)
				return false;
			else
				return true;
		}
		if (i == mapa.length() - 1 && j == 0)
		{
			if (mapa(i - 1, j) == false || mapa(i, j + 1) == false)
				return false;
			else
				return true;
		}
		if (i == mapa.length() - 1 && j == mapa.width() - 1)
		{
			if (mapa(i, j - 1) == false || mapa(i - 1, j) == false)
				return false;
			else
				return true;
		}
		if (i == 0 && j == mapa.width() - 1)
		{
			if (mapa(i + 1, j) == false || mapa(i, j - 1) == false)
				return false;
			else
				return true;
		}
		/*----------------------Sprawdzanie krawędzi----------------------*/
		if (i == 0)
		{
			if (mapa(i, j - 1) == false || mapa(i, j + 1) == false || mapa(i + 1, j) == false)
				return false;
			else
				return true;
		}

		if (i == mapa.length() - 1)
		{
			if (mapa(i, j - 1) == false || mapa(i, j + 1) == false || mapa(i - 1, j) == false)
				return false;
			else
				return true;
		}

		if (j == 0)
		{
			if (mapa(i - 1, j) == false || mapa(i + 1, j) == false || mapa(i, j + 1) == false)
				return false;
			else
				return true;
		}

		if (j == mapa.width() - 1)
		{
			if (mapa(i - 1, j) == false || mapa(i + 1, j) == false || mapa(i, j - 1) == false)
				return false;
			else
				return true;
		}
		/*-----------------Sprawdzanie reszty pozycji(bez wierzchołków i krawędzi)--------------*/

		if (mapa(i - 1, j) == false || mapa(i + 1, j) == false || mapa(i, j - 1) == false || mapa(i, j + 1) == false)
			return false;
	}

	return true; //przypadek gdy wszyscy sąsiedzi są ciemnoskórzy
}

bool checkNeighboursDylatacja(Bitmapa& mapa, unsigned i, unsigned j)
{
	if (mapa(i, j) == true)
		return true;
	else
	{
		/*----------------Sprawdzenie narożników---------------------*/
		if (i == 0 && j == 0)
		{
			if (mapa(i, j + 1) == true || mapa(i + 1, j) == true)
				return true;
			else
				return false;
		}
		if (i == mapa.length() - 1 && j == 0)
		{
			if (mapa(i - 1, j) == true || mapa(i, j + 1) == true)
				return true;
			else
				return false;
		}
		if (i == mapa.length() - 1 && j == mapa.width() - 1)
		{
			if (mapa(i, j - 1) == true || mapa(i - 1, j) == true)
				return true;
			else
				return false;
		}
		if (i == 0 && j == mapa.width() - 1)
		{
			if (mapa(i + 1, j) == true || mapa(i, j - 1) == true)
				return true;
			else
				return false;
		}
		/*----------------------Sprawdzanie krawędzi----------------------*/
		if (i == 0)
		{
			if (mapa(i, j - 1) == true || mapa(i, j + 1) == true || mapa(i + 1, j) == true)
				return true;
			else
				return false;
		}

		if (i == mapa.length() - 1)
		{
			if (mapa(i, j - 1) == true || mapa(i, j + 1) == true || mapa(i - 1, j) == true)
				return true;
			else
				return false;
		}

		if (j == 0)
		{
			if (mapa(i - 1, j) == true || mapa(i + 1, j) == true || mapa(i, j + 1) == true)
				return true;
			else
				return false;
		}

		if (j == mapa.width() - 1)
		{
			if (mapa(i - 1, j) == true || mapa(i + 1, j) == true || mapa(i, j - 1) == true)
				return true;
			else
				return false;
		}
		/*-----------------Sprawdzanie reszty pozycji(bez wierzchołków i krawędzi)--------------*/

		if (mapa(i - 1, j) == true || mapa(i + 1, j) == true || mapa(i, j - 1) == true || mapa(i, j + 1) == true)
			return true;
	}

	return false;
}

bool checkNeighboursUsrdenianie(Bitmapa& mapa, unsigned i, unsigned j)
{
	bool tmp;
	int counter = 0;

	if (mapa(i, j) == true)
		tmp = false;
	else
		tmp = true;

		/*-------Sprawdzenie narożników(nie mogą mieć więcej niż dwóch sąsiadów)---------*/
		if (i == 0 && j == 0)
		{
			return mapa(i, j);
		}
		if (i == mapa.length() - 1 && j == 0)
		{
			return mapa(i, j);
		}
		if (i == mapa.length() - 1 && j == mapa.width() - 1)
		{
			return mapa(i, j);
		}
		if (i == 0 && j == mapa.width() - 1)
		{
			return mapa(i, j);
		}
		/*----------------------Sprawdzanie krawędzi----------------------*/
		if (i == 0)
		{
			if (mapa(i, j - 1) == tmp && mapa(i, j + 1) == tmp && mapa(i + 1, j) == tmp)
				return tmp;
			else
				return !tmp;
		}

		if (i == mapa.length() - 1)
		{
			if (mapa(i, j - 1) == tmp && mapa(i, j + 1) == tmp && mapa(i - 1, j) == tmp)
				return tmp;
			else
				return !tmp;
		}

		if (j == 0)
		{
			if (mapa(i - 1, j) == tmp && mapa(i + 1, j) == tmp && mapa(i, j + 1) == tmp)
				return tmp;
			else
				return !tmp;
		}

		if (j == mapa.width() - 1)
		{
			if (mapa(i - 1, j) == tmp && mapa(i + 1, j) == tmp && mapa(i, j - 1) == tmp)
				return tmp;
			else
				return !tmp;
		}
		/*-----------------Sprawdzanie reszty pozycji(bez wierzchołków i krawędzi)--------------*/


		if (mapa(i - 1, j) == tmp)
			counter++;
		if (mapa(i + 1, j) == tmp)
			counter++;
		if (mapa(i, j - 1) == tmp)
			counter++;
		if (mapa(i, j + 1) == tmp)
			counter++;

		if (counter > 2)
			return tmp;
		else
			return !tmp;
}
