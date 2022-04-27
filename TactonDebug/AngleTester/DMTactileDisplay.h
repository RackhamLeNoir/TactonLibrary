#pragma once

#include <QDial>
#include <QTimer>
#include <QList>
//#include "ui_DMTactileDisplayClass.h"

class Target: QObject
{
  Q_OBJECT

  public:
    Target(int start, int end);
    Target(const Target & t);
    ~Target() {}

    Target& operator =(const Target& t);

    inline int getStart() const { return _start; }
    inline int getEnd() const { return _end; }
    inline void move(int delta) { _start += delta; _end += delta; }
  
  private:
    int _start, _end;
};

class DMTactileDisplay : public QDial//, Ui::DMTactileDisplayClass
{
  Q_OBJECT

  public:
    DMTactileDisplay(QWidget *parent = 0);
    ~DMTactileDisplay() {}

    inline void addTarget(const Target &target) { _targets.append(target); }

    void paintEvent(QPaintEvent *);

    enum Hover {OnBackground, OnTarget};

  public slots:
    void updateAngle(int value);
    void released();

  signals:
    void updateAll(int angle, DMTactileDisplay::Hover h);
    void stop();

  private:
    QList<Target> _targets;
    QTimer _timer;
};
