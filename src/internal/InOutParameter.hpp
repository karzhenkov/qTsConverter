#pragma once

#include "CsvProperty.hpp"

#include <QString>

struct InOutParameter {
    InOutParameter()                       = default;
    InOutParameter(const InOutParameter &) = default;
    InOutParameter(InOutParameter &&)      = default;
    ~InOutParameter()                      = default;

    InOutParameter &operator=(const InOutParameter &) = default;
    InOutParameter &operator=(InOutParameter &&) = default;

    InOutParameter(
    	const QString &in, const QString &out, const QString &fieldSep,
    	const QString &stringSep, const QString &tsVersion,
    	bool noVersion_ = false, bool noLocation_ = false,
    	const QString& language_ = QString())
      :
    	inputFile(in), outputFile(out), tsVersion(tsVersion),
    	csvProperty(stringSep, fieldSep),
    	noVersion(noVersion_), noLocation(noLocation_),
    	language(language_)
    {
    }

    InOutParameter(const QString &tsVersion) : tsVersion(tsVersion)
    {
    }

    QString inputFile;
    QString outputFile;
    QString tsVersion;
    CsvProperty csvProperty;
    bool noVersion;
    bool noLocation;
    QString language;
};
