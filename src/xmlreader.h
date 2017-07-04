#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTemporaryFile>
#include <QList>
#include <QStringRef>
#include <QByteArray>
#include <QBuffer>
#include "qzipreader_p.h"

class XMLReader : public QObject
{
    Q_OBJECT
public:

    explicit XMLReader(QObject *parent = 0);
    ~XMLReader();

    void parseXML(QXmlStreamReader &xml);
    QMap<QString,QString> parseSeries(QXmlStreamReader& xml);
    QMap<QString,QString> parseLanguages(QXmlStreamReader& xml);
    QMap<QString,QString> parseEpisode(QXmlStreamReader& xml);
    QMap<QString,QString> parseBanner(QXmlStreamReader& xml);
    void addElementDataToMap(QXmlStreamReader& xml,
                                 QMap<QString, QString>& map) const;
    void startRequest(QUrl url);

    void getLanguages();
    void searchSeries(QString text);
    void getFullSeriesRecord(QString seriesid, QString method);

    QList<QMap<QString,QString> > getSeries();
    QList<QMap<QString,QString> > getEpisodes();
    QList<QMap<QString,QString> > getBanners();

    bool getUpdateFlag();
    void setUpdateFlag(bool state);
    bool getFullRecordFlag();
    void setFullRecordFlag(bool state);

signals:
    void readyToPopulateSeries(QMap<QString, QList<QMap<QString, QString> > > data);
    void readyToStoreSeries(QMap<QString, QList<QMap<QString, QString> > > data);
    void readyToUpdateSeries(QMap<QString, QList<QMap<QString, QString> > > data);

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* m_nam;
    QList<QMap<QString,QString> > m_languages;
    QList<QMap<QString,QString> > m_series;
    QList<QMap<QString,QString> > m_episodes;
    QList<QMap<QString,QString> > m_banners;
    QString m_currentServerTime;

    bool m_fullRecord;
    bool m_update;

    QString getLocale();

};

#endif // XMLREADER_H
