

#include "Drawer.h"
#include <qpainter.h>
#include "RecordVideo/Entity/FreeCurve.h"
#include "RecordVideo/Entity/HighlightedFreeCurve.h"
#include "RecordVideo/Entity/LineSegment.h"
#include "RecordVideo/Entity/ArrowLineSegment.h"
#include "RecordVideo/Entity/Number.h"


Drawer::Drawer(QPainter &painter)
	:painter(painter) {

}

Drawer::~Drawer() {

}

void Drawer::visit(FreeCurve *freeCurve) {

	QPen pen(freeCurve->getColor());
	pen.setWidth(freeCurve->getWidth());
	
	QPen oldPen = painter.pen();

	painter.setPen(pen);

	if (freeCurve->getSize() == 0) {
	
		painter.setPen(oldPen);
		return;
	}
	else if (freeCurve->getSize() == 1) {
	
		painter.drawPoint(*freeCurve->getPoint(0));
	}
	else {
	
		QPainterPath path;
		path.moveTo(*freeCurve->getPoint(0));

		for (int i = 1; i < freeCurve->getSize(); i++) {

			path.lineTo(*freeCurve->getPoint(i));
		}

		painter.drawPath(path);
	}

	painter.setPen(oldPen);
}


void Drawer::visit(HighlightedFreeCurve *highlightedFreeCurve) {
	
	QColor color = highlightedFreeCurve->getColor();
	color.setAlpha(highlightedFreeCurve->getAlpha());

	QPen pen(color);
	pen.setWidth(highlightedFreeCurve->getWidth());

	QPen oldPen = painter.pen();

	painter.setPen(pen);

	if (highlightedFreeCurve->getSize() == 0) {

		painter.setPen(oldPen);
		return;
	}
	else if (highlightedFreeCurve->getSize() == 1) {

		painter.drawPoint(*highlightedFreeCurve->getPoint(0));
	}
	else {

		QPainterPath path;
		path.moveTo(*highlightedFreeCurve->getPoint(0));

		for (int i = 1; i < highlightedFreeCurve->getSize(); i++) {

			path.lineTo(*highlightedFreeCurve->getPoint(i));
		}

		painter.drawPath(path);
	}

	painter.setPen(oldPen);
}


void Drawer::visit(LineSegment *lineSegment) {

	QPen pen(lineSegment->getColor());
	pen.setWidth(lineSegment->getWidth());

	QPen oldPen = painter.pen();

	painter.setPen(pen);


	painter.drawLine(lineSegment->getStart(), lineSegment->getEnd());

	painter.setPen(oldPen);
}

void Drawer::visit(ArrowLineSegment *arrowLineSegment) {


	QPen pen(arrowLineSegment->getColor());
	pen.setWidth(arrowLineSegment->getWidth());

	QPen oldPen = painter.pen();

	painter.setPen(pen);

	painter.drawLine(arrowLineSegment->getStart(), arrowLineSegment->getEnd());

	QPoint p1, p2, p3;
	arrowLineSegment->getArrowPoints(p1, p2, p3);

	painter.drawLine(p1.x(), p1.y(), p2.x(), p2.y());
	painter.drawLine(p1.x(), p1.y(), p3.x(), p3.y());

	painter.setPen(oldPen);
}

void Drawer::visit(Number *number) {

	QColor color = number->getColor();
	color.setAlpha(125);

	QBrush brush(color);
	QBrush oldBrush = painter.brush();
	painter.setBrush(brush);

	QPen pen(color);
	QPen oldPen = painter.pen();
	painter.setPen(pen);
	

	painter.drawEllipse(number->getPoint(), number->getWidth() / 2, number->getWidth() / 2);
	painter.setBrush(oldBrush);
	painter.setPen(oldPen);


	painter.setPen(QColor(255, 255, 255));
	painter.drawText(number->getPoint().x() - number->getWidth() / 2, number->getPoint().y() - number->getWidth() / 2,
		number->getWidth(), number->getWidth(), Qt::AlignVCenter | Qt::AlignHCenter, QString::number(number->getNumber()));
}