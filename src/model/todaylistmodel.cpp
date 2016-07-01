#include "todaylistmodel.h"

TodayListModel::TodayListModel(QObject *parent, DatabaseManager *dbmanager, XMLReader *reader) :
    QObject(parent)
{
    m_dbmanager = dbmanager;
    m_reader = reader;

    populateTodayModel();
}

TodayListModel::~TodayListModel() {

    foreach(auto series, m_todayListModel) {
        delete series;
        series = 0;
    }
    qDebug() << "destructing TodayListModel";

}

QQmlListProperty<SeriesData> TodayListModel::getTodayModel() {

    return QQmlListProperty<SeriesData>(this,&m_todayListModel,&TodayListModel::todayListCount,&TodayListModel::todayListAt);

}

void TodayListModel::todayListAppend(QQmlListProperty<SeriesData>* prop, SeriesData* val) {

    TodayListModel* todayModel = qobject_cast<TodayListModel*>(prop->object);
    todayModel->m_todayListModel.append(val);
}

SeriesData* TodayListModel::todayListAt(QQmlListProperty<SeriesData>* prop, int index) {

    return (qobject_cast<TodayListModel*>(prop->object))->m_todayListModel.at(index);
}

int TodayListModel::todayListCount(QQmlListProperty<SeriesData>* prop) {
    return qobject_cast<TodayListModel*>(prop->object)->m_todayListModel.size();
}

void TodayListModel::todayListClear(QQmlListProperty<SeriesData>* prop) {
    qobject_cast<TodayListModel*>(prop->object)->m_todayListModel.clear();
}

void TodayListModel::populateTodayModel() {

    m_todayListModel.clear();
    emit todayModelChanged();

    auto allSeries = m_dbmanager->getStartPageSeries();
    auto length = allSeries.size();
    for(auto i = 0; i < length; ++i ) {
        auto temp = allSeries.at(i);
        auto series = new SeriesData(this, temp);
        m_todayListModel.append(series);
    }

    emit todayModelChanged();
}

