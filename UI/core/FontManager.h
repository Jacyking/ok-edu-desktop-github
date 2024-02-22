
#pragma once

#include <QObject>
#include <QCoreApplication>
#include <QStringList>
#include <QFontDatabase>
#include <QFont>

class FontManager : public QObject
{
	Q_OBJECT

public:
	FontManager(QObject *parent = nullptr);
	~FontManager();

	void loadFonts();
};
