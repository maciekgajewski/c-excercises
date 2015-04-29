#include <memory>
#include <exception>

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
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node() = default;
    Node(NodeType type): type(type) {}
    Node(NodeType type, double value): type(type), value(value) {}
};

class Parser
{
public:
    Parser(Tokenizer& tokenizer): tokenizer(tokenizer) {}

    void token_read();
    void token_match(TokenType);

    std::unique_ptr<Node> expression();
    std::unique_ptr<Node> expression_r();
    std::unique_ptr<Node> term();
    std::unique_ptr<Node> term_r();
    std::unique_ptr<Node> factor();

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

std::unique_ptr<Node> Parser::expression()
{
    std::unique_ptr<Node> left = term();
    std::unique_ptr<Node> node = expression_r();

    while (node->type != Undefined)
    {
        node->left = std::move(left);
        left = std::move(node);
        node = expression_r();
    }

    return left;
}

std::unique_ptr<Node> Parser::expression_r()
{
    std::unique_ptr<Node> node(new Node());

    if (token.type == TokenPlus)
    {
        node->type = OperatorPlus;
        node->right = term();
    }
    else
    if (token.type == TokenMinus)
    {
        node->type = OperatorMinus;
        node->right = term();
    }

    return node;
}

std::unique_ptr<Node> Parser::term()
{
    std::unique_ptr<Node> left = factor();
    std::unique_ptr<Node> node = term_r();

    while (node->type != Undefined)
    {
        node->left = std::move(left);
        left = std::move(node);
        node = term_r();
    }

    return left;
}

std::unique_ptr<Node> Parser::term_r()
{
    token_read();

    std::unique_ptr<Node> node(new Node());

    if (token.type == TokenMul)
    {
        node->type = OperatorMul;
        node->right = factor();
    }
    else
    if (token.type == TokenDiv)
    {
        node->type = OperatorDiv;
        node->right = factor();
    }

    return node;
}

std::unique_ptr<Node> Parser::factor()
{
    std::unique_ptr<Node> node(new Node());

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
        node->left = factor();
    }
    else
    if (token.type == TokenMinus)
    {
        node->type = UnaryMinus;
        node->left = factor();
    }
    else
    if (token.type == TokenLP)
    {
        node = expression();
        token_match(TokenRP);
    }

    return node;
}

void print(const std::unique_ptr<Node>& node)
{
    std::cout << node->type << " " << node->value << std::endl;
    if (node->left)
        print(node->left);
    if (node->right)
        print(node->right);
}

struct EvalError : public std::exception
{
  const char * what () const throw ()
  {
    return "Evaluation error";
  }
};

double eval(const std::unique_ptr<Node>& node)
{
    if (node->type == Double)
        return node->value;

    if (node->type == OperatorPlus)
    {
        return eval(node->left) + eval(node->right);
    }
    else if (node->type == OperatorMinus)
    {
        return eval(node->left) - eval(node->right);
    }
    else if (node->type == OperatorMul)
    {
        return eval(node->left) * eval(node->right);
    }
    else if (node->type == OperatorDiv)
    {
        return eval(node->left) / eval(node->right);
    }

    throw EvalError();
}

}
