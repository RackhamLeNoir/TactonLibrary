#ifndef ANGLETESTER_H
#define ANGLETESTER_H

#include <QMainWindow>
#include "ui_angletester.h"

#include <TactonPlayer.hpp>

class AngleTester : public QMainWindow, Ui::AngleTesterClass
{
	Q_OBJECT

	public:
		AngleTester(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
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
