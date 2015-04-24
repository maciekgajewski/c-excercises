#include <memory>

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
    Undefined, Double, OperatorPlus, OperatorMinus, OperatorMul, OperatorDiv, UnaryPlus, UnaryMinus
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

    // TODO: Implement move

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
    Node* node = new Node(); // TODO: Use smart pointers

    token_read();

    if (token.type == TokenDouble)
    {
        node->type = Double;
        node->value = token.value;
    }
    else
    if (token.type == TokenPlus)
    {
        node->type = UnaryPlus;
        node->set_left(factor());
    }
    else
    if (token.type == TokenMinus)
    {
        node->type = UnaryMinus;
        node->set_left(factor());
    }
    else
    if (token.type == TokenLP)
    {
        node = expression();
        token_match(TokenRP);
    }

    return node;
}

void print(expr_ast::Node* node)
{
    std::cout << node->type << " " << node->value << std::endl;
    if (node->get_left())
        print(node->get_left());
    if (node->get_right())
        print(node->get_right());
}

double eval(Node* node)
{
    if (node->type == Double)
        return node->value;

    if (node->type == OperatorPlus)
    {
        return eval(node->get_left()) + eval(node->get_right());
    }
    else if (node->type == OperatorMinus)
    {
        return eval(node->get_left()) - eval(node->get_right());
    }
    else if (node->type == OperatorMul)
    {
        return eval(node->get_left()) * eval(node->get_right());
    }
    else if (node->type == OperatorDiv)
    {
        return eval(node->get_left()) / eval(node->get_right());
    }

    // TODO: Raise an exception
    return 0;
}

}
