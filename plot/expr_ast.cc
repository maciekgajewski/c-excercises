#include <memory>
#include <iostream>

namespace expr_ast
{

enum TokenType
{
    TokenError,
    TokenEOF,
    TokenNumber,
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
    TokenType type = TokenError;

    Token() = default;
    Token(TokenType type): type(type) {}
};

class Tokenizer
{
public:
    virtual ~Tokenizer() = default;

    virtual Token current() = 0;
    virtual Token next() = 0;
};

enum NodeType
{
    Undefined, Number, OperatorPlus, OperatorMinus, OperatorMul, OperatorDiv,
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

    void match(TokenType);

    Node* expression();
    Node* expression_r();
    Node* term();
    Node* term_r();
    Node* factor();

private:
    Tokenizer& tokenizer;
};

Node* Parser::expression()
{
    std::cout << "expression" << std::endl;

    Node* left = term();
    Node* node = expression_r();

    if (node->type == Undefined)
        return left;
    else {
        node->set_left(left);
        return node;
    }
}

Node* Parser::expression_r()
{
    std::cout << "expression_r" << std::endl;

    //Token token = tokenizer.next();
    Token token = tokenizer.current();
    Node* node = new Node();

    if (token.type == TokenPlus)
    {
        node->type = OperatorPlus;
        node->set_right(factor());
    }
    else
    if (token.type == TokenMinus)
    {
        node->type = OperatorMinus;
        node->set_right(factor());
    }

    return node;
}

Node* Parser::term()
{
    std::cout << "term" << std::endl;

    Node* left = factor();

    Node* node = term_r();

    if (node->type == Undefined)
        return left;
    else
    {
        node->set_left(left);
        return node;
    }
}

Node* Parser::term_r()
{
    std::cout << "term_r" << std::endl;

    Token token = tokenizer.next();
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

    Token token = tokenizer.next();

    if (token.type == TokenNumber)
    {
        node->type = Number;
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
        match(TokenRP);
    }

    return node;
}

void Parser::match(TokenType token_type)
{
    tokenizer.next();
}

}
