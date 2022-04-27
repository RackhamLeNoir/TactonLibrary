#include "DMTactileDisplay.h"

#include <cmath>
#include <algorithm>
using namespace std;

#include <QPainter>
#include <QPoint>


Target::Target(int start, int end)
:_start(start), _end(end)
{
}

Target::Target(const Target & t)
:Target(t._start, t._end)
{
}

Target& Target::operator =(const Target& t)
{
  _start = t._start;
  _end = t._end;
  return *this;
}

DMTactileDisplay::DMTactileDisplay(QWidget *parent)
: QDial(parent), _timer(this)
{
  _timer.setSingleShot(true);

  connect(this, SIGNAL(valueChanged(int)), this, SLOT(updateAngle(int)));
  connect(&_timer, SIGNAL(timeout()), this, SLOT(released()));
}

void DMTactileDisplay::updateAngle(int value)
{
  _timer.start(500);
  bool onatarget = false;
  for (QList<Target>::const_iterator i = _targets.begin() ; i != _targets.end() ; i++)
  {
    if (value >= i->getStart() && value <= i->getEnd()) 
    {
      onatarget = true;
      break;
    }
  }
  if (onatarget)
    emit updateAll(value, OnTarget);
  else
    emit updateAll(value, OnBackground);
}

void DMTactileDisplay::released()
{
  emit stop();
}

void DMTactileDisplay::paintEvent(QPaintEvent *e)
{
  int margin = 10;
  int thickness = 10;
  int rhandle = 10;

  int r = (min(size().width(), size().height()) - margin - thickness) / 2;
  QPoint c(size().width() / 2, size().height() / 2);
  int angle = value() + 90;

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  //Display
  p.setPen(QPen(QColor(200,200,200), thickness));
  p.drawEllipse(c, r, r);

  //Targets
  p.setPen(QPen(QColor(43,153,255), thickness));
  for (QList<Target>::const_iterator i = _targets.begin() ; i != _targets.end() ; i++)
    p.drawArc(c.x() - r, c.y() - r, 2 * r, 2 * r, 16 * (- i->getStart() - 90), -16 * (i->getEnd() - i->getStart()));
  
  // Pointer
  p.setPen(Qt::NoPen);
  p.setBrush(QColor(250,43,38));
  p.drawEllipse(c + r * QPointF(cos(angle * M_PI / 180.0), sin(angle * M_PI / 180.0)), rhandle, rhandle);
}
