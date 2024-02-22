#pragma once
#include <memory>
#include <QObject>
#include <QtGui/QtGui>
#include <QPixmap>
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <base/basic_types.h>

namespace utils
{

	class ImageLoader : public QObject
	{

		Q_OBJECT

	public:
		ImageLoader(QObject *parent = nullptr);
		~ImageLoader();

		void load(const QString &url, Fn<void(const QByteArray &)> fn);


	private:
	};
}
