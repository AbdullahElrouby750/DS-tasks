
#include <iostream>
#include <cmath>

using namespace std;

struct Data {
private: //var
	int n = 0, choose = 0;
	double x[30], y[30];
	double sum_x = 0, sum_y = 0, sum_xx = 0, sum_xy = 0;
long double a = 0, b = 0;
public:

	void push()
	{
		char answer = 'y';
		cout << "Plz, enter your data here\n";

		while (answer == 'y' || answer == 'Y')
		{
			cout << "enter x value :: ";
			cin >> x[n];

			cout << "enter y value :: ";
			cin >> y[n];

			n++;

			cout << "do you want to continue? :: y/n ";
			cin >> answer;
		}
		calculate_the_sum();
		print_data();
		equ_form();
		solve();
	}


private: //fun
	void print_data()
	{
		if (n == 0)
			return;
		cout << "		x			y\n";
		for (int i = 0; i < n; i++)
		{
			cout << "		" << x[i] << "			" << y[i] << endl;
		}
	}

	void calculate_the_sum()
	{
		for (size_t i = 0; i < n; i++)
		{
			sum_x += x[i];
			sum_y += y[i];
			sum_xx += x[i] * x[i];
			sum_xy += x[i] * y[i];
		}
	}

	void equ1()
	{
		cout << " Solve for 'a' & 'b' in 'y = a + bx'\n";

		b = (sum_xy - (sum_x * sum_y) / n) / (sum_xx - (sum_x * sum_x) / n);

		a = (sum_y - sum_x * b) / n;

		cout << " a = " << a << "		b = " << b << endl;
		cout << "the final form of the equ :: y = " << a << " + " << b << " x\n";
	}

	void equ2()
	{
		double sum_xxx = 0, sum_xxxx = 0, sum_xxy = 0,c=0;

		for (int i = 0; i < n; i++)
		{
			sum_xxx += x[i] * x[i] * x[i];
			sum_xxxx += x[i] * x[i] * x[i] * x[i];
			sum_xxy += x[i] * x[i] * y[i];
		}

		cout << " Solve for 'a' & 'b' in 'y = a + bx'\n";

		c = (sum_xxy * n - sum_xx * sum_y + ((sum_xxx * sum_x * sum_y * n - sum_xx * sum_x * sum_x * sum_y) / (sum_xx * n - sum_x * sum_x)) - ((sum_xxx * sum_xy * n - sum_xx * sum_x * sum_xy) / (sum_xx - (sum_x * sum_x) / n))) / (sum_xxxx * n - sum_xx * sum_xx + ((sum_xxx * sum_xx * sum_x - sum_xxx * sum_xxx * n) / (sum_xx - (sum_x * sum_x) / n)) + ((sum_xxx * sum_xx * sum_x * n - sum_x * sum_x * sum_xx * sum_xx) / (sum_xx * n - sum_x * sum_x)));

		b = (sum_xy - sum_xxx * c) / (sum_xx - (sum_x * sum_x) / n) + (sum_x * sum_xx * c - sum_x * sum_y) / (sum_xx * n - sum_x * sum_x);

		a = (sum_y - sum_x * b - sum_xx * c) / n;
		cout << " a = " << a << "		b = " << b <<"		c = "<< c << endl;
		cout << "the final form of the equ :: y = " << a << " + " << b << " x + "<<c<<" x^2\n";
	}

	void equ3()
	{
		double sum_Y = 0,sum_xY=0,A=0,c=0;
		
		cout << " Solve for 'a' & 'b' in 'y = a * e^(bx) + c'\n";
		
		cout << "enter the value of c :: ";
		cin >> c;

		for (int i = 0; i < n; i++)
		{
			sum_Y += log(y[i] - c);
			sum_xY += (log(y[i] - c) * x[i]);
		}

		b = (sum_xY - (sum_x * sum_Y) / n) / (sum_xx - (sum_x * sum_x) / n);

		A = (sum_Y - sum_x * b) / n;

		a = exp(A);

		cout << " a = " << a << "		b = " << b << endl;
		cout << "the final form of the equ :: y = " << a << " * e^(" << b << " x) + " << c << endl;
	}

	void equ4()
	{
		double sum_X = 0, sum_Xy = 0,sum_XX=0;

		cout << " Solve for 'a' & 'b' in 'y = a + b/x'\n";

		for (int i = 0; i < n; i++)
		{
			sum_X += 1 / x[i];
			sum_XX += (1 / x[i]) * (1 / x[i]);
			sum_Xy += (1 / x[i]) * y[i];
		}

		b = (sum_Xy - (sum_X * sum_y) / n) / (sum_XX - (sum_X * sum_X) / n);

		a = (sum_y - sum_X * b) / n;

		cout << " a = " << a << "		b = " << b << endl;
		cout << "the final form of the equ :: y = " << a << " + " << b << "/x\n";
	}

	void equ5()
	{
		double sum_Y = 0, sum_xY = 0;
		long double A = 0, B = 0;

		cout << " Solve for 'a' & 'b' in 'y =  b / (a + x)'\n";

		for (int i = 0; i < n; i++)
		{
			sum_Y += 1 / y[i];
			sum_xY += x[i] * (1 / y[i]);
		}

		b = (sum_xY - (sum_x * sum_Y) / n) / (sum_xx - (sum_x * sum_x) / n);
		
		a = (sum_Y - sum_x * b) / n;

		b = 1 / B;
		a = A * b;

		cout << " a = " << a << "		b = " << b << endl;
		cout << "the final form of the equ :: y = " << b << " / (" << a << " + x)\n";
	}

	void equ6()
	{
		double sum_Y = 0, sum_xY = 0;

		cout << " Solve for 'a' & 'b' in 'y = ax + bx^2'\n";

		for (int i = 0; i < n; i++)
		{
			sum_Y += y[i] / x[i];
			sum_xY += x[i] * (y[i] / x[i]);
		}


		b = (sum_xY - (sum_x * sum_Y) / n) / (sum_xx - (sum_x * sum_x) / n);

		a = (sum_Y - sum_x * b) / n;

		cout << " a = " << a << "		b = " << b << endl;
		cout << "the final form of the equ :: y = " << a << " x + " << b << " x^2\n";

	}

	void equ7()
	{
		double sum_X = 0, sum_Y = 0, sum_XX = 0, sum_XY = 0, A = 0, c = 0;

		cout << " Solve for 'a' & 'b' in 'y = a * x^b + c'\n";

		cout << "enter the value of c :: ";
		cin >> c;

		for (int i = 0; i < n; i++)
		{
			sum_X += log(x[i]);
			sum_Y += log(y[i] - c);
			sum_XX += log(x[i]) * log(x[i]);
			sum_XY += log(x[i]) * log(y[i] - c);
		}


		b = (sum_XY - (sum_X * sum_Y) / n) / (sum_XX - (sum_X * sum_X) / n);

		A = (sum_Y - sum_X * b) / n;

		a = exp(A);

		cout << " a = " << a << "		b = " << b << endl;
		cout << "the final form of the equ :: y = " << a << " * " << " x^" << b << " + " << c << endl;;
	}

	void solve()// y=a+xb	//for a and b
	{
		switch (choose)
		{
		case 1:
			equ1();

			break;

		case 2:
			equ2();
			
			break;

		case 3:
			equ3();
			break;

		case 4:
			equ4();
			break;

		case 5:
			equ5();
			break;

		case 6:
			equ6();
			break;

		case 7:
			equ7();
			break;
		}
	}

	void equ_form()
	{
		cout << "Plz, choose your equ form from the list below.\n";
		cout << "1) y = a + xb.\n2) y = a + bx + cx^2.\n3) y = a * e^(bx) + c. NOTE 'c' is a given constant\n4) y = a + b/x.\n5) y = b / (a + x).\n6) y = ax + bx^2.\n7) y = a * x^b + c. NOTE 'c' is a given constant\n >> ";
		cin >> choose;
	}
};

int main()
{
	Data data;
	data.push();
	cin.get();
	
}

