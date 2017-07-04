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
#include "xmlparser.h"

class XMLReader : public QObject
{
    Q_OBJECT
public:

    explicit XMLReader(QObject *parent = 0);
    ~XMLReader();

    void startRequest(QUrl url);

    void searchSeries(QString text);
    void getFullSeriesRecord(QString seriesid, QString method);

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
    XMLParser* m_parser;

    bool m_fullRecord;
    bool m_update;
};

#endif // XMLREADER_H
