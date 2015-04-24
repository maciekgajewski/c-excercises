#include "plot.h"
#include "engine_csv.cc"
#include "expr_spirit.cc"
#include "expr_ast.cc"

#include <cassert>
#include <iostream>
#include <vector>


void test_spirit()
{
	boost::spirit::utree ut;

	assert(expr_parse("3.14 * x * x / 4", ut));

	assert(expr_evaluate(ut, 4.0) == 12.56);
}

void test_ast()
{
    struct TestTokenizer: expr_ast::Tokenizer
    {
        expr_ast::Token next()
        {
            expr_ast::Token token = *it;
            it++;

            return token;
        }

        std::vector<expr_ast::Token> tokens =
        {
                expr_ast::Token(expr_ast::TokenDouble, 2),
                expr_ast::Token(expr_ast::TokenMul),
                expr_ast::Token(expr_ast::TokenLP),
                expr_ast::Token(expr_ast::TokenDouble, 1),
                expr_ast::Token(expr_ast::TokenPlus),
                expr_ast::Token(expr_ast::TokenDouble, 2),
                expr_ast::Token(expr_ast::TokenPlus),
                expr_ast::Token(expr_ast::TokenDouble, 3),
                expr_ast::Token(expr_ast::TokenRP)
        };

        std::vector<expr_ast::Token>::iterator it = tokens.begin();

    } tokenizer ;

    expr_ast::Parser parser(tokenizer);

    expr_ast::Node* node = parser.expression();

    expr_ast::print(node);

    assert(expr_ast::eval(node) == 12);
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
	test_spirit();
	test_ast();
	test_plot_csv();

	std::cout << "All OK" << std::endl;
}
