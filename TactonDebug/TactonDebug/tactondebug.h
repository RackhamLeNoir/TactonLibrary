#ifndef TACTONDEBUG_H
#define TACTONDEBUG_H

#include <QMainWindow>
#include "ui_tactondebug.h"

#include <TactonPlayer.hpp>

class TactonDebug : public QMainWindow, Ui::TactonDebugClass
{
	Q_OBJECT

	public:
		TactonDebug(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
		~TactonDebug();

	public slots:
		void setFrequency(int f);
		void setFrequency(const QString &text);
		void setAmplitude(int a);
		void setAmplitude(const QString &text);
		void setDuration(int d);
		void setDuration(const QString &text);

		void play(bool);
		 
	private:
		static int MaxFrequency;
		static int MaxAmplitude;
		static int MaxDuration;

		TactonPlayer *_tactonPlayer;
};

#endif // TACTONDEBUG_H
