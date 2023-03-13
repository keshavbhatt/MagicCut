#include "lib/json/jsonmodel.h"
#include "utils.h"

#include <QTest>

class UtilsTest : public QObject
{
    Q_OBJECT

private slots:
    void testGetMaxExpandDepthh();
};

void UtilsTest::testGetMaxExpandDepthh()
{
    // test data
    JsonModel *m_model = new JsonModel();

    QString data = R""(
                    {
                        "programs": [
                        ],
                        "streams": [
                            {
                                "index": 0,
                                "codec_name": "h264",
                                "codec_long_name": "H.264 / AVC / MPEG-4 AVC / MPEG-4 part 10",
                                "profile": "High",
                                "codec_type": "video",
                                "codec_tag_string": "avc1",
                                "codec_tag": "0x31637661",
                                "width": 1920,
                                "height": 1080,
                                "coded_width": 1920,
                                "coded_height": 1080,
                                "closed_captions": 0,
                                "film_grain": 0,
                                "has_b_frames": 2,
                                "sample_aspect_ratio": "1:1",
                                "display_aspect_ratio": "16:9",
                                "pix_fmt": "yuv420p",
                                "level": 40,
                                "color_range": "tv",
                                "color_space": "bt709",
                                "color_transfer": "bt709",
                                "color_primaries": "bt709",
                                "chroma_location": "left",
                                "field_order": "progressive",
                                "refs": 1,
                                "is_avc": "true",
                                "nal_length_size": "4",
                                "id": "0x1",
                                "r_frame_rate": "30/1",
                                "avg_frame_rate": "30/1",
                                "time_base": "1/15360",
                                "start_pts": 0,
                                "start_time": "0.000000",
                                "duration_ts": 2124800,
                                "duration": "138.333333",
                                "bit_rate": "1793888",
                                "bits_per_raw_sample": "8",
                                "nb_frames": "4150",
                                "extradata_size": 50,
                                "disposition": {
                                    "default": 1,
                                    "dub": 0,
                                    "original": 0,
                                    "comment": 0,
                                    "lyrics": 0,
                                    "karaoke": 0,
                                    "forced": 0,
                                    "hearing_impaired": 0,
                                    "visual_impaired": 0,
                                    "clean_effects": 0,
                                    "attached_pic": 0,
                                    "timed_thumbnails": 0,
                                    "captions": 0,
                                    "descriptions": 0,
                                    "metadata": 0,
                                    "dependent": 0,
                                    "still_image": 0
                                },
                                "tags": {
                                    "language": "und",
                                    "handler_name": "VideoHandler",
                                    "vendor_id": "[0][0][0][0]"
                                }
                            },
                            {
                                "index": 1,
                                "codec_name": "aac",
                                "codec_long_name": "AAC (Advanced Audio Coding)",
                                "profile": "LC",
                                "codec_type": "audio",
                                "codec_tag_string": "mp4a",
                                "codec_tag": "0x6134706d",
                                "sample_fmt": "fltp",
                                "sample_rate": "48000",
                                "channels": 2,
                                "channel_layout": "stereo",
                                "bits_per_sample": 0,
                                "id": "0x2",
                                "r_frame_rate": "0/0",
                                "avg_frame_rate": "0/0",
                                "time_base": "1/48000",
                                "start_pts": 0,
                                "start_time": "0.000000",
                                "duration_ts": 6640608,
                                "duration": "138.346000",
                                "bit_rate": "193332",
                                "nb_frames": "6486",
                                "extradata_size": 5,
                                "disposition": {
                                    "default": 1,
                                    "dub": 0,
                                    "original": 0,
                                    "comment": 0,
                                    "lyrics": 0,
                                    "karaoke": 0,
                                    "forced": 0,
                                    "hearing_impaired": 0,
                                    "visual_impaired": 0,
                                    "clean_effects": 0,
                                    "attached_pic": 0,
                                    "timed_thumbnails": 0,
                                    "captions": 0,
                                    "descriptions": 0,
                                    "metadata": 0,
                                    "dependent": 0,
                                    "still_image": 0
                                },
                                "tags": {
                                    "language": "und",
                                    "handler_name": "SoundHandler",
                                    "vendor_id": "[0][0][0][0]"
                                }
                            }
                        ],
                        "chapters": [

                        ],
                        "format": {
                            "filename": "untitled.mp4",
                            "nb_streams": 2,
                            "nb_programs": 0,
                            "format_name": "mov,mp4,m4a,3gp,3g2,mj2",
                            "format_long_name": "QuickTime / MOV",
                            "start_time": "0.000000",
                            "duration": "138.347000",
                            "size": "34508695",
                            "bit_rate": "1995486",
                            "probe_score": 100,
                            "tags": {
                                "major_brand": "isom",
                                "minor_version": "512",
                                "compatible_brands": "isomiso2avc1mp41",
                                "encoder": "Lavf58.76.100"
                            }
                        }
                    })"";

    m_model->setJson(data.toUtf8());

//    // Call the getMaxExpandDepth method
//    int maxExpandDepth = Utils::getMaxExpandDepth(m_model->index(2, 0));

//    // Check the expected result
//    QCOMPARE(maxExpandDepth, 3);
}

QTEST_MAIN(UtilsTest)

#include "tst_utils.moc"
