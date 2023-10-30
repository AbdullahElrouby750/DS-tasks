
#include <iostream>
#include <cmath>
#include <stack>
#include <string>

//#include <muParser.h>

using namespace std;
//using namespace mu;

struct integrate {
private:
    double a = 0, b = 1, h = 0, n = 5, I = 0, sum = 0;
    string fun;
    string num;
    // Parser p;
public:

    void trapezoidal()
    {
        cout << "plz,enter your get_fun :: ";
        cin.clear();
        getline(cin, fun);    // 1 + x + e ^ x

        h = (b - a) / (n - 1);
        sum = get_fun(a) + get_fun(b);
        for (double i = a + h; i < b; i += h)
        {
            sum += 2 * get_fun(i);
        }
        I = (h / 2) * sum;
        std::cout << I << endl;
    }
private:

    bool is_operator(char ch)
    {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
    }
    int opperator_degree(char ch)
    {
        int weight = -1;
        switch (ch)
        {
        case '+':
        case '-':
            weight = 1;
        case '*':
        case '/':
            weight = 2;
        case '^':
            weight = 3;
        }
        return weight;
    }

    double is_constant(char ch)
    {
        if (ch == 'e')
            return 2.718281828;
        else
            return false;
    }

    bool x_value(char ch)
    {
        return (ch == 'x' || ch == 'X');
    }
    double get_fun(double v)
    {
        if (v == 0)
            return 0;
        int size = fun.length(), weight = -1, weight2;
        double result = 0, n2 = 0;
        char op;
        stack<char> s;
        for (int i = 0; i < size; i++)
        {
            if (is_constant(fun[i]))
            {
                if (result == 0)
                    result = is_constant(fun[i]);
                else
                    n2 = is_constant(fun[i]);
            }
            else if (x_value(fun[i]))
            {
                if (result == 0)
                    result = v;
                else
                    n2 = v;
            }
            else if (is_operator(fun[i]) || i==size-1)
            {
                weight2 = opperator_degree(fun[i]);
                if (weight2 > weight)
                {
                    s.push(fun[i]);
                    weight = weight2;
                }
                if(weight>weight2 || i==size-1)
                {
                    if (i == size - 1)
                    {
                        num += fun[i];
                        op = s.top();
                    }
                    if (result == 0)
                        result = stod(num);
                    else
                        n2 = stod(num);
                    num.clear();

                    switch (op)
                    {
                    case '+':
                        result += n2;
                        s.pop();
                    case'-':
                        result -= n2;
                        s.pop();
                    case'*':
                        result *= n2;
                        s.pop();
                    case'/':
                        result /= n2;
                        s.pop();
                    case '^':
                        result = pow(result, n2);
                        s.pop();
                    }

                }

            }

            else
            {
                num += fun[i];
            }

        }
        return result;
    }
};
int main()
{
    integrate ob;
    ob.trapezoidal();
}