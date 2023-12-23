#include <iostream>
#include <string>
#include <stack>
using namespace std;
#define null nullptr
#define size 15
struct Node
{
    string data;
    Node* left, * right;
    Node(string item)
    {
        data = item;
        left = right = null;
    }
};

class project
{
private:
    bool Operator(char item)
    {
        return item == '+' || item == '-' || item == '*' || item == '/' || item == '^';
    }

    bool Operand(char item)
    {
        return isdigit(item);
    }

    int Priority_operation(char ch) {
        int weight = 0;
        if(ch == '-' || ch == '+')
            weight = 1;
        if(ch == '*' || ch == '/')
            weight = 2;
        if(ch == '^')
            weight = 3;
        return weight;
    }

public:
    Node* root;
    project()
    {
        Node* root = null;
    }

    Node* Tree(string exp) // creat the tree (5+7)(9+2)
    {
        stack<Node*> s;
        stack<char> sc;

        for (int i = 0; i < exp.length(); ++i) // for ->input all char
        {
            char c = exp[i];

            if (c == ' ')
            {
                continue;
            }
            else if (Operand(c)) // check (5,7,9,2)
            {
                string nodes(1, c);
                while (i + 1 < exp.length() && isdigit(exp[i + 1]))
                {
                    nodes += exp[i + 1];
                    i++;
                }
                s.push(new Node(nodes));
            }
            else if (c == '(')
            {
                sc.push(c);
            }
            else if (c == ')')
            {
                while (!sc.empty() && sc.top() != '(')
                {
                    Node* right = s.top();
                    s.pop();
                    Node* left = s.top();
                    s.pop();

                    Node* newNode = new Node(string(1, sc.top()));
                    newNode->left = left;
                    newNode->right = right;
                    s.push(newNode);

                    sc.pop();
                }
                sc.pop(); // Pop the '('
            }
            else if (Operator(c))
            {
                while (!sc.empty() && Priority_operation(sc.top()) >= Priority_operation(c)) // check in opreator (+,-,*,/)
                {
                    Node* right = s.top();
                    s.pop();
                    Node* left = s.top();
                    s.pop();

                    Node* newNode = new Node(string(1, sc.top()));
                    newNode->left = left;
                    newNode->right = right;
                    s.push(newNode);

                    sc.pop();
                }
                sc.push(c);
            }
            else
            {
                cout << "\nERROR! invalid character (" << c << ") spotted!\n";
                return null;
            }
        }

        while (!sc.empty()) // fianl input
        {
            Node* right = s.top();
            s.pop();
            Node* left = s.top();
            s.pop();

            Node* newNode = new Node(string(1, sc.top()));
            newNode->left = left;
            newNode->right = right;
            s.push(newNode);

            sc.pop();
        }

        return s.top();
    }

    int result(Node* root)
    {
        if (root == null)
        {
            return 0;
        }

        if (root->left == null && root->right == null)
        {
            return stoi(root->data);
        }

        int left = result(root->left);
        int right = result(root->right);

        if (root->data == "+")
        {
            return left + right;
        }
        else if (root->data == "-")
        {
            return left - right;
        }
        else if (root->data == "*")
        {
            return left * right;
        }
        else if (root->data == "/")
        {
            return left / right;
        }

        return 0;
    }

    void in_order(Node* root)
    {
        if (root == null)
            return;
        else
        {
            in_order(root->left);
            cout << root->data << " ";
            in_order(root->right);
        }
    }

    void Post_order(Node* root)
    {
        if (root)
        {
            Post_order(root->right);
            Post_order(root->left);
            cout << root->data << " ";
        }
    }

    void Pre_order(Node* root)
    {
        if (root)
        {
            cout << root->data << " ";
            Pre_order(root->left);
            Pre_order(root->right);
        }
    }

    string prefix(string expr) {
        stack<char>equa;
        string result = "";

        for (int i = expr.length() - 1; i >= 0; --i) {
            if (expr[i] == ' ') {
                continue;
            }
            else if (isdigit(expr[i]) || isalpha(expr[i])) {
                result += expr[i];

            }
            else if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[') {
                equa.push(expr[i]);
            }
            else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']') {
                //if was not frist of stack use while loop
                while (equa.top() != ')' || equa.top() != '}' || equa.top() != ']') {
                    result += equa.top();
                    equa.pop();
                }
                equa.pop();
            }
            else {
                while (!equa.empty() && Priority_operation(expr[i]) >= Priority_operation(equa.top())) {
                    result += equa.top();
                    equa.pop();
                }
                equa.push(expr[i]);

            }
        }
        while (!equa.empty()) {
            result += equa.top();
            equa.pop();
        }
        reverse(result.begin(), result.end());
        return result;

    }

    string Postfix(string expr) {
        stack<char> equa;
        string result = "";

        for (int i = 0; i < expr.length(); ++i) {
            if (expr[i] == ' ') {
                continue;
            }
            else if (isdigit(expr[i]) || isalpha(expr[i])) {
                result += expr[i];
            }
            else if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[') {
                equa.push(expr[i]);
            }
            else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']') {
                while (!equa.empty() && equa.top() != '(' && equa.top() != '{' && equa.top() != '[') {
                    result += equa.top();
                    equa.pop();
                }
                equa.pop();
            }
            else {
                while (!equa.empty() && Priority_operation(expr[i]) <= Priority_operation(equa.top())) {
                    result += equa.top();
                    equa.pop();
                }
                equa.push(expr[i]);
            }
        }

        while (!equa.empty()) {
            result += equa.top();
            equa.pop();
        }

        return result;
    }

    bool checkPare(const string& opject)
    {
        stack<char> charStack;
        for (char c : opject) {
            if (c == '(' || c == '{' || c == '[') {
                charStack.push(c);
            }
            else if (c == ')' || c == '}' || c == ']') {
                if (charStack.empty()) {
                    return false;
                }

                char _top = charStack.top();
                charStack.pop();
                if ((c == ')' && _top != '(') || (c == '}' && _top != '{') || (c == ']' && _top != '[')) {
                    return false;
                }
            }
        }
        return charStack.empty();
    }


};

int main()
{
    project pro;
    cout << "Plz, enter the expression :: ";
    string expression;

    getline(cin, expression);
    
    if (pro.checkPare(expression))
    {
        cout << "\nTo post-fix -> " << pro.Postfix(expression) << endl;

        cout << "\nTo pre-fix -> " << pro.prefix(expression) << endl;

        Node* root = pro.Tree(expression);

        if (root == null)
        {
            return -1;
        }

        cout << "\nThe tree in pre-order ->";
        pro.Pre_order(root);

        cout << "\n\nThe tree post-order ->";
        pro.Post_order(root);

        cout << "\n\nThe tree in in-order -> ";
        pro.in_order(root);

        cout << "\n\n" << expression << " = " << pro.result(root);
    }
   
    else
    {
        cout << "\n\nERRRO! check the parentheses\n";
        return -1;
    }
}
