/*This program takes either an integer or a character expression input and prints whether or not it is a palindrome. 
Created by Geoff Gaugler for CS 501 stack project. */
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;

void numeric();
void characters();
string clean(string str);

int main()
{
	int value;
	int n;
	cout << "Is expression numeric? Enter 1 if so, 2 if not \n";
	cin >> value;
	if (value == 1)
		numeric();
	if (value == 2)
		characters();
	if (value != 1 && value != 2)
		cout << "Try again \n";
	return 0;
}

void numeric() //function executed if the user input is numeric
{
	//convert int input to string so we can loop over each character in the string
	int expression;
	cout << "Enter expression: \n";
	cin >> expression;
	std::string out_string;
	std::stringstream ss;
	ss << expression;
	//out_string = ss.str();
	//string newexp = out_string;
	string newexp = ss.str();
	const int length = newexp.size();
	//creating an array from the new string where each char is an element in the array
	char array1[999];
	for (int i = 0; i < length; i++)
		array1[i] = newexp[i];
	//using a stack, creating a second array where each element is a character of the string but in reverse
	std::stack<char> stack1;
	for (int i = 0; i < length; ++i) stack1.push(array1[i]);
	char array2[999];
	for (int i = 0; i < length; i++)
	{
		array2[i] = stack1.top();
		stack1.pop();
	}
	//checking to see if the corresponding elements of the arrays are the same
	bool same = true;
	for (int i = 0; i < length; i++)
	{
		if (array1[i] != array2[i])
			same = false;
	}
	if (same == true)
		cout << "Your expression is numeric and is a palindrome! \n";
	if (same == false)
	{
		cout << "Your expression is numeric and is not a palindrome. \n";
		cout << "An expression similar to yours that is a palindrome is: ";
		for (int i = 0; i < length; i++)
			cout << array1[i];
		for (int i = 0; i < length; i++)
			cout << array2[i];
	}
}
void characters() //function to be carried out when the input is one consisting of characters.
{
	//inputting expression and removing punctuation and spaces from it
	string expression;
	cout << "Enter expression: \n";
	cin.ignore();
	getline(cin, expression);
	expression = clean(expression);
	int length = expression.size();
	//creating an array from the expression where each element 
	//is a character of the cleaned expression.
	char array1[999];
	for (int i = 0; i < length; i++)
		array1[i] = expression[i];
	std::stack<char> stack1;
	for (int i = 0; i < length; ++i) stack1.push(array1[i]);
	//using a stack, creating a second array where each element
	//is a character of the cleaned expression but in reverse order
	char array2[999];
	for (int i = 0; i < length; i++)
	{
		array2[i] = stack1.top();
		stack1.pop();
	}
	//seeing if the corresponding elements of each array are equal.
	bool same = true;
	for (int i = 0; i < length; i++)
	{
		if (array1[i] != array2[i])
			same = false;
	}
	if (same == true)
		cout << "Your expression is not numeric and is a palindrome! \n";
	if (same == false)
	{
		cout << "Your expression is not numeric and is not a palindrome. \n";
		cout << "An expression similar to yours that is a palindrome is: ";
		for (int i = 0; i < length; i++)
			cout << array1[i];
		for (int i = 0; i < length; i++)
			cout << array2[i];
	}
}

string clean(string str) //removes spaces and punctuation from the user inputted expression, also makes it completely lowercase
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	for (int i = 0; i < str.size(); i++)
	{
		if (ispunct(str[i]))
			str.erase(i--, 1);
	}
	return str;
}
