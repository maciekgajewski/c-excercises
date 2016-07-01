#pragma once

#include <QString>

#include <boost/property_tree/ptree.hpp>

namespace Teabag {


struct Translator
{
	using internal_type = std::string;
	using external_type = QString;

	inline boost::optional<QString> get_value(const std::string& s) const
	{
		return QString::fromStdString(s);
	}

	inline boost::optional<std::string> put_value(const QString& s) const
	{
		return s.toStdString();
	}
};

// GDB's MI input record, parsed

using Result = boost::property_tree::ptree;

QString toJson(const Result& r);

struct InputRecord
{
	int token;
	QString inputClass;
	QChar type;
	Result result;
};

} // Teabag

namespace boost { namespace property_tree {

template<>
struct translator_between<std::string, QString>
{
	using type = Teabag::Translator;
};

}}
