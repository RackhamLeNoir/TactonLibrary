#ifndef ANGLETESTER_H
#define ANGLETESTER_H

#include <QtGui/QMainWindow>
#include "ui_angletester.h"

#include <TactonPlayer\TactonPlayer.hpp>

class AngleTester : public QMainWindow, Ui::AngleTesterClass
{
	Q_OBJECT

	public:
		AngleTester(QWidget *parent = 0, Qt::WFlags flags = 0);
		~AngleTester();

	public slots:
		void play(bool);
		void stop(bool);
		void setFrequency(int frequency);
		void setAngle(int angle);

	private:
		TactonPlayer *_tactonPlayer;
};

#endif // ANGLETESTER_H
