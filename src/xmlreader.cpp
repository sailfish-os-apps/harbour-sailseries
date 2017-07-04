#include "xmlreader.h"

#define APIKEY "88D0BD893851FA78"
#define MIRRORPATH "http://thetvdb.com"

XMLReader::XMLReader(QObject *parent) :
    QObject(parent),
    m_nam(0),
    m_parser(new XMLParser),
    m_fullRecord(false),
    m_update(false)
{
    m_nam = new QNetworkAccessManager(this);

    connect(m_nam,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(replyFinished(QNetworkReply*)));
}

XMLReader::~XMLReader()
{
    delete m_nam;
    m_nam = 0;
}

void XMLReader::searchSeries(QString text)
{
    m_fullRecord = false;
    QString url = QString("%1/api/GetSeries.php?seriesname=%2").arg(QString(MIRRORPATH)).arg(text);
    QUrl finalUrl(url);
    startRequest(finalUrl);
}

void XMLReader::getFullSeriesRecord(QString seriesid, QString method)
{
    if (method == "full") {
        setFullRecordFlag(true);
    } else if (method == "update") {
        setUpdateFlag(true);
    }

    QString url = QString("%1/api/%2/series/%3/all/en.zip").arg(QString(MIRRORPATH)).arg(QString(APIKEY)).arg(seriesid);
    QUrl finalUrl(url);
    startRequest(finalUrl);
}

void XMLReader::startRequest(QUrl url)
{
    QNetworkRequest request(url);
    m_nam->get(request);
}

// ---------------------------------------------------
// slots
// ---------------------------------------------------

void XMLReader::replyFinished(QNetworkReply *reply)
{
    qDebug() << reply->url() << reply->errorString();

    // Error -> inform user by appending error message to listview
    if (reply->error() != QNetworkReply::NoError) {

        QMap<QString, QList<QMap<QString, QString> > > data;
        QList<QMap<QString, QString> > series;
        QMap<QString,QString> temp;

        temp.insert("SeriesName", "Error, try again later.");
        series.append(temp);
        data["series"] = series;

        emit readyToPopulateSeries(data);

        reply->deleteLater();
        return;
    }

    auto b = reply->readAll();
    auto buf = new QBuffer(&b);

    if (reply->url().toString().endsWith(".zip")) {
        auto zip = new QZipReader(buf);
        QXmlStreamReader xml(zip->fileData("en.xml"));
        QMap<QString, QList<QMap<QString, QString> > > data = m_parser->parseXML(xml);
        QXmlStreamReader xml_banners(zip->fileData("banners.xml"));
        QMap<QString, QList<QMap<QString, QString> > > banners = m_parser->parseXML(xml_banners);

        data.unite(banners);

        if (data["series"].size() != 0 && !getFullRecordFlag() && !getUpdateFlag()) {
            setFullRecordFlag(false);
            setUpdateFlag(false);
            emit readyToPopulateSeries(data);
        } else if (getFullRecordFlag()) {
            setFullRecordFlag(false);
            setUpdateFlag(false);
            emit readyToStoreSeries(data);
        } else if (getUpdateFlag()) {
            setFullRecordFlag(false);
            setUpdateFlag(false);
            emit readyToUpdateSeries(data);
        }

    } else {

        QXmlStreamReader xml(buf->buffer());
        auto data = m_parser->parseXML(xml);

        if (data["series"].size() != 0 && !getFullRecordFlag() && !getUpdateFlag()) {
            setFullRecordFlag(false);
            setUpdateFlag(false);
            emit readyToPopulateSeries(data);
        } else if (getFullRecordFlag()) {
            setFullRecordFlag(false);
            setUpdateFlag(false);
            emit readyToStoreSeries(data);
        } else if (getUpdateFlag()) {
            setFullRecordFlag(false);
            setUpdateFlag(false);
            emit readyToUpdateSeries(data);
        }
    }

    reply->deleteLater();
}

bool XMLReader::getUpdateFlag() { return m_update; }

void XMLReader::setUpdateFlag(bool state) { m_update = state; }

bool XMLReader::getFullRecordFlag() { return m_fullRecord; }

void XMLReader::setFullRecordFlag(bool state) { m_fullRecord = state; }
