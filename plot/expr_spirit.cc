#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/support_utree.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

#include <iostream>
#include <string>

namespace expr_spirit
{
    namespace qi = boost::spirit::qi;
    namespace ascii =  boost::spirit::ascii;
    namespace spirit = boost::spirit;

    struct expr
    {
        template<typename T1, typename T2 = void>
        struct result
        {
            typedef void type;
        };

        expr(char op): op(op) {}

        void operator()(spirit::utree& expr, spirit::utree const& rhs) const
        {
            spirit::utree lhs;
            lhs.swap(expr);
            expr.push_back(spirit::utf8_symbol_range_type(&op, &op + 1));
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
        template<typename T1, typename T2 = void>
        struct result {
            typedef void type;
        };

        void operator()(spirit::utree& expr, spirit::utree const& rhs) const
        {
            char const op = '-';
            expr.clear();
            expr.push_back(spirit::utf8_symbol_range_type(&op, &op + 1));
            expr.push_back(rhs);
        }
	};
	boost::phoenix::function<negate_expr> neg;

    template <typename Iterator>
    struct parser : qi::grammar<Iterator, ascii::space_type, spirit::utree()>
    {
        parser() : parser::base_type(expression)
        {
            using qi::double_;
            using qi::char_;
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

            factor = symbol                     [_val = _1]
                | double_                       [_val = _1]
                |   '(' >> expression           [_val = _1] >> ')'
                |   ('-' >> factor              [neg(_val, _1)])
                |   ('+' >> factor              [_val = _1])
                ;

            symbol = char_('x');

        }

        qi::rule<Iterator, ascii::space_type, spirit::utree()> expression, term, factor;
        qi::rule<Iterator, spirit::utf8_symbol_type()> symbol;

    };

    bool parse(const std::string& str, boost::spirit::utree& ut)
    {
        using boost::spirit::ascii::space;

        typedef std::string::const_iterator iterator_type;
        typedef expr_spirit::parser<iterator_type> parser;

        parser pr;

        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();

        bool r = phrase_parse(iter, end, pr, space, ut);

        return (r && iter == end);
    }

    double evaluate(const boost::spirit::utree& ut, double x)
    {
        using boost::spirit::utree;
        using boost::spirit::utree_type;
        using boost::spirit::utf8_symbol_range_type;

        auto it = ut.begin();

        auto node_operation = *it;
        ++it;
        auto node_left = *it;
        ++it;
        auto node_right = *it;

        char operation = *(node_operation.get<utf8_symbol_range_type>().begin());
        double a;
        double b;

        auto eval = [&] (const boost::spirit::utree& node)
        {
            if (node.which() == utree_type::list_type)
                return evaluate(node, x);
            if (node.which() == utree_type::symbol_type)
                return x;
            return node.get<double>();
        };

        a = eval(node_left);
        b = eval(node_right);

        if (operation == '*')
            return a * b;
        else if (operation == '/')
            return a / b;
        else if (operation == '+')
            return a + b;
        else if (operation == '-')
            return a - b;

        return 0;
    }

    double eval(const boost::spirit::utree& node, double x)
    {
        using boost::spirit::utree_type;

        if (node.which() == utree_type::list_type)
            return evaluate(node, x);

        if (node.which() == utree_type::symbol_type)
            return x;

        return node.get<double>();
    };


}
