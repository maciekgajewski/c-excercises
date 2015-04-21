#include "plot.h"
#include "engine_csv.cc"
#include "expr_spirit.cc"
#include "expr_ast.cc"

#include <cassert>
#include <iostream>
#include <vector>


void test_parse()
{
	// "x * x"
}


void test_evaluate()
{

}

void test_spirit()
{
	boost::spirit::utree ut;

	assert(expr_parse("3.14 * x * x / 4", ut));

	assert(expr_evaluate(ut, 4.0) == 12.56);
}

void print_ast(expr_ast::Node* node)
{
    std::cout << node->type << std::endl;
    if (node->get_left())
        print_ast(node->get_left());
    if (node->get_right())
        print_ast(node->get_right());
}

void test_ast()
{
    struct TestTokenizer: expr_ast::Tokenizer
    {
        expr_ast::Token current()
        {
           std::cout << "current " << c.type << std::endl;
           return c;
        }

        expr_ast::Token next()
        {
            c = *it;
            it++;
            std::cout << "next " << c.type << std::endl;
            return c;
        }

        std::vector<expr_ast::Token> tokens =
        {
                expr_ast::Token(expr_ast::TokenNumber),
                expr_ast::Token(expr_ast::TokenPlus),
                expr_ast::Token(expr_ast::TokenNumber)
        };

        std::vector<expr_ast::Token>::iterator it = tokens.begin();
        expr_ast::Token c = *it;
    };

    TestTokenizer tokenizer;
    expr_ast::Parser parser(tokenizer);

    expr_ast::Node* node = parser.expression();

    //print_ast(node);

    assert(node->type == expr_ast::OperatorPlus);
    assert(node->get_left()->type == expr_ast::Number);
    assert(node->get_right()->type == expr_ast::Number);
}


void test_plot_csv()
{
	CsvEngine engine(std::cout);

	std::vector<Point> points;
	points.push_back(Point(1, 0));
	points.push_back(Point(2, 0.6931471805599453));
	points.push_back(Point(3, 1.0986122886681098));

    engine.plot(points);

    // TODO: Check output
}




int main()
{
	test_parse();
	test_evaluate();
	test_spirit();
	test_ast();
	test_plot_csv();

	std::cout << "All OK" << std::endl;
}
