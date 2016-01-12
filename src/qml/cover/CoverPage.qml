import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    id: cover

    Label {
        id: placeholder
        text: qsTr("Nothing airs tonight")
        font.pixelSize: Theme.fontSizeTiny
        color: Theme.secondaryColor
        anchors.centerIn: cover
        visible: listView.count === 0 && controller.SeriesListModel.Mode === "default"
    }

    //---------------------------------
    // This is the "MySeries" coverPage
    //---------------------------------

    function nextEpisodeDetails(episodeName,daysTo,status) {

        if(status === "Ended") {
            return qsTr("This show has ended");
        } else if(daysTo === "today") {
            return episodeName + " " + qsTr("airs tonight");
        } else if(daysTo === "tommorrow") {
            return episodeName + " " + qsTr("airs tomorrow");
        } else if(episodeName.length !== 0) {
            return episodeName + " " + qsTr("airs in") + " " + daysTo + " " + qsTr("days");
        } else if(episodeName.length === 0 && daysTo !== "unknown") {
            return qsTr("Next episode airs in") + " " + daysTo + " " + qsTr("days");
        } else {
            return qsTr("No information about next episode");
        }
    }

    function setDetails() {

        if(controller.SeriesListModel.Mode === "mySeries" &&
                controller.SeriesListModel.NextEpisodeName !== null &&
                controller.SeriesListModel.DaysToNextEpisode !== null &&
                controller.SeriesListModel.Status !== null) {
            return nextEpisodeDetails(controller.SeriesListModel.NextEpisodeName,controller.SeriesListModel.DaysToNextEpisode,controller.SeriesListModel.Status)
        }
    }

    function setPosterVisible() {
        if(controller.SeriesListModel.Mode === "mySeries" && controller.SeriesListModel.Poster !== null) {
            return "http://thetvdb.com/banners/" + controller.SeriesListModel.Poster
        }
    }

    Image {
        id: poster
        source: setPosterVisible()
        anchors.top: parent.top
        width: parent.width
        height: parent.height
        visible: controller.SeriesListModel.Mode === "mySeries"
        opacity: 1.0
    }

//    Label {
//        id: seriesName
//        text: "Arrow"
//        width: cover.width
//        truncationMode: TruncationMode.Fade
//        anchors.left: parent.left
//        anchors.leftMargin: 2 * Theme.paddingMedium
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 2 * Theme.paddingMedium
//        font.pixelSize: Theme.fontSizeTiny
//        color: Theme.highlightDimmerColor
//        visible: controller.SeriesListModel.Mode === "mySeries"
//    }

    //--------------------------------
    // This is the "default" coverPage
    //--------------------------------

    function defaultVisibility() {
        var ret = false;
        if(controller.SeriesListModel.Mode === "default") {
            ret = true;
        }
        return ret;
    }

//    Label {
//        id: defaultheader
//        text: qsTr("On Tonight")
//        color: Theme.primaryColor
//        font.pixelSize: Theme.fontSizeMedium
//        anchors.top: cover.top
//        anchors.topMargin: Theme.paddingLarge
//        anchors.left: cover.left
//        anchors.leftMargin: Theme.paddingMedium
//        visible: listView.count !== 0 && defaultVisibility()
//    }

    SectionHeader {
        id: defaultheader
        text: qsTr("On Tonight")
        anchors {
            top: cover.top
            topMargin: Theme.paddingLarge
        }
        visible: listView.count !== 0 && defaultVisibility()
    }

    SilicaListView {
        visible: defaultVisibility()
        id: listView
        height: 500
        anchors.top: defaultheader.bottom
        anchors.topMargin: Theme.paddingSmall
        model: controller.TodayModel.TodayModel

        delegate: ListItem {
            id: item
            contentHeight: column.height * 1.1
            contentWidth: listView.width

            Column {
                id: column
                x: Theme.paddingMedium

                Label {
                    id: seriesName
                    text: SeriesName.length === 0 ? text = "SeriesName" : text = SeriesName
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                    truncationMode: TruncationMode.Fade
                    width: cover.width
                }

                Label {
                    id: episodeName
                    text: NextEpisodeName
                    font.pixelSize: Theme.fontSizeTiny
                    color: Theme.secondaryColor
                    truncationMode: TruncationMode.Fade
                    width: cover.width
                }

                Label {
                    id: network
                    text: AirsTime + " @ " + Network
                    font.pixelSize: Theme.fontSizeTiny
                    color: Theme.secondaryColor
                    truncationMode: TruncationMode.Fade
                    width: cover.width
                }
            }
        }
    }
}





// UPCOMING IDEAS

//            function search() {

//                appWindow.activate()

//                var page = pageStack.currentPage
//                if(page.contains("SearchPage")) {
//                    //appWindow.activate()
//                } else if(page.contains("MySeries") || page.contains("SeriesViewPage")) {
//                    pageStack.pop()
//                    pageStack.completeAnimation()
//                    pageStack.push(Qt.resolvedUrl("SearchPage.qml"))
//                } else if(page.contains("StartPage")) {
//                    pageStack.push(Qt.resolvedUrl("SearchPage.qml"))
//                }

//                console.log(page)
//            }
