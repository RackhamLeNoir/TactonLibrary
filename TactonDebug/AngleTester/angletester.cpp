#include "angletester.h"

#include <cmath>

AngleTester::AngleTester(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	try
	{
		//_tactonPlayer = new TactonPlayer("COM4");
		_tactonPlayer = new TactonPlayer("/dev/tty.usbserial-FTFRHUAO"); // Mac USB serial cable
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
	_tactonPlayer->playAngle(angle);
	return;
}

void AngleTester::play(bool)
{
	setFrequency(_frequency->value());
	setAngle(_angle->value());
}

void AngleTester::stop(bool)
{
	_tactonPlayer->stopBuzz();
}
