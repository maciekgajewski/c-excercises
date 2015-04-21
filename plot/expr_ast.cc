#include <memory>
#include <iostream>

namespace expr_ast
{

enum TokenType
{
    TokenUnknown,
    TokenEOF,
    TokenDouble,
    TokenPlus,
    TokenMinus,
    TokenMul,
    TokenDiv,
    TokenLP,
    TokenRP,
};

class Token
{
public:
    TokenType type = TokenUnknown;

    double value = 0;

    Token() = default;
    Token(TokenType type): type(type) {}
    Token(TokenType type, double value): type(type), value(value) {}
};

class Tokenizer
{
public:
    virtual ~Tokenizer() = default;

    virtual Token next() = 0;
};

enum NodeType
{
    Undefined, Double, OperatorPlus, OperatorMinus, OperatorMul, OperatorDiv,
};


class Node
{
public:
    NodeType type = Undefined;

    double value = 0;

    Node() = default;
    Node(NodeType type): type(type) {}
    Node(NodeType type, double value): type(type), value(value) {}

    void set_left(Node* node)
    {
        left.reset(node);
    }

    Node* get_left()
    {
        return left.get();
    }

    void set_right(Node* node)
    {
        right.reset(node);
    }

    Node* get_right()
    {
        return right.get();
    }

private:
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};


class Parser
{
public:
    Parser(Tokenizer& tokenizer): tokenizer(tokenizer) {}

    void token_read();
    void token_match(TokenType);

    Node* expression();
    Node* expression_r();
    Node* term();
    Node* term_r();
    Node* factor();

private:
    Tokenizer& tokenizer;
    Token token;
};

void Parser::token_read()
{
    token = tokenizer.next();
}

void Parser::token_match(TokenType token_type)
{
    token_read();
}

Node* Parser::expression()
{
    std::cout << "expression" << std::endl;

    Node* left = term();
    Node* node = expression_r();

    while (node->type != Undefined)
    {
        node->set_left(left);
        left = node;
        node = expression_r();
    }

    return left;
}

Node* Parser::expression_r()
{
    std::cout << "expression_r" << std::endl;

    Node* node = new Node();

    if (token.type == TokenPlus)
    {
        node->type = OperatorPlus;
        node->set_right(term());
    }
    else
    if (token.type == TokenMinus)
    {
        node->type = OperatorMinus;
        node->set_right(term());
    }

    return node;
}

Node* Parser::term()
{
    std::cout << "term" << std::endl;

    Node* left = factor();
    Node* node = term_r();

    while (node->type != Undefined)
    {
        node->set_left(left);
        left = node;
        node = term_r();
    }

    return left;
}

Node* Parser::term_r()
{
    std::cout << "term_r" << std::endl;

    token_read();

    Node* node = new Node();

    if (token.type == TokenMul)
    {
        node->type = OperatorMul;
        node->set_right(factor());
    }
    else
    if (token.type == TokenDiv)
    {
        node->type = OperatorDiv;
        node->set_right(factor());
    }

    return node;
}

Node* Parser::factor()
{
    std::cout << "factor" << std::endl;

    Node* node = new Node();

    token_read();

    if (token.type == TokenDouble)
    {
        node->type = Double;
    }
    else
    if (token.type == TokenPlus)
        node = factor();
    else
    if (token.type == TokenMinus)
        node = factor(); // TODO: Unary minus
    else
    if (token.type == TokenLP)
    {
        node = expression();
        token_match(TokenRP);
    }

    return node;
}

}
