/****************************************************************************
**
** Created by Sergei A. Bazylev.
** Contact: tubaluga@gmail.com
**
****************************************************************************/

#ifndef USERDATABASETABLEMODEL_H
#define USERDATABASETABLEMODEL_H

#include <QVector>
#include <QAbstractTableModel>

class UserDatabaseTableModel : public QAbstractTableModel {
	Q_OBJECT

	Q_PROPERTY(QString dbFileName READ dbFileName WRITE setDbFileName NOTIFY dbFileNameChanged)

public:
	explicit UserDatabaseTableModel(QObject *parent = nullptr);	

	QVariant data(const QModelIndex &index, int role) const override;

	QHash<int, QByteArray> roleNames() const override;

	int rowCount(const QModelIndex &index = QModelIndex()) const override;

	int columnCount(const QModelIndex &index = QModelIndex()) const override;

	const QString dbFileName() const;

	void setDbFileName(const QString &dbFileName);

private:
	void readFromFile(const QString &fileName);

private:
	QString m_dbFileName;
	QVector<QVector<QString>> m_data;

Q_SIGNALS:
	void dbFileNameChanged();
};

#endif // USERDATABASETABLEMODEL_H
