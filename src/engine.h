#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "xmlreader.h"
#include "databasemanager.h"
#include "./model/serieslistmodel.h"
#include "./model/episodelistmodel.h"
#include "./model/searchlistmodel.h"
#include "./model/todaylistmodel.h"
#include "./model/seasonlistmodel.h"

class Engine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SeriesListModel* SeriesListModel READ getSeriesListModel NOTIFY seriesListModelChanged)
    Q_PROPERTY(SearchListModel* SearchModel READ getSearchModel NOTIFY searchModelChanged)
    Q_PROPERTY(TodayListModel* TodayModel READ getTodayModel NOTIFY todayModelChanged)
    Q_PROPERTY(EpisodeListModel* EpisodeListModel READ getEpisodeListModel NOTIFY episodeListModelChanged)
    Q_PROPERTY(SeasonListModel* SeasonListModel READ getSeasonListModel NOTIFY seasonListModelChanged)
    Q_PROPERTY(bool Loading READ getLoading NOTIFY loadingChanged)

public:
    explicit Engine(QObject *parent = 0);
    ~Engine();

    SeriesListModel *getSeriesListModel();
    SearchListModel* getSearchModel();
    TodayListModel *getTodayModel();
    EpisodeListModel* getEpisodeListModel();
    SeasonListModel* getSeasonListModel();
    Q_INVOKABLE void updateModels();
    bool getLoading();

    Q_INVOKABLE int getWatchedEpisodesDuration();

signals:
    void seriesListModelChanged();
    void programListModelChanged();
    void searchModelChanged();
    void todayModelChanged();
    void episodeListModelChanged();
    void seasonListModelChanged();
    void loadingChanged();

public slots:
    void readyToUpdateModels();

private:
    SeriesListModel* m_seriesListModel;
    SearchListModel* m_searchListModel;
    TodayListModel* m_todayListModel;
    EpisodeListModel* m_episodeListModel;
    SeasonListModel* m_seasonListModel;
    XMLReader* m_reader;
    DatabaseManager* m_dbmanager;
    bool m_loading;
    void toggleLoading(bool state);
};

#endif // ENGINE_H
