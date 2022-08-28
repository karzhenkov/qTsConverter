#pragma once

#include <QString>

struct CsvProperty {
    CsvProperty() = default;
    explicit CsvProperty(const QString &field_sep, const QString &string_sep) :
        field_separator{ field_sep }, string_separator{ string_sep }
    {
    }
    CsvProperty(const CsvProperty &) = default;
    CsvProperty(CsvProperty &&)      = default;
    ~CsvProperty()                   = default;

    CsvProperty &operator=(const CsvProperty &) = default;
    CsvProperty &operator=(CsvProperty &&) = default;

    void swap() {
    	std::swap(field_separator, string_separator);
    }

    QString field_separator;
    QString string_separator;
};
