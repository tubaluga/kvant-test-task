#include <QFile>
#include <QDebug>
#include <QTextStream>

#include "userdatabasetablemodel.h"

UserDatabaseTableModel::UserDatabaseTableModel(QObject *parent) : QAbstractTableModel(parent) {
}

void UserDatabaseTableModel::readFromFile(const QString &fileName) {
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly)) {
		qWarning() << file.errorString();
		return;
	}

	QTextStream stream(&file);

	QString row;

	beginResetModel();

	m_data.clear();

	while (stream.readLineInto(&row)) {
		m_data.append(row.trimmed().split(';').toVector());
	}

	endResetModel();
}

QVariant UserDatabaseTableModel::data(const QModelIndex &index, int role) const {
	switch (role) {
	case Qt::DisplayRole: {

		if (index.isValid() && m_data.size() > index.row() &&
				m_data[index.row()].size() > index.column()) {
			return m_data[index.row()][index.column()];
		}
	}
	default:
		break;
	}

	return QVariant();
}

QHash<int, QByteArray> UserDatabaseTableModel::roleNames() const {
	return { {Qt::DisplayRole, "displayText"} };
}

int UserDatabaseTableModel::rowCount(const QModelIndex &index) const {
	Q_UNUSED(index)

	return m_data.size();
}

int UserDatabaseTableModel::columnCount(const QModelIndex &index) const {	
	Q_UNUSED(index)

	return 3;
}

const QString UserDatabaseTableModel::dbFileName() const {
	return m_dbFileName;
}

void UserDatabaseTableModel::setDbFileName(const QString &dbFileName) {

	if (m_dbFileName == dbFileName) {
		return;
	}

	m_dbFileName = dbFileName;

	readFromFile(m_dbFileName);

	emit dbFileNameChanged();
}
