#include "mediaplayer.h"

MediaPlayer::MediaPlayer(QObject *parent)
    : QObject(parent)
    , m_player(new QMediaPlayer(this))
    , m_playlist(new QMediaPlaylist(this))
{
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayer::mediaStatusChanged);
}

void MediaPlayer::addMedia(const QMediaContent &mediaContent)
{
    m_playlist->addMedia(mediaContent);
}

void MediaPlayer::addMedia(const QStringList &fileNames)
{
    foreach (const QString &fileName, fileNames) {
        QMediaContent mediaContent(QUrl::fromLocalFile(fileName));
        m_playlist->addMedia(mediaContent);
    }
}

void MediaPlayer::loadPlaylist(QMediaPlaylist *playlist)
{
    m_playlist->clear();
    for (int i = 0; i < playlist->mediaCount(); ++i) {
        m_playlist->addMedia(playlist->media(i));
    }
}

void MediaPlayer::play()
{
    m_player->play();
}

void MediaPlayer::pause()
{
    m_player->pause();
}

void MediaPlayer::stop()
{
    m_player->stop();
}

void MediaPlayer::setVolume(int volume)
{
    m_player->setVolume(volume);
}

int MediaPlayer::volume() const
{
    return m_player->volume();
}

bool MediaPlayer::isPlaying() const
{
    return m_player->state() == QMediaPlayer::PlayingState;
}
