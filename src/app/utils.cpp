#include "utils.h"

Utils::Utils(QObject *parent)
    : QObject{parent}
{}

QString Utils::formatSize(qint64 sizeInBytes)
{
    static const QStringList suffixes = { "B", "KB", "MB", "GB", "TB" };

    int suffixIndex = 0;
    double size = static_cast<double>(sizeInBytes);

    while (size >= 1024.0 && suffixIndex < suffixes.count() - 1) {
        size /= 1024.0;
        suffixIndex++;
    }

    QString result = QString::number(size, 'f', 2);
    result.append(" ").append(suffixes.at(suffixIndex));

    return result;
}
