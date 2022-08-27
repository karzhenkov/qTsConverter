#include "XlsxBuilder.hpp"

#include "TitleHeaders.hpp"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QVersionNumber>
#include <QtDebug>

XlsxBuilder::XlsxBuilder(InOutParameter parameter) :
    Builder{ std::move(parameter) }
{
    if (!m_ioParameter.outputFile.endsWith("xlsx")) {
        m_ioParameter.outputFile += ".xlsx";
    }
}

auto XlsxBuilder::build(const Result &res) const -> bool
{
    QXlsx::Document xlsx;
    int row = 0;
    int col = 0;

    if (!m_ioParameter.noVersion) {
        addTsSupport(row, xlsx);
    }

    ++row;
    xlsx.write(row, ++col, TitleHeader::Context);
    xlsx.write(row, ++col, TitleHeader::Source);
    xlsx.write(row, ++col, TitleHeader::Translation);
    if (!m_ioParameter.noLocation) {
        xlsx.write(row, ++col, TitleHeader::Location);
    }

    for (const auto &tr : res.translantions) {
        for (const auto &msg : tr.messages) {
            col = 0;
            ++row;

            xlsx.write(row, ++col, tr.name);
            xlsx.write(row, ++col, msg.source);
            xlsx.write(row, ++col, msg.translation);

            if (!m_ioParameter.noLocation) {
                for (const auto &loc : msg.locations) {
                    xlsx.write(row, ++col,
                               QString(loc.first + " - " +
                                       QString::number(loc.second)));
                }
            }
        }
    }

    if (!xlsx.saveAs(m_ioParameter.outputFile)) {
        qWarning() << "error writing file";
        return false;
    }

    return true;
}

void XlsxBuilder::addTsSupport(int &row, QXlsx::Document &doc) const
{
    doc.write(++row, 1, TitleHeader::TsVersion);
    doc.write(++row, 1, m_ioParameter.tsVersion);
}
