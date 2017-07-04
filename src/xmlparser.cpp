#include "xmlparser.h"

XMLParser::XMLParser(QObject *parent) : QObject(parent)
{

}

QMap<QString, QList<QMap<QString, QString> > > XMLParser::parseXML(QXmlStreamReader& xml)
{
    QMap<QString, QList<QMap<QString, QString> > > data;
    QList<QMap<QString, QString> > series;
    QList<QMap<QString, QString> > episodes;
    QList<QMap<QString, QString> > banners;

    /* We'll parse the XML until we reach end of it.*/
    while (!xml.atEnd() &&
          !xml.hasError()) {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = xml.readNext();
        /* If token is just StartDocument, we'll go to next.*/
        if (token == QXmlStreamReader::StartDocument) {
            continue;
        }
        /* If token is StartElement, we'll see if we can read it.*/
        if (token == QXmlStreamReader::StartElement) {

            /* If it's named Data, we'll go to the next.*/
            if (xml.name() == "Data") {
                continue;
            }
            /* If it's named Languages, we'll go to the next.*/
            if (xml.name() == "Languages") {
                continue;
            }
            /* If it's named Banners, we'll go to the next.*/
            if (xml.name() == "Banners") {
                continue;
            }

            /* If it's named Series, we'll dig the information from there.*/
            if (xml.name() == "Series") {
                series.append(this->parseSeries(xml));
            }
            /* If it's named Episode, we'll dig the information from there.*/
            if (xml.name() == "Episode") {
                episodes.append(this->parseEpisode(xml));
            }
            /* If it's named Banner, we'll dig the information from there.*/
            if (xml.name() == "Banner") {
                banners.append(this->parseBanner(xml));
            }
        }
    }
    /* Error handling. */
    if (xml.hasError()) {
        qDebug() << xml.errorString();
    }
    /* Removes any device() or data from the reader
         * and resets its internal state to the initial state. */
    xml.clear();

    if (series.size() != 0) {
        data["series"] = series;
    }

    if (episodes.size() != 0){
        data["episodes"] = episodes;
    }

    if (banners.size() != 0) {
        data["banners"] = banners;
    }

    return data;
}

// Base series record parsing.
QMap<QString, QString> XMLParser::parseSeries(QXmlStreamReader &xml)
{
    QMap<QString, QString> series;
    /* Let's check that we're really getting a series. */
    if (xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "Series") {
        return series;
    }
    /* Let's get the attributes for series */
    QXmlStreamAttributes attributes = xml.attributes();
    /* Let's check that series has id attribute. */
    if (attributes.hasAttribute("seriesid")) {
        /* We'll add it to the map. */
        series["seriesid"] = attributes.value("seriesid").toString();
    }
    /* Next element... */
    xml.readNext();
    /*
        * We're going to loop over the things because the order might change.
        * We'll continue the loop until we hit an EndElement named Series.
        */
    while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "Series")) {

        if (xml.tokenType() == QXmlStreamReader::StartElement) {

            if (xml.name() == "seriesid") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "id") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "Actors") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "Airs_DayOfWeek") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "Airs_Time") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "ContentRating") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "Genre") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "Rating") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "RatingCount") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "Runtime") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "Status") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "added") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "addedBy") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "fanart") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "lastupdated") {
                this->addElementDataToMap(xml, series);
            }

            if (xml.name() == "poster") {
                this->addElementDataToMap(xml, series);
            }

            /*------------------------------------------*/
            /* These come from searchSeries             */
            /*------------------------------------------*/

            /* We've found Language. */
            if (xml.name() == "Language") {
                this->addElementDataToMap(xml, series);
            }
            /* We've found SeriesName. */
            if (xml.name() == "SeriesName") {
                this->addElementDataToMap(xml, series);
            }
            /* We've found AliasNames. */
            if (xml.name() == "AliasNames") {
                this->addElementDataToMap(xml, series);
            }
            /* We've found banner. */
            if (xml.name() == "banner") {
                this->addElementDataToMap(xml, series);
            }
            /* We've found Overview. */
            if (xml.name() == "Overview") {
                this->addElementDataToMap(xml, series);
            }
            /* We've found FirstAired. */
            if (xml.name() == "FirstAired") {
                this->addElementDataToMap(xml, series);
            }
            /* We've found IMDB_ID. */
            if (xml.name() == "IMDB_ID") {
                this->addElementDataToMap(xml, series);
            }
            /* We've found zap2it_id. */
            if (xml.name() == "zap2it_id") {
                this->addElementDataToMap(xml, series);
            }
            /* We've found Network. */
            if (xml.name() == "Network") {
                this->addElementDataToMap(xml, series);
            }
        }
        /* ...and next... */
        xml.readNext();
    }
    return series;
}

QMap<QString, QString> XMLParser::parseEpisode(QXmlStreamReader &xml)
{
    QMap<QString, QString> episode;
    /* Let's check that we're really getting a Episode. */
    if (xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "Episode") {
        return episode;
    }
    /* Let's get the attributes for episode */
    QXmlStreamAttributes attributes = xml.attributes();
    /* Let's check that episode has id attribute. */
    if (attributes.hasAttribute("id")) {
        /* We'll add it to the map. */
        episode["id"] = attributes.value("id").toString();
    }
    /* Next element... */
    xml.readNext();
    /*
        * We're going to loop over the things because the order might change.
        * We'll continue the loop until we hit an EndElement named Episode.
        */
    while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "Episode")) {

        if (xml.tokenType() == QXmlStreamReader::StartElement) {

            if (xml.name() == "id") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "Director") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "EpisodeName") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "EpisodeNumber") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "GuestStars") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "ProductionCode") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "Rating") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "RatingCount") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "SeasonNumber") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "Writer") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "absolute_number") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "airsafter_season") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "airsbefore_episode") {
                this->addElementDataToMap(xml, episode);
            }

            /* Location of the episode image */
            if (xml.name() == "filename") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "lastupdated") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "seasonid") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "seriesid") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "thumb_added") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "thumb_height") {
                this->addElementDataToMap(xml, episode);
            }

            if (xml.name() == "thumb_width") {
                this->addElementDataToMap(xml, episode);
            }

            /* We've found language. */
            if (xml.name() == "Language") {
                this->addElementDataToMap(xml, episode);
            }

            /* We've found banner. */
            if (xml.name() == "banner") {
                this->addElementDataToMap(xml, episode);
            }

            /* We've found Overview. */
            if (xml.name() == "Overview") {
                this->addElementDataToMap(xml, episode);
            }

            /* We've found FirstAired. */
            if (xml.name() == "FirstAired") {
                this->addElementDataToMap(xml, episode);
            }

            /* We've found IMDB_ID. */
            if (xml.name() == "IMDB_ID") {
                this->addElementDataToMap(xml, episode);
            }
        }
        /* ...and next... */
        xml.readNext();
    }
    return episode;
}

QMap<QString, QString> XMLParser::parseBanner(QXmlStreamReader &xml)
{
    QMap<QString, QString> banner;
    /* Let's check that we're really getting a series. */
    if (xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "Banner") {
        return banner;
    }
    /* Let's get the attributes for series */
    QXmlStreamAttributes attributes = xml.attributes();
    /* Let's check that banner has id attribute. */
    if (attributes.hasAttribute("id")) {
        /* We'll add it to the map. */
        banner["id"] = attributes.value("id").toString();
    }
    /* Next element... */
    xml.readNext();
    /*
        * We're going to loop over the things because the order might change.
        * We'll continue the loop until we hit an EndElement named Series.
        */
    while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "Banner")) {

        if (xml.tokenType() == QXmlStreamReader::StartElement) {

            if (xml.name() == "id") {
                this->addElementDataToMap(xml, banner);
            }

            if (xml.name() == "BannerPath") {
                this->addElementDataToMap(xml, banner);
            }

            if (xml.name() == "BannerType") {
                this->addElementDataToMap(xml, banner);
            }

            if (xml.name() == "BannerType2") {
                this->addElementDataToMap(xml, banner);
            }

            if (xml.name() == "Language") {
                this->addElementDataToMap(xml, banner);
            }

            if (xml.name() == "Season") {
                this->addElementDataToMap(xml, banner);
            }
        }
        /* ...and next... */
        xml.readNext();
    }
    return banner;
}

void XMLParser::addElementDataToMap(QXmlStreamReader& xml, QMap<QString, QString>& map) const
{
    /* We need a start element, like <foo> */
    if (xml.tokenType() != QXmlStreamReader::StartElement) {
        return;
    }
    /* Let's read the name... */
    QString elementName = xml.name().toString();
    /* ...go to the next. */
    xml.readNext();
    /*
     * This elements needs to contain Characters so we know it's
     * actually data, if it's not we'll leave.
     */
    if (xml.tokenType() != QXmlStreamReader::Characters) {
        return;
    }
    /* Now we can add it to the map.*/
    map.insert(elementName, xml.text().toString());
}
