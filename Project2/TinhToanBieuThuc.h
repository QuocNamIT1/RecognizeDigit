#pragma once
#include<iostream>
using namespace std;
class TinhToanBieuThuc
{
	string  chuoibieuthuc;
public:
	TinhToanBieuThuc(string);
	bool check(string s)
	{
		for (int i = 0; i<s.size(); i++)
			if (s[i] == '(' || s[i] == ')')
				return true;
		return false;
	}
	string itoa(float x)
	{
		string s;
		int d = 0, dem = 0, a;
		if (x == 0) s.insert(0, "0");
		if (x<0)
		{
			d = 1;
			x = -x;
		}
		while (float(x) - long(x) != 0)
		{
			dem++;
			x *= 10;
		}
		long z = long(x);
		for (int i = 0; i<dem; i++)
		{
			a = z % 10;
			z /= 10;
			switch (a)
			{
			case 0:s.insert(0, "0"); break;
			case 1:s.insert(0, "1"); break;
			case 2:s.insert(0, "2"); break;
			case 3:s.insert(0, "3"); break;
			case 4:s.insert(0, "4"); break;
			case 5:s.insert(0, "5"); break;
			case 6:s.insert(0, "6"); break;
			case 7:s.insert(0, "7"); break;
			case 8:s.insert(0, "8"); break;
			case 9:s.insert(0, "9"); break;
			}
		}
		if (dem>0)s.insert(0, ".");
		if (z == 0) s.insert(0, "0");
		while (z>0)
		{
			a = z % 10;
			z /= 10;
			switch (a)
			{
			case 0:s.insert(0, "0"); break;
			case 1:s.insert(0, "1"); break;
			case 2:s.insert(0, "2"); break;
			case 3:s.insert(0, "3"); break;
			case 4:s.insert(0, "4"); break;
			case 5:s.insert(0, "5"); break;
			case 6:s.insert(0, "6"); break;
			case 7:s.insert(0, "7"); break;
			case 8:s.insert(0, "8"); break;
			case 9:s.insert(0, "9"); break;
			}
		}
		if (d == 1) s.insert(0, "-");
		else s.insert(0, "+");
		return s;
	}
	float lay1(string s)
	{
		long d = 1;
		float x = 0;
		for (int i = s.size() - 1; i >= 0; i--)
		{
			if (s[i] == '-' || s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')')
			{
				if (s[i] == '-') x = -x;
				break;
			}
			else if (s[i] == '.')
			{
				x /= d;
				d = 1;
			}
			else
			{
				switch (s[i])
				{
				case '0':break;
				case '1':x += d; break;
				case '2':x += 2 * d; break;
				case '3':x += 3 * d; break;
				case '4':x += 4 * d; break;
				case '5':x += 5 * d; break;
				case '6':x += 6 * d; break;
				case '7':x += 7 * d; break;
				case '8':x += 8 * d; break;
				case '9':x += 9 * d; break;
				}
				d *= 10;
			}
		}
		return x;
	}
	float lay2(string s)
	{
		long j = 0, k = 0, i;
		float d;
		float x = 0;
		if (s[0] == '+' || s[0] == '-') j = 1;
		for (i = j; i<s.size(); i++)
		{
			if (s[i] >= '0' && s[i] <= '9')
			{
				switch (s[i])
				{
				case '0':x = x * 10 + 0; break;
				case '1':x = x * 10 + 1; break;
				case '2':x = x * 10 + 2; break;
				case '3':x = x * 10 + 3; break;
				case '4':x = x * 10 + 4; break;
				case '5':x = x * 10 + 5; break;
				case '6':x = x * 10 + 6; break;
				case '7':x = x * 10 + 7; break;
				case '8':x = x * 10 + 8; break;
				case '9':x = x * 10 + 9; break;
				}
			}
			else break;
		}
		if (i<s.size() && s[i] == '.')
		{
			d = 10;
			for (j = i + 1; j<s.size(); j++)
			{
				if (s[j] >= '0' && s[j] <= '9')
				{
					switch (s[j])
					{
					case '0':x += 0 / d; break;
					case '1':x += 1 / d; break;
					case '2':x += 2 / d; break;
					case '3':x += 3 / d; break;
					case '4':x += 4 / d; break;
					case '5':x += 5 / d; break;
					case '6':x += 6 / d; break;
					case '7':x += 7 / d; break;
					case '8':x += 8 / d; break;
					case '9':x += 9 / d; break;
					}
					d *= 10;
				}
				else break;
			}
		}
		if (s[0] == '-') x = -x;
		return x;
	}
	void xuly(string &s)

	{

		if (s[s.size() - 1] == '+' || s[s.size() - 1] == '-')

		{

			s.push_back('0');

		}

		if (s[s.size() - 1] == '*' || s[s.size() - 1] == '/')

		{

			bool p = false;

			for (int i = s.size() - 2; i >= 0; i--)

				if (s[i] == '+' || s[i] == '-')

				{

					p = true;

					i++;

					s.replace(i, s.size() - i, "0");

				}

			if (p == false)

			{

				s.erase(0, s.size());

				s.insert(0, "0");

			}

		}

		for (int i = 0; i<s.size() - 1; i++)

			if (s[i] == '+' && s[i + 1] == '+')

			{

				s.erase(i, 1);

			}

			else if (s[i] == '+' && s[i + 1] == '-')

			{

				s.erase(i, 1);

			}

			else if (s[i] == '-' && s[i + 1] == '+')

			{

				s.erase(i + 1, 1);

			}

			else if (s[i] == '-' && s[i + 1] == '-')

			{

				s.erase(i, 2);

				s.insert(i, "+");

			}

	}

	float tinh(string s)

	{

		xuly(s);

		int p1, p2;

		string a, c;

		float x, y, t = 0, p;

		while (check(s))

		{

			p2 = s.find(")");

			if (p2 >= 0)

			{

				xuly(s);

				p1 = s.rfind("(", p2);

				a = s.substr(p1 + 1, p2 - p1 - 1);

				p = tinh(a);

				c = itoa(p);

				s.replace(p1, p2 - p1 + 1, c);

				xuly(s);

			}

		}

	loop:;

		for (p = 0; p<s.size(); p++)

			if (s[p] == '*' || s[p] == '/') break;

		if (p != s.size())

		{

			xuly(s);

			a = s.substr(0, p);

			c = s.substr(p + 1, s.size() - p - 1);

			x = lay1(a);

			y = lay2(c);

			if (s[p] == '*') t = x*y;

			else t = x / y;

			for (p1 = p - 1; p1 >= 0; p1--)

				if (s[p1] == '+' || s[p1] == '-' || s[p1] == '*' || s[p1] == '/' || s[p1] == '(' || s[p1] == ')') break;

			if (p1 == -1) p1++;

			else if (s[p1] == '*' || s[p1] == '/') p1++;

			for (p2 = p + 2; p2<s.size(); p2++)

				if (s[p2] == '+' || s[p2] == '-' || s[p2] == '*' || s[p2] == '/' || s[p2] == '(' || s[p2] == ')') break;

			p2--;

			a = itoa(t);

			s.replace(p1, p2 - p1 + 1, a);

			xuly(s);

			goto loop;

		}

		//dau +-

		else

		{

			int k;

			do{

				k = 0;

				for (p = 1; p<s.size(); p++)

					if (s[p] == '+' || s[p] == '-') break;

				if (p<s.size())

				{

					xuly(s);

					a = s.substr(0, p);

					c = s.substr(p + 1, s.size() - p - 1);

					x = lay1(a);

					y = lay2(c);

					if (s[p] == '+') t = x + y;

					else t = x - y;

					a = itoa(t);

					for (p2 = p + 1; p2<s.size(); p2++)

						if (s[p2] == '+' || s[p2] == '-') break;

					p2--;

					s.replace(0, p2 + 1, a);

					xuly(s);

					k = 1;

				}

			} while (k);

		}

		t = lay1(s);

		return t;

	}
	float tinhbieuthuc()
	{
		return tinh(chuoibieuthuc);
	}
	~TinhToanBieuThuc();
};

