#include "tactondebug.h"

int TactonDebug::MaxFrequency = 400;
int TactonDebug::MaxAmplitude = 255;
int TactonDebug::MaxDuration = 2000;

TactonDebug::TactonDebug(QWidget *parent, Qt::WFlags flags)
:QMainWindow(parent, flags)
{
	try
	{
		_tactonPlayer = new TactonPlayer("COM8");
	}
	catch(...)
	{
		_tactonPlayer = NULL;
	}

	setupUi(this);

	//layout()->setSizeConstraint(QLayout::SetFixedSize);

	QObject::connect(frequencebox, SIGNAL(textChanged(const QString &)), this, SLOT(setFrequency(const QString &)));
	QObject::connect(frequenceslider, SIGNAL(valueChanged(int)), this, SLOT(setFrequency(int)));
	QObject::connect(amplitudebox, SIGNAL(textChanged(const QString &)), this, SLOT(setAmplitude(const QString &)));
	QObject::connect(amplitudeslider, SIGNAL(valueChanged(int)), this, SLOT(setAmplitude(int)));
	QObject::connect(durationbox, SIGNAL(textChanged(const QString &)), this, SLOT(setDuration(const QString &)));
	QObject::connect(durationslider, SIGNAL(valueChanged(int)), this, SLOT(setDuration(int)));

	QObject::connect(playbutton, SIGNAL(clicked(bool)), this, SLOT(play(bool)));
}

TactonDebug::~TactonDebug()
{

}

void TactonDebug::setFrequency(int f)
{
	if (f > MaxFrequency)
		f = MaxFrequency;
	frequencebox->setText(QString::number(f));
}

void TactonDebug::setFrequency(const QString &text)
{
	int f = text.toInt();
	if (f > MaxFrequency)
		f = MaxFrequency;
	frequenceslider->setValue(f);
}

void TactonDebug::setAmplitude(int a)
{
	if (a > MaxAmplitude)
		a = MaxAmplitude;
	amplitudebox->setText(QString::number(a));
}

void TactonDebug::setAmplitude(const QString &text)
{
	int a = text.toInt();
	if (a > MaxAmplitude)
		a = MaxAmplitude;
	amplitudeslider->setValue(a);
}

void TactonDebug::setDuration(int d)
{
	if (d > MaxDuration)
		d = MaxDuration;
	durationbox->setText(QString::number(d));
}

void TactonDebug::setDuration(const QString &text)
{
	int d = text.toInt();
	if (d > MaxDuration)
		d = MaxDuration;
	durationslider->setValue(d);
}

void TactonDebug::play(bool)
{
	if (!_tactonPlayer)
		return;
	unsigned char pattern = up->isChecked() * POS2_UP |
		right->isChecked() * POS2_RIGHT |
		left->isChecked() * POS2_LEFT | 
		down->isChecked() * POS2_DOWN;

	_tactonPlayer->play(Tacton(pattern, durationslider->value(), frequenceslider->value(), amplitudeslider->value()));
}
