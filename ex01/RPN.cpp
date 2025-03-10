#include "RPN.hpp"

static int calcul(int a, int b, char c){
	if (c == '*')
		return (a * b);
	else if (c == '+')
		return (a + b);
	else if (c == '/'){
		if (b == 0)
			throw std::runtime_error("Error");
		return (a / b);
	}
	else if (c == '-')
		return (a - b);
	return 0;
}
void rpn(std::string s){
	std::stack <int> stk;
	size_t i = 0;
	while(i < s.length() && s[i] == ' ')
		i++;
	if(!s[i])
		throw std::runtime_error("Error");
	if (!s.length() && !isdigit(s[0]) && s[0] != '*'
			&& s[0] != '+' && s[0] != '-' && s[0] != '/')
		throw std::runtime_error("Error");
	std::istringstream inp(s);
	std::string str;
	while(inp >> str){
		if(str.length() != 1)
			throw std::runtime_error("Error");
		if (!isdigit(str[0]) && str[0] != '*'
			&& str[0] != '+' && str[0] != '-' && str[0] != '/')
				throw std::runtime_error("Error");
		if (str[0] != '*' && str[0] != '+' && str[0] != '-' && str[0] != '/')
			stk.push(std::atoi(str.c_str()));
		else{
			if(stk.size() > 1){
				int top1 = stk.top();
				stk.pop();
				int top2 = stk.top();
				stk.pop();
				stk.push(calcul(top2, top1, str[0]));
			}
			else
				throw std::runtime_error("Error");
		}
	}
	if(stk.size() > 1)
		throw std::runtime_error("Error");
	std::cout << stk.top() << std::endl;
}