#pragma once

#include "InOutParameter.hpp"
#include <QStringList>

class CliRunner
{
  public:
    CliRunner() = default;
    explicit CliRunner(QStringList &&args, InOutParameter params);
    CliRunner(const CliRunner &) = delete;
    CliRunner(CliRunner &&)      = delete;
    ~CliRunner()                 = default;

    int run();

  private:
    QStringList m_args;
    InOutParameter m_params;

    static QString getSuffix(const QString &filepath);
};
