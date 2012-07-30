#ifndef MAGICCIRCLE_H
#define MAGICCIRCLE_H

#include <QtGui/QMainWindow>
#include "ui_magiccircle.h"

#include <QTimer>

#include <TactonPlayer\TactonPlayer.hpp>

class MagicCircle : public QMainWindow, Ui::MagicCircleClass
{
	Q_OBJECT

	public:
		MagicCircle(QWidget *parent = 0, Qt::WFlags flags = 0);
		~MagicCircle();

	public slots:
		void play(bool);
		void stop(bool);
		void update();
		
		void setDirection(const QString &);
		void setSpeed(int);
		void setResolution(int);

		void tactileFeedback(float);
		void visualFeedback(float);

	signals:
		void setAngle(float a);		

	private:
		float _angle, _stepsize;
		bool _clockwise;

		TactonPlayer *_tactonPlayer;
		QTimer _timer;
};

#endif // MAGICCIRCLE_H
