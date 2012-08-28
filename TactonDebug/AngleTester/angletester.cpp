#include "angletester.h"

#include <cmath>

AngleTester::AngleTester(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	try
	{
		_tactonPlayer = new TactonPlayer("COM4");
	}
	catch(...)
	{
		_tactonPlayer = NULL;
	}

	setupUi(this);

	layout()->setSizeConstraint(QLayout::SetFixedSize);

	setFrequency(_frequency->value());

	connect(_play, SIGNAL(clicked(bool)), this, SLOT(play(bool)));
	connect(_stop, SIGNAL(clicked(bool)), this, SLOT(stop(bool)));

	connect(_angle, SIGNAL(valueChanged(int)), this, SLOT(setAngle(int)));
	connect(_frequency, SIGNAL(valueChanged(int)), this, SLOT(setFrequency(int)));
}

AngleTester::~AngleTester()
{

}

void AngleTester::setFrequency(int frequency)
{
	_tactonPlayer->setFrequency(frequency);
}

void AngleTester::setAngle(int angle)
{
	unsigned char amplitudes[4];
	memset(amplitudes, 0, 4);

//	angle = 90;

	//vertical
	if (angle < 180)
		amplitudes[1] = 255 * sin(angle * M_PI / 180.0);
	else
		amplitudes[3] = - 255 * sin(angle * M_PI / 180.0);

	//horizontal
	if (angle < 90 ||angle > 270)
		amplitudes[0] = 255 * cos(angle * M_PI / 180.0);
	else
		amplitudes[2] = - 255 * cos(angle * M_PI / 180.0);

	_tactonPlayer->setAmplitudes(4, amplitudes);
}

void AngleTester::play(bool)
{
	setAngle(_angle->value());
}

void AngleTester::stop(bool)
{
	_tactonPlayer->stopBuzz();
}
