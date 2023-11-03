#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <cctype>

#define null NULL

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

class exprssion {
	stack <double> operands;
	stack <char> operators;
	stack<char> temp_operator;
	string Fx = "", snum = "";
	int it = 0, weight1 = -1, temp_weight = -1, weight2 = 0;
	char ch = null;
	double value = null, left = null, right = null, num = null, result = null;
public:
	double F_x(string fx, double val)
	{
		Fx = fx;
		value = val;

		evaluate();

		return result;
	}

private:

	//check the cha functions
	bool is_operator(char& ch)
	{
		return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')');
	}

	bool is_e(char& ch)
	{
		if (ch == 'e')
			return true;
		else
			return false;
	}

	bool is_x(char& ch)
	{
		if (ch == 'x' || ch == 'X')
			return true;
		else
			return false;
	}

	//calculate is_trigonometric
	void is_trigonometric()
	{
		string tri = "";
		while (Fx[it] != '(') {
			tri += Fx[it++];
		}
		it++; // Move past '('

		// Parse the angle value
		string temp_expr = "";
		int openParenCount = 0;

		while (Fx[it] != ')' || openParenCount > 0) {
			if (Fx[it] == '(') {
				openParenCount++;
			}
			else if (Fx[it] == ')') {
				openParenCount--;
			}
			temp_expr += Fx[it++];
		}

		int temp_it = it;
		double temp_result = result;

		// Evaluate the angle value
		double temp_value = F_x(temp_expr, value);

		result = temp_result;

		if (tri == "sin") {
			operands.push(sin(temp_value * (M_PI / 180.0))); // Convert degrees to radians
			result += operands.top();
		}
		else if (tri == "cos") {
			operands.push(cos(temp_value * (M_PI / 180.0))); // Convert degrees to radians
			result += operands.top();
		}
		else if (tri == "tan") {
			operands.push(tan(temp_value * (M_PI / 180.0))); // Convert degrees to radians
			result += operands.top();
		}

		it= ++temp_it; // Move past ')'
	}

	//set operator degree
	int set_weight(char& ch)
	{
		int weight = 0;
		switch (ch)
		{
		case '+':
		case '=':
			weight = 1;
			break;
		case '*':
		case '/':
			weight = 2;
			break;
		case '^':
			weight = 3;
			break;
		}
		return weight;
	}

	// arthimatical opeerators functions
	void add()
	{
		right = operands.top();
		operands.pop();

		left = operands.top();
		operands.pop();

		result = left + right;
		operands.push(result);
	}

	void subtract()
	{
		right = operands.top();
		operands.pop();

		left = operands.top();
		operands.pop();

		result = left - right;
		operands.push(result);
	}

	void multiply()
	{
		right = operands.top();
		operands.pop();

		left = operands.top();
		operands.pop();

		result = left * right;
		operands.push(result);
	}

	void divide()
	{
		right = operands.top();
		operands.pop();

		left = operands.top();
		operands.pop();
		if (right == 0)
		{
			cout << "Error! can't divide over a 0\n";
			return;
		}

		result = left / right;
		operands.push(result);
	}

	void power()
	{
		right = operands.top();
		operands.pop();

		left = operands.top();
		operands.pop();

		result = pow(left,right);
		operands.push(result);
	}


	void dedect_the_operation()
	{
		switch (ch)
		{
		case '+':
			add();
			break;
		case '-':
			subtract();
			break;
		case '*':
			multiply();
			break;
		case '/':
			divide();
			break;
		case '^':
			power();
			break;
		}
	}

	//calulate the results
	void calculate()
	{ 
		if(Fx[it]!='(')
			weight2 = set_weight(Fx[it]);

		if (Fx[it] == ')')
		{
			while (temp_operator.top() != '(')
			{
				ch = temp_operator.top();
				temp_operator.pop();

				temp_weight = set_weight(temp_operator.top());

				dedect_the_operation();
			}
			temp_operator.pop();
		}

		else if (!temp_operator.empty())
		{
			if (weight2 > temp_weight)
			{
				temp_operator.push(Fx[it]);
				temp_weight = weight2;
				return;
			}
			while (temp_weight > weight2)
			{
				if (!temp_operator.top()!='(')
				{
					ch = temp_operator.top();
					temp_operator.pop();

					temp_weight = set_weight(temp_operator.top());

					dedect_the_operation();
				}
				else
					break;
			}
			temp_operator.push(Fx[it]);
		}

		else if (Fx[it] == '(' || weight2 > weight1)
		{
			if (Fx[it] == '(')
				temp_operator.push(Fx[it]);
			else
			{
				operators.push(Fx[it]);
				weight1 = weight2;
			}
		}
		else if(weight1 > weight2)
		{
			while (weight1 > weight2)
			{
				if (!operators.empty())
				{
					ch = operators.top();
					operators.pop();
					if (!operators.empty())
						weight1 = set_weight(operators.top());

					dedect_the_operation();
				}
				else
					break;
			}
			if (is_operator(Fx[it]))
				operators.push(Fx[it]);
		}
	}
	
	//dedect the char
	void evaluate()
	{
		int size = Fx.length();
		for (it = 0; it < size; it++)
		{
			if (Fx[it] == ' ')
				continue;
			if (is_operator(Fx[it]))
			{
				if(!snum.empty())
				{
					operands.push(stod(snum));
					snum.clear();
				}
				calculate();
			}

			else if (is_e(Fx[it]))
				operands.push(2.7181);

			else if (is_x(Fx[it]))
				operands.push(value);

			else if (Fx[it] == 's' || Fx[it] == 'c' || Fx[it] == 't')
			{
				is_trigonometric();
				snum.clear();
			}

			else
				snum += Fx[it];
		}
		while (!operators.empty() || !snum.empty())
		{
			if (!snum.empty())
			{
				operands.push(stod(snum));
				snum.clear();
			}
			if (result == 0 && operands.size() == 1)
			{
				result = operands.top();
				operands.pop();
				break;
			}
			else
				calculate();
		}
	}

};

int main()
{
	exprssion ex;
	string s = "sin(30)";
	double x = 2;
	//cout << sin(1) << endl;
	cout << "result = " << ex.F_x(s, x) << "\n";
}