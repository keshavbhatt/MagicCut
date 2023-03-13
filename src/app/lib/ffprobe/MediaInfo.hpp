#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QObject>
#include <QProcess>

/**
 * @brief The MediaInfo class provides a way to get media information using ffprobe in json format
 */
class MediaInfo : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a MediaInfo object with the given parent
     * @param parent the parent object
     */
    MediaInfo(QObject *parent = nullptr)
        : QObject(parent)
    {
        connect(&m_process,
                QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                this,
                &MediaInfo::processFinished);
        connect(&m_process,
                &QProcess::readyReadStandardOutput,
                this,
                &MediaInfo::processReadyReadStandardOutput);
        connect(&m_process, &QProcess::errorOccurred, this, &MediaInfo::processErrorOccurred);
    }

public slots:
    /**
     * @brief Gets information about the specified media file using ffprobe
     * @param fileName the path of the media file to get information for
     *
     * The infoReady() signal will be emitted with the file name and the media information as arguments
     * if the operation is successful. Otherwise, the infoFailed() signal will be emitted with the
     * file name and an error message as arguments.
     */
    void getInfo(const QString &fileName)
    {
        m_fileName = fileName;
        m_process.start("ffprobe",
                        QStringList() << "-hide_banner"
                                      << "-loglevel"
                                      << "fatal"
                                      << "-show_error"
                                      << "-show_format"
                                      << "-show_streams"
                                      << "-show_programs"
                                      << "-show_chapters"
                                      << "-show_private_data"
                                      << "-print_format"
                                      << "json"
                                      << "-i" << m_fileName);
    }

signals:

    /**
     * @brief This signal is emitted when media information has been retrieved successfully
     * @param fileName the path of the media file
     * @param info the media information
     */
    void infoReady(const QString &fileName, const QString &info);

    /**
     * @brief This signal is emitted when an error occurs while retrieving media information
     * @param fileName the path of the media file
     * @param error the error message
     */
    void infoFailed(const QString &fileName, const QString &error);

private slots:
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus)
    {
        if (exitStatus == QProcess::NormalExit && exitCode == 0) {
            emit infoReady(m_fileName, m_output);
        } else {
            emit infoFailed(m_fileName, "Failed to run ffprobe");
        }
    }

    void processReadyReadStandardOutput()
    {
        m_output += QString::fromUtf8(m_process.readAllStandardOutput());
    }

    void processErrorOccurred(QProcess::ProcessError error)
    {
        Q_UNUSED(error)
        emit infoFailed(m_fileName, "Failed to run ffprobe");
    }

private:
    QString m_fileName;
    QString m_output;
    QProcess m_process;
};

#endif // MEDIAINFO_H
