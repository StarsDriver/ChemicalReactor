#ifndef PAINTER_H
#define PAINTER_H

#include<QWidget>
#include<QPainter>
#include<QVector2D>
#include<QtCore/qmath.h>
class ArrowWidget : public QWidget
{
public:
    ArrowWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFixedSize(400, 400);
        m_startPoint = QPointF(100, 100);
        m_endPoint = QPointF(300, 300);
    }

    void setStartPoint(const QPointF &point)
    {
        m_startPoint = point;
        update();
    }

    void setEndPoint(const QPointF &point)
    {
        m_endPoint = point;
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);



        // 绘制箭头的线段
        painter.drawLine(m_startPoint, m_endPoint);

        const qreal arrowSize = 10;
        QPointF direction = m_endPoint - m_startPoint;
        direction /= qMax(1.0, qSqrt(direction.x() * direction.x() + direction.y() * direction.y())); // 归一化
        QPointF arrowP1 = m_endPoint - direction * arrowSize + QPointF(direction.y(), -direction.x()) * arrowSize / 2.0;
        QPointF arrowP2 = m_endPoint - direction * arrowSize + QPointF(-direction.y(), direction.x()) * arrowSize / 2.0;
        painter.drawLine(m_endPoint, arrowP1);
        painter.drawLine(m_endPoint, arrowP2);

    }

private:
    QPointF m_startPoint;
    QPointF m_endPoint;
};

#endif // PAINTER_H
