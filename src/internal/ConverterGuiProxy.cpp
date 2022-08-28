#include "ConverterGuiProxy.hpp"

ConverterGuiProxy::ConverterGuiProxy(QObject *parent) : QObject(parent) {}

void ConverterGuiProxy::convert(QConversionType type, QStringList input,
                                QString output, const QString &fieldSeparator,
                                const QString &stringSeparator,
                                const QString &tsVersion)
{
    const auto convType = static_cast<ConverterFactory::ConversionType>(type);

    std::for_each(input.begin(), input.end(),
                  [](auto &in) { in = QUrl::fromUserInput(in).toLocalFile(); });

    output = QUrl::fromUserInput(output).toLocalFile();

    auto result = Converter::CoversionResult(
        false, QStringLiteral("Conversion successfull!"), {});

    const auto inputDim           = input.size();
    const auto multipleConversion = inputDim > 1;

    QStringList out;
    if (multipleConversion) {
        for (const auto &i : input) {
            auto n    = i.right(i.length() - 1 - i.lastIndexOf("/"));
            n         = n.left(n.lastIndexOf("."));
            auto name = output + "/" + n + ConverterFactory::toString(convType);
            out.append(name);
        }
    }

    for (int i = 0; i < inputDim; ++i) {
        const auto o = multipleConversion ? out[i] : output;

        auto converter = ConverterFactory::make_converter(
            convType, { input[i], o, fieldSeparator, stringSeparator, tsVersion });

        const auto tmpResult = converter->process();
        if (!tmpResult.failed) {
            setConversionInfo(tmpResult.failed, tmpResult.message,
                              tmpResult.detailedMessage);
            return;
        }
    }

    setConversionInfo(result.failed, result.message, result.detailedMessage);
}

auto ConverterGuiProxy::convSuccessfull() const -> bool
{
    return m_convSuccessfull;
}

auto ConverterGuiProxy::convMsg() const -> QString
{
    return m_convMsg;
}

auto ConverterGuiProxy::detailedConvMsg() const -> QString
{
    return m_detailedConvMsg;
}

void ConverterGuiProxy::setConversionInfo(bool convSuccessfull,
                                          const QString &errorMsg,
                                          const QString &detailedConvMsg)
{
    m_convSuccessfull = convSuccessfull;
    m_convMsg         = errorMsg;
    m_detailedConvMsg = detailedConvMsg;
    emit conversionCompleted();
}

static_assert(static_cast<int>(ConverterGuiProxy::QConversionType::Dummy) ==
                  static_cast<int>(ConverterFactory::ConversionType::Dummy),
              "enum proxy QConversionType is different than ConversionType");
