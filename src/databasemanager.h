#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QFile>
#include <QDir>
#include <QtSql/QSqlQuery>
#include <QTextStream>
#include <QStandardPaths>
#include <QVariant>
#include <QDebug>
#include <QBuffer>
#include <QStringRef>
#include <QDate>
#include <QLocale>
#include <QDateTime>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();

    bool openDB();
    bool deleteDB();
    QSqlError lastError();
    void close();
    bool createDB();
    void setUpDB();

    bool startTransaction();
    bool commit();

    bool initializeInfoTable();
    bool createInfoTable();
    bool updateInfoTable(double version);

    bool createSeriesTable();
    bool createEpisodeTable();
    bool createBannerTable();

    bool deleteDuplicateEpisodes();

    bool insertSeries(QMap<QString, QString> series);
    bool insertEpisodes(QList<QMap<QString, QString> > episodes);
    bool insertBanners(QList<QMap<QString, QString> > banners, int seriesId);

    bool updateSeries();
    bool updateEpisode();

    bool deleteSeries(int seriesID);
    bool deleteAllSeries();

    QList<QMap<QString, QString> > getEpisodes(int seriesID, int seasonNumber);
    QMap<QString, QString> getNextEpisodeDetails(int seriesID);
    QString getStatus(int seriesID);
    QString getSeasonBanner(int seriesID, int season);

    void toggleWatched(QString episodeID);
    void markSeasonWatched(int seriesID, int season);

    bool isAlreadyAdded(int seriesId, QString name);
    int watchedCount(int seriesID);
    int watchedCountBySeason(int seriesID, int seasonNumber);
    int totalCount(int seriesID);
    int totalCountBySeason(int seriesID, int seasonNumber);
    int seasonCount(int seriesID);

    int getWatchedEpisodesDuration();
    double getAverageWatchedEpisodesDuration();
    int getWatchedEpisodesCount();
    int getAllEpisodesCount();
    int getAllSeriesCount();
    int getEndedSeriesCount();
    int getWatchedSeriesCount();
    int getWatchedSeasonsCount();
    int getAllSeasonsCount();
    QString getLastRefresh();

    QMultiMap<int, QMap<QString, QStringList> > getMostWatchedDirectors();
    QMultiMap<int, QMap<QString, QStringList> > getMostWatchedActors();

signals:
    void populateTodayModel(QList<QMap<QString, QString> > allSeries);
    void populateBannerList(QList<QMap<QString, QString> > allSeries);

public slots:
    void getStartPageSeries();
    void getSeries();

private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
