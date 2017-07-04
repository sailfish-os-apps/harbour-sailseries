#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QMap>
#include <QList>
#include <QDebug>

class XMLParser : public QObject
{
    Q_OBJECT
public:
    explicit XMLParser(QObject *parent = 0);

    QMap<QString, QList<QMap<QString, QString> > > parseXML(QXmlStreamReader &xml);

private:
    QMap<QString,QString> parseSeries(QXmlStreamReader& xml);
    QMap<QString,QString> parseEpisode(QXmlStreamReader& xml);
    QMap<QString,QString> parseBanner(QXmlStreamReader& xml);
    void addElementDataToMap(QXmlStreamReader& xml, QMap<QString, QString>& map) const;
};

#endif // XMLPARSER_H
