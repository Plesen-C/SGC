#include "HUDWidget.h"

#include "canvas.h"
#include "GraphicObject.h"
#include "RectangleObject.h"
#include "LineObject.h"

#include <QPainter>
#include <QFont>

HUDWidget::HUDWidget(Canvas *canvas, QWidget *parent)
    : QWidget(parent),
      canvas(canvas)
{
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_TranslucentBackground);
}

void HUDWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (!canvas)
        return;

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, false);

    QFont font("DejaVu Sans Mono");
    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(12);

    painter.setFont(font);
    painter.setPen(QColor(210, 210, 210));

    const int margin = 10;
    const int leftWidth = 400;
    const int topHeight = 70;
    const int bottomHeight = 58;

    const int right = width() - margin;
    const int bottom = height() - margin;

    /*
     * ─────────────────────────────────────────────
     * HEADER
     * ─────────────────────────────────────────────
     */

    painter.drawText(
        margin,
        margin + 12,
        QString("┌─ SGC :: SCENE GRAPHIC CONSOLE ")
    );

    painter.drawText(
        right - 95,
        margin + 12,
        "[ ONLINE ] ┐"
    );

    painter.drawLine(
        margin,
        margin + 18,
        right,
        margin + 18
    );

    painter.drawText(
        margin + 2,
        margin + 36,
        "│ MODE: SELECT"
    );

    painter.drawText(
        right - 170,
        margin + 36,
        "INPUT: KEYBOARD+ MOUSE│"
    );

    /*
     * ─────────────────────────────────────────────
     * OBJECTS PANEL
     * ─────────────────────────────────────────────
     */

    const int objectsTop = margin + topHeight;
    const int objectsBottom = bottom - bottomHeight;

    painter.drawText(
        margin,
        objectsTop,
        "┌─ OBJECTS"
    );

    painter.drawText(
        margin + leftWidth - 70,
        objectsTop,
        "COUNT:"
    );

    painter.drawText(
        margin + leftWidth - 25,
        objectsTop,
        QString::number(canvas->objectCount())
    );

    painter.drawLine(
        margin,
        objectsTop + 7,
        margin + leftWidth,
        objectsTop + 7
    );

    const int selectedIndex = canvas->selectedObjectIndex();

    int y = objectsTop + 25;

    for (int i = canvas->objectCount() - 1; i >= 0; --i)
    {
        if (y > objectsBottom - 20)
            break;

        GraphicObject *object = canvas->objectAt(i);

        if (!object)
            continue;

        const bool selected = (i == selectedIndex);
        const bool hovered = (i == hoveredAction);

        QString type;

        if (dynamic_cast<RectangleObject*>(object))
            type = "▣ RECTANGLE";
        else if (dynamic_cast<LineObject*>(object))
            type = "─ LINE";
        else
            type = "? OBJECT";

        QString marker;

        if (selected)
            marker = ">";
        else if (hovered)
            marker = "~";
        else
            marker = " ";

        painter.drawText(
            margin + 8,
            y,
            QString("│ %1 [%2] %3")
                .arg(marker)
                .arg(i, 3, 10, QChar('0'))
                .arg(type)
        );

        y += 16;
    }

    painter.drawLine(
        margin,
        objectsBottom,
        margin + leftWidth,
        objectsBottom
    );

    painter.drawText(
        margin,
        objectsBottom + 15,
        "└──────────────────────────────"
    );
    /*
     * ─────────────────────────────────────────────
     * STATUS BAR
     * ─────────────────────────────────────────────
     */

    const int statusY = bottom - bottomHeight + 8;

    painter.drawLine(
        margin,
        statusY,
        right,
        statusY
    );

    QString selectedText = "-";

    if (selectedIndex >= 0)
    {
        GraphicObject *selected =
            canvas->objectAt(selectedIndex);

        if (selected)
        {
            if (dynamic_cast<RectangleObject*>(selected))
                selectedText = "RECTANGLE";
            else if (dynamic_cast<LineObject*>(selected))
                selectedText = "LINE";
            else
                selectedText = "OBJECT";
        }
    }

    painter.drawText(
        margin,
        statusY + 18,
        QString("│ OBJECTS: %1")
            .arg(canvas->objectCount())
    );

    painter.drawText(
        margin + 150,
        statusY + 18,
        QString("SELECTED: %1")
            .arg(selectedIndex >= 0
                     ? QString::number(selectedIndex)
                     : "-")
    );

    painter.drawText(
        margin + 300,
        statusY + 18,
        QString("TYPE: %1")
            .arg(selectedText)
    );

    painter.drawText(
        margin,
        statusY + 36,
        "│ [LMB] SELECT   [RMB] PAN/MENU   [DEL] DELETE   [↑↓] OBJECT   [ESC] CANCEL"
    );

    painter.drawText(
        right - 2,
        statusY + 36,
        "┘"
    );
}
void HUDWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!canvas)
        return;

    const int margin = 10;
    const int leftWidth = 400;
    const int topHeight = 70;
    const int bottomHeight = 58;

    const int objectsTop = margin + topHeight;
    const int objectsBottom = height() - margin - bottomHeight;

    const QPoint position = event->position().toPoint();

    int newHoveredAction = -1;

    int y = objectsTop + 25;

    for (int i = canvas->objectCount() - 1; i >= 0; --i)
    {
        if (y > objectsBottom - 20)
            break;

        QRect itemRect(
            margin,
            y - 14,
            leftWidth,
            16
        );

        if (itemRect.contains(position))
        {
            newHoveredAction = i;
            break;
        }

        y += 16;
    }

    if (hoveredAction != newHoveredAction)
    {
        hoveredAction = newHoveredAction;
        update();
    }
}
void HUDWidget::mousePressEvent(QMouseEvent *event)
{
    if (!canvas)
        return;

    if (event->button() != Qt::LeftButton)
        return;

    if (hoveredAction >= 0 &&
        hoveredAction < canvas->objectCount())
    {
        canvas->selectObject(hoveredAction);
        update();
    }
}

void HUDWidget::keyPressEvent(QKeyEvent *event)
{
    if(!canvas)
        return;
    switch (event->key()){
        case Qt::Key_N:
            const QPoint position(
                canvas->width() / 2,
                canvas->height() / 2
            );
            canvas->createRectangle(position);
            update();
            break;
    }




}