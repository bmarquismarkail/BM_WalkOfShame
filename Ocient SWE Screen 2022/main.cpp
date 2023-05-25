#include <string>
#include <iostream>
#include <variant>
#include <stack>
#include <vector>

using namespace std;

using value = variant<int, string>; // represents a value

using token = variant<string, value, char>; // represents a parsed token

// Helper function to check if a character is a delimiter
bool isDelimiter(char c) {
    return (c == '(' || c == ')' || c == ',');
}

token consumeNextToken(string& s) {
    token r;
    size_t tokenLen = 1;
    if (s[0] == ')' || s[0] == '(' || s[0] == ',') {
        r = s[0];
    } else if (s[0] == '"') {
        size_t i = 1;
        for (; i < s.length(); ++i) {
            if (s[i] == '"')
                break;
        }
        r = value(s.substr(1, i - 1));
        tokenLen = i + 1;
    } else if (s[0] >= '0' && s[0] <= '9') {
        size_t i = 0;
        for (; i < s.length(); ++i) {
            if (s[i] < '0' || s[i] > '9')
                break;
        }
        r = value(std::stoi(s.substr(0, i)));
        tokenLen = i;
    } else {
        size_t i = 0;
        for (; i < s.length(); ++i) {
            if (s[i] == '(' || s[i] == ')' || s[i] == ',')
                break;
        }
        r = s.substr(0, i);
        tokenLen = i;
    }

    s.erase(0, tokenLen);

    return r;
}

// Tokenize the input expression
vector<token> tokenizeExpression(const string& expr) {
    vector<token> tokens;
    string tokenStr;
    for (char c : expr) {
        if (c == ' ') {
            continue; // Skip spaces
        } else if (isDelimiter(c)) {
            if (!tokenStr.empty()) {
                tokens.push_back(consumeNextToken(tokenStr));
            }
        } else {
            tokenStr += c;
        }
    }
    if (!tokenStr.empty()) {
        tokens.push_back(consumeNextToken(tokenStr));
    }
    return tokens;
}

value evaluateAdd(value left, value right) {
    if (holds_alternative<int>(left) && holds_alternative<int>(right)) {
        return get<int>(left) + get<int>(right);
    } else if (holds_alternative<string>(left) && holds_alternative<string>(right)) {
        return get<string>(left) + get<string>(right);
    } else {
        throw runtime_error("Invalid argument types for addition.");
    }
}

value evaluateExpression(const vector<token>& tokens) {
    stack<value> stack;
    for (const auto& token : tokens) {
        if (holds_alternative<value>(token)) {
            stack.push(get<value>(token));
        } else if (holds_alternative<string>(token)) {
            if (get<string>(token) == "add") {
                value right = stack.top();
                stack.pop();
                value left = stack.top();
                stack.pop();
                value result = evaluateAdd(left, right);
                stack.push(result); // Push the result back to the stack
            }
        }
    }
    return stack.top();
}

int main() {
    string expr;
    getline(cin, expr);

    vector<token> tokens = tokenizeExpression(expr);

    value result = evaluateExpression(tokens);

    if (holds_alternative<int>(result)) {
        cout << get<int>(result) << endl;
    } else if (holds_alternative<string>(result)) {
        cout << get<string>(result) << endl;
    }

    return 0;
}