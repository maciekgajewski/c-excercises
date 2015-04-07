// #define BOOST_SPIRIT_DEBUG

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/support_utree.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

#include <iostream>
#include <string>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace spirit = boost::spirit;

    struct expr
    {
        template <typename T1, typename T2 = void>
        struct result { typedef void type; };

        expr(char op) : op(op) {}

        void operator()(spirit::utree& expr, spirit::utree const& rhs) const
        {
            spirit::utree lhs;
            lhs.swap(expr);
            expr.push_back(spirit::utf8_symbol_range_type(&op, &op+1));
            expr.push_back(lhs);
            expr.push_back(rhs);
        }

        char const op;
    };
    boost::phoenix::function<expr> const plus = expr('+');
    boost::phoenix::function<expr> const minus = expr('-');
    boost::phoenix::function<expr> const times = expr('*');
    boost::phoenix::function<expr> const divide = expr('/');

    struct negate_expr
    {
        template <typename T1, typename T2 = void>
        struct result { typedef void type; };

        void operator()(spirit::utree& expr, spirit::utree const& rhs) const
        {
            char const op = '-';
            expr.clear();
            expr.push_back(spirit::utf8_symbol_range_type(&op, &op+1));
            expr.push_back(rhs);
        }
    };
    boost::phoenix::function<negate_expr> neg;

    template <typename Iterator>
    struct calculator : qi::grammar<Iterator, ascii::space_type, spirit::utree()>
    {
        calculator() : calculator::base_type(expression)
        {
            using qi::uint_;
            using qi::_val;
            using qi::_1;

            expression =
                term                            [_val = _1]
                >> *(   ('+' >> term            [plus(_val, _1)])
                    |   ('-' >> term            [minus(_val, _1)])
                    )
                ;

            term =
                factor                          [_val = _1]
                >> *(   ('*' >> factor          [times(_val, _1)])
                    |   ('/' >> factor          [divide(_val, _1)])
                    )
                ;

            factor =
                uint_                           [_val = _1]
                |   '(' >> expression           [_val = _1] >> ')'
                |   ('-' >> factor              [neg(_val, _1)])
                |   ('+' >> factor              [_val = _1])
                ;

            BOOST_SPIRIT_DEBUG_NODE(expression);
            BOOST_SPIRIT_DEBUG_NODE(term);
            BOOST_SPIRIT_DEBUG_NODE(factor);
        }

        qi::rule<Iterator, ascii::space_type, spirit::utree()> expression, term, factor;
    };
}

bool expr_parse(const std::string& str, boost::spirit::utree& ut)
{
    using boost::spirit::ascii::space;

    typedef std::string::const_iterator iterator_type;
    typedef client::calculator<iterator_type> calculator;

    calculator calc;

	std::string::const_iterator iter = str.begin();
	std::string::const_iterator end = str.end();

	bool r = phrase_parse(iter, end, calc, space, ut);

	return (r && iter == end);
}

double expr_evaluate(const boost::spirit::utree& ut)
{
	return 0;
}

