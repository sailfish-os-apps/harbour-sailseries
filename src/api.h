#ifndef API_H
#define API_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QList>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class Api : public QObject
{
    Q_OBJECT
public:

    explicit Api(QObject *parent = 0);
    ~Api();

    QList<QVariantMap> parseSeries(QJsonObject obj);
    QList<QVariantMap> parseJSON(QJsonObject obj);
    QVariantMap parseEpisode(QJsonObject obj);

    QNetworkReply* get(QUrl url);

    void getAuthenticationToken();
    void getLanguages();
    void searchSeries(QString seriesName);
    void getSeries(QString seriesId);
    void getSeasonImages(QString seriesId);
    void getPosterImages(QString seriesId);
    void getSeriesImages(QString seriesId);
    void getFanartImages(QString seriesId);
    void getActors(QString seriesId);
    void getEpisodes(QString seriesId, int page);
    void getAll(QString seriesId, QString method);
    void getEpisode(QString episodeId);

    QList<QVariantMap> series();
    QList<QVariantMap> episodes();
    QList<QVariantMap> banners();

    bool getUpdateFlag();
    void setUpdateFlag(bool state);
    bool getFullRecordFlag();
    void setFullRecordFlag(bool state);

    QString findHighestRatedImage(QList<QVariantMap> images);

signals:
    void readyToPopulateSeries(QList<QVariantMap>);
    void readyToStoreSeries(QList<QVariantMap>, QList<QVariantMap>, QList<QVariantMap>);
    void readyToUpdateSeries(QList<QVariantMap>, QList<QVariantMap>, QList<QVariantMap>);
    void readyToCheckIfReady();
    void readyToPopulateEpisodeDetails(QVariantMap episode);

public slots:
    void replyFinishedError(QNetworkReply* reply);
    void checkIfReady();

private:
    QNetworkAccessManager* m_nam;
    QList<QMap<QString,QString> > m_languages;

    QList<QVariantMap> m_series;
    QList<QVariantMap> m_episodes;
    QList<QVariantMap> m_actors;
    QList<QVariantMap> m_fanartImages;
    QList<QVariantMap> m_seasonImages;
    QList<QVariantMap> m_seriesImages;
    QList<QVariantMap> m_posterImages;

    bool m_seriesFinished;
    bool m_episodesFinished;
    bool m_actorsFinished;
    bool m_fanartImagesFinished;
    bool m_seasonImagesFinished;
    bool m_seriesImagesFinished;
    bool m_posterImagesFinished;

    bool m_fullRecord;
    bool m_update;
    QString m_jwt;

    QString getLocale();
};

#endif // API_H
