#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);

    /**
     * @brief Converts a size in bytes to a human-readable string with SI unit suffixes.
     *
     * This method takes a qint64 value representing the size in bytes and converts it
     * to a human-readable string with SI suffixes (e.g. "1.23 MB"). The size is rounded
     * to two decimal places and the largest appropriate suffix is appended.
     *
     * @param sizeInBytes The size in bytes to be converted.
     * @return A QString representing the size in a human-readable format.
     */
    static QString formatSize(qint64 sizeInBytes);
};

#endif // UTILS_H
