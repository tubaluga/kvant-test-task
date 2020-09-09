import QtQuick 2.12
import QtQuick.Window 2.12

import Application.Models 1.0

Window {
	width: 640
	height: 480
	visible: true
	title: qsTr("KVANT-application")

	UserDatabaseTableModel {
		id: userModel

		dbFileName: ':/user-db.txt'
	}

	TableView {
		id: tableView
		anchors.fill: parent

		property var columnWidths: [80, 100, 200]
		columnWidthProvider: function (column) { return columnWidths[column] }

		clip: true
		boundsBehavior: Flickable.StopAtBounds

		columnSpacing: 4
		rowSpacing: 4

		model: userModel
		delegate: Rectangle {

			implicitHeight: 30

			Text {
				anchors.fill: parent

				anchors.margins: {
					left: 6
					right: 6
				}

				verticalAlignment: Qt.AlignVCenter
				text: displayText
				elide: Text.ElideRight
			}
		}
	}
}
