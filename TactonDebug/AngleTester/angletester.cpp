#include "AngleTester.h"

#include <cmath>
#include <algorithm>
using namespace std;

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPoint>

#include "DMTactileDisplay.h"

AngleTester::AngleTester(QWidget *parent, Qt::WindowFlags flags)
: QMainWindow(parent, flags), 
  _angle(new DMTactileDisplay()), 
  _frequency(new QSpinBox()), 
  _tfrequency(new QSpinBox()), 
  _play(new QPushButton()),
  _stop(new QPushButton())
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

  //setupUi(this);
  
  resize(500, 600);
  QWidget *centralWidget = new QWidget(this);
  QVBoxLayout *verticalLayout = new QVBoxLayout(centralWidget);
  verticalLayout->setSpacing(6);
  verticalLayout->setContentsMargins(11, 11, 11, 11);
  _angle->setMaximum(359);
  _angle->setTracking(true);
  _angle->setInvertedAppearance(false);
  _angle->setInvertedControls(false);
  _angle->setWrapping(true);
  _angle->setNotchTarget(30.0);
  //_angle->setNotchesVisible(true);

  verticalLayout->addWidget(_angle);

  QFormLayout * formLayout = new QFormLayout();
  formLayout->setSpacing(6);

  QLabel *frequencyLabel = new QLabel(centralWidget);
  frequencyLabel->setText("Background frequency");
  _frequency->setMaximum(500);
  _frequency->setValue(100);
  formLayout->setWidget(0, QFormLayout::LabelRole, frequencyLabel);
  formLayout->setWidget(0, QFormLayout::FieldRole, _frequency);

  QLabel *tfrequencyLabel = new QLabel(centralWidget);
  tfrequencyLabel->setText("Target frequency");
  formLayout->setWidget(1, QFormLayout::LabelRole, tfrequencyLabel);
  _tfrequency->setMaximum(500);
  _tfrequency->setValue(250);
  formLayout->setWidget(1, QFormLayout::FieldRole, _tfrequency);
/*
  _play->setText("Play");
  _stop->setText("Stop");
  formLayout->setWidget(2, QFormLayout::FieldRole, _play);
  formLayout->setWidget(2, QFormLayout::LabelRole, _stop);
*/
  verticalLayout->addLayout(formLayout);
  setCentralWidget(centralWidget);

  //layout()->setSizeConstraint(QLayout::SetFixedSize);

  _angle->addTarget(Target(10, 60));
  _angle->addTarget(Target(100, 150));
  _angle->addTarget(Target(200, 250));

  setFrequency(_frequency->value());

//  connect(_play, SIGNAL(clicked(bool)), this, SLOT(play(bool)));
//  connect(_stop, SIGNAL(clicked(bool)), this, SLOT(stop(bool)));

  //connect(_angle, SIGNAL(valueChanged(int)), this, SLOT(setAngle(int)));
  connect(_angle, SIGNAL(updateAll(int, DMTactileDisplay::Hover)), this, SLOT(setOutput(int, DMTactileDisplay::Hover)));
  connect(_angle, SIGNAL(stop()), this, SLOT(stop()));
  connect(_frequency, SIGNAL(valueChanged(int)), this, SLOT(setFrequency(int)));
}

AngleTester::~AngleTester()
{
}

void AngleTester::setFrequency(int frequency)
{
  _tactonPlayer->setFrequency(frequency);
}

void AngleTester::setOutput(int angle, DMTactileDisplay::Hover hover)
{
  if (hover == DMTactileDisplay::OnTarget)
    _tactonPlayer->setFrequency(_tfrequency->value());
  else
    _tactonPlayer->setFrequency(_frequency->value());
  _tactonPlayer->playAngle(angle);
  return;
}

void AngleTester::play(bool)
{
//  setFrequency(_frequency->value());
//  setAngle(_angle->value());
}

void AngleTester::stop(bool)
{
  _tactonPlayer->stopBuzz();
}
