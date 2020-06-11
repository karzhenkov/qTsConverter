#include "ConverterFactory.hpp"

#include "CsvBuilder.hpp"
#include "CsvParser.hpp"
#include "TsBuilder.hpp"
#include "TsParser.hpp"
#include "XlsxBuilder.hpp"
#include "XlsxParser.hpp"

#include <cassert>

std::unique_ptr<Converter> ConverterFactory::make_converter(
    ConverterFactory::ConversionType type, const std::string &in,
    const std::string &out, const std::string &fieldSep,
    const std::string &stringSep, const std::string &tsVersion)
{
    switch (type) {
        case ConversionType::Ts2Csv:
            return std::make_unique<Converter>(
                std::make_unique<TsParser>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ stringSep, fieldSep } }),
                std::make_unique<CsvBuilder>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ fieldSep, stringSep } }));
            break;

        case ConversionType::Csv2Ts:
            return std::make_unique<Converter>(
                std::make_unique<CsvParser>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ stringSep, fieldSep } }),
                std::make_unique<TsBuilder>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ fieldSep, stringSep } }));
            break;

        case ConversionType::Ts2Xlsx:
            return std::make_unique<Converter>(
                std::make_unique<TsParser>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ stringSep, fieldSep } }),
                std::make_unique<XlsxBuilder>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ fieldSep, stringSep } }));
            break;

        case ConversionType::Xlsx2Ts:
            return std::make_unique<Converter>(
                std::make_unique<XlsxParser>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ stringSep, fieldSep } }),
                std::make_unique<TsBuilder>(InOutParameter{
                    in, out, tsVersion, CsvProperty{ fieldSep, stringSep } }));
            break;

        default:
            break;
    }

    assert(false);
}
