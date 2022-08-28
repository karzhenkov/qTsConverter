#include "CliRunner.hpp"

#include "ConverterFactory.hpp"

#include <QDir>
#include <QtDebug>

CliRunner::CliRunner(QStringList &&args, InOutParameter params) :
    m_args{ args }, m_params(params)
{
}

auto CliRunner::run() -> int
{
    if (m_args.size() < 2) {
        qCritical() << "error, only 1 parameter passed as arg.";
        return 1;
    }

    const auto input = m_args.at(0);
    auto output      = m_args.at(1);

    if (output.startsWith("./")) {
        output = QDir::toNativeSeparators(QDir::currentPath() + "/" + output);
    }

    using CF        = ConverterFactory;
    const auto type = CF::fromString(getSuffix(input), getSuffix(output));
    m_params.inputFile = input;
    m_params.outputFile = output;
    auto converter  = CF::make_converter(type, m_params);

    const auto tmpResult = converter->process();
    qInfo() << tmpResult.failed << tmpResult.message
            << tmpResult.detailedMessage;
    return static_cast<int>(tmpResult.failed);
}

auto CliRunner::getSuffix(const QString &filepath) -> QString
{
    const auto dotPoint = filepath.lastIndexOf('.');
    return filepath.right(filepath.size() - dotPoint);
}
