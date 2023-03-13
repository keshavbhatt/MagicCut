#ifndef FFPROBEPARSER_H
#define FFPROBEPARSER_H

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class FFProbeParser
{
public:
    struct VideoStream
    {
        int index;
        QString codecName;
        QString codecLongName;
        QString profile;
        QString codecType;
        QString codecTagString;
        QString codecTag;
        int width;
        int height;
        int codedWidth;
        int codedHeight;
        int closedCaptions;
        int filmGrain;
        int hasBFrames;
        QString sampleAspectRatio;
        QString displayAspectRatio;
        QString pixelFormat;
        int level;
        QString colorRange;
        QString colorSpace;
        QString colorTransfer;
        QString colorPrimaries;
        QString chromaLocation;
        QString fieldOrder;
        int refs;
        bool isAVC;
        QString nalLengthSize;
        QString id;
        QString rFrameRate;
        QString avgFrameRate;
        QString timeBase;
        qint64 startPts;
        QString startTime;
        qint64 durationTs;
        QString duration;
        qint64 bitRate;
        int bitsPerRawSample;
        int nbFrames;
        int extradataSize;
        QJsonObject disposition;
        QJsonObject tags;
    };

    struct AudioStream
    {
        int index;
        QString codecName;
        QString codecLongName;
        QString profile;
        QString codecType;
        QString codecTagString;
        QString codecTag;
        QString sampleFormat;
        int sampleRate;
        int channels;
        QString channelLayout;
        int bitsPerSample;
        QString id;
        QString rFrameRate;
        QString avgFrameRate;
        QString timeBase;
        qint64 startPts;
        QString startTime;
        qint64 durationTs;
        QString duration;
        qint64 bitRate;
        int nbFrames;
        int extradataSize;
        QJsonObject disposition;
        QJsonObject tags;
    };

    struct Format
    {
        QString filename;
        int nbStreams;
        int nbPrograms;
        QString formatName;
        QString formatLongName;
        QString startTime;
        QString duration;
        qint64 size;
        qint64 bitRate;
        int probeScore;
        QJsonObject tags;
    };

    QList<VideoStream> videoStreams;
    QList<AudioStream> audioStreams;
    Format format;

    bool parse(const QByteArray &jsonData)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if (!jsonDoc.isObject())
            return false;

        QJsonObject jsonObj = jsonDoc.object();

        // Parse video streams
        if (jsonObj.contains("streams") && jsonObj["streams"].isArray()) {
            QJsonArray streamsArray = jsonObj["streams"].toArray();
            for (const QJsonValue &streamValue : streamsArray) {
                if (!streamValue.isObject())
                    continue;

                QJsonObject streamObj = streamValue.toObject();
                if (streamObj["codec_type"].toString() == "video") {
                    VideoStream videoStream;
                    videoStream.index = streamObj["index"].toInt();
                    videoStream.codecName = streamObj["codec_name"].toString();
                    videoStream.codecLongName = streamObj["codec_long_name"].toString();
                    videoStream.profile = streamObj["profile"].toString();
                    videoStream.codecType = streamObj["codec_type"].toString();
                    videoStream.codecTagString = streamObj["codec_tag_string"].toString();
                    videoStream.codecTag = streamObj["codec_tag"].toString();
                    videoStream.width = streamObj["width"].toInt();
                    videoStream.height = streamObj["height"].toInt();
                    videoStream.codedWidth = streamObj['coded_width'].toInt();
                    videoStream.codedHeight = streamObj['coded_height'].toInt();
                    videoStream.closedCaptions = streamObj['closed_captions'].toInt();
                    videoStream.filmGrain = streamObj['film_grain'].toInt();
                    videoStream.hasBFrames = streamObj['has_b_frames'].toInt();
                    videoStream.sampleAspectRatio = streamObj['sample_aspect_ratio'].toString();
                    videoStream.displayAspectRatio = streamObj['display_aspect_ratio'].toString();
                    videoStream.pixelFormat = streamObj['pixel_format'].toString();
                    videoStream.level = streamObj['level'].toInt();
                    videoStream.colorRange = streamObj['color_range'].toString();
                    videoStream.colorSpace = streamObj['color_space'].toString();
                    videoStream.colorTransfer = streamObj['color_transfer'].toString();
                    videoStream.colorPrimaries = streamObj['color_primaries'].toString();
                    videoStream.chromaLocation = streamObj['chroma_location'].toString();
                    videoStream.fieldOrder = streamObj['field_order'].toString();
                    videoStream.refs = streamObj['refs'].toInt();
                    videoStream.isAVC = streamObj['is_avc'].toBool();
                    videoStream.nalLengthSize = streamObj['nal_length_size'].toString();
                    videoStream.id = streamObj['id'].toString();
                    videoStream.rFrameRate = streamObj['r_frame_rate'].toString();
                    videoStream.avgFrameRate = streamObj['avg_frame_rate'].toString();
                    videoStream.timeBase = streamObj['time_base'].toString();
                    videoStream.startPts = streamObj['start_pts'].toInt();
                    videoStream.startTime = streamObj['start_time'].toString();
                    videoStream.durationTs = streamObj['duration_ts'].toInt();
                    videoStream.duration = streamObj['duration'].toString();
                    videoStream.bitRate = streamObj['bit_rate'].toInt();
                    videoStream.bitsPerRawSample = streamObj['bits_per_raw_sample'].toInt();
                    videoStream.nbFrames = streamObj['nb_frames'].toInt();
                    videoStream.extradataSize = streamObj['extradata_size'].toInt();
                    //QJsonObject disposition;
                    //QJsonObject tags;
                } else if (streamObj["codec_type"].toString() == "audio") {
                    //TODO complete this shit
                }
            }
        }
    }
}

#endif // FFPROBEPARSER_H
