#include "magiccircle.h"

#include <cmath>

#include <iostream>
using namespace std;

MagicCircle::MagicCircle(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags), _timer(this), _angle(0), _clockwise(true)
{
	try
	{
//		_tactonPlayer = new TactonPlayer("COM8");
		_tactonPlayer = new TactonPlayer("/dev/tty.usbserial-FTFRHUAO"); // Mac USB serial cable
	}
	catch (const char* message)
	{
		cerr << message << endl;
		_tactonPlayer = NULL;
	}
	catch (...)
	{
		cerr << "Error" << endl;
		_tactonPlayer = NULL;
	}
	
	setupUi(this);

	layout()->setSizeConstraint(QLayout::SetFixedSize);

	//set initial parameters
	setDirection(_direction->currentText());
	setResolution(_resolution->value());
	setSpeed(_speed->value());
	setFrequency(_frequency->value());

	connect(_play, SIGNAL(clicked(bool)), this, SLOT(play(bool)));
	connect(_stop, SIGNAL(clicked(bool)), this, SLOT(stop(bool)));

	connect(_direction, SIGNAL(currentTextChanged (const QString &)), this, SLOT(setDirection(const QString &)));
	connect(_speed, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
	connect(_resolution, SIGNAL(valueChanged(int)), this, SLOT(setResolution(int)));
	connect(_frequency, SIGNAL(valueChanged(int)), this, SLOT(setFrequency(int)));

	connect(this, SIGNAL(setAngle(float)), SLOT(tactileFeedback(float)));
	connect(this, SIGNAL(setAngle(float)), SLOT(visualFeedback(float)));

	connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
}

MagicCircle::~MagicCircle()
{
	stop(true);
}

void MagicCircle::play(bool)
{
	_timer.start();
}

void MagicCircle::stop(bool)
{
	_timer.stop();
	_tactonPlayer->stopBuzz();
}

void MagicCircle::update()
{
	if (_clockwise)
		_angle -= _stepsize;
	else
		_angle += _stepsize;

	while (_angle < 0)
		_angle += 360;

	while (_angle >= 360)
		_angle -= 360;

	emit setAngle(_angle);
}

void MagicCircle::setDirection(const QString &direction)
{
	_clockwise = (direction == "Clockwise");
}

void MagicCircle::setSpeed(int speed)
{
	_timer.setInterval(_stepsize / speed * 1000.0);
}

void MagicCircle::setResolution(int res)
{
	_stepsize = 360.0 / res;
	setSpeed(_speed->value());
}

void MagicCircle::setFrequency(int frequency)
{
	_tactonPlayer->setFrequency(frequency);
}

void MagicCircle::tactileFeedback(float angle)
{
	_tactonPlayer->playAngle(angle);
	return;
}

void MagicCircle::visualFeedback(float)
{
}
