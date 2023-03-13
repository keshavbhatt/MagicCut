#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "medialoader.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QObject>

/**
 * The MediaPlayer class provides a simple interface for playing media files
 * using QMediaPlayer and QMediaPlaylist.
 */
class MediaPlayer : public QObject
{
    Q_OBJECT
public:
    /**
     * Constructs a new MediaPlayer object.
     *
     * @param parent The parent QObject (optional).
     */
    explicit MediaPlayer(QObject *parent = nullptr);
    //    explicit MediaPlayer(QObject* parent = nullptr, m_player, m_mediaLoader);

    /**
     * Returns true if the player is currently playing media, false otherwise.
     *
     * @return True if the player is playing media, false otherwise.
     */
    bool isPlaying() const;

    /**
     * Returns the current volume of the player.
     *
     * @return The current volume level (0-100).
     */
    int volume() const;

    /**
     * Sets the volume level of the player.
     *
     * @param volume The new volume level (0-100).
     */
    void setVolume(int volume);

    /**
     * Stops playback of the current media item in the playlist.
     */
    void stop();

    /**
     * Pauses playback of the current media item in the playlist.
     */
    void pause();

    /**
     * Starts playback of the current media item in the playlist.
     */
    void play();

public slots:
    /**
     * Clears the current playlist and loads a new playlist.
     *
     * @param playlist A pointer to the new playlist to load.
     */
    void loadPlaylist(QMediaPlaylist *playlist);

    /**
     * Adds one or more media files to the playlist.
     *
     * @param fileNames A QStringList of file names to add to the playlist.
     */
    void addMedia(const QStringList &fileNames);

    /**
     * Adds a media content object to the playlist.
     *
     * @param mediaContent The media content object to add to the playlist.
     */
    void addMedia(const QMediaContent &mediaContent);

signals:
    /**
     * Emitted when the media status of the player changes.
     *
     * @param status The new media status of the player.
     */
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    /**
     * The QMediaPlayer object used to play media files.
     */
    QMediaPlayer *m_player;

    /**
     * The QMediaPlaylist object used to store media files.
     */
    QMediaPlaylist *m_playlist;
};

#endif // MEDIAPLAYER_H
