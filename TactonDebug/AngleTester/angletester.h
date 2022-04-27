#pragma once

#include <QMainWindow>
#include <QSpinBox>
#include <QPushButton>
#include <QDial>
//#include "ui_angletester.h"

#include <TactonPlayer.hpp>

#include "DMTactileDisplay.h"

class AngleTester : public QMainWindow//, Ui::AngleTesterClass
{
  Q_OBJECT

  public:
    AngleTester(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~AngleTester();

  public slots:
    void play(bool);
    void stop(bool=false);
    void setFrequency(int frequency);
    void setOutput(int angle, DMTactileDisplay::Hover hover);

  private:
    DMTactileDisplay *_angle;
    QSpinBox *_frequency, *_tfrequency;
    QPushButton *_play, *_stop;
    int _tfreq, _bfreq;

    TactonPlayer *_tactonPlayer;
};
