 /****************************************************************************
 **
 ** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
 **     the names of its contributors may be used to endorse or promote
 **     products derived from this software without specific prior written
 **     permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 #include <QtGui>

 #include "circlewidget.h"

 #include <stdlib.h>

 CircleWidget::CircleWidget(QWidget *parent)
     : QWidget(parent)
 {
     floatBased = false;
     antialiased = false;
     frameNo = 0;

     setBackgroundRole(QPalette::Base);
     setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 }

 void CircleWidget::setFloatBased(bool floatBased)
 {
     this->floatBased = floatBased;
     update();
 }

 void CircleWidget::setAntialiased(bool antialiased)
 {
     this->antialiased = antialiased;
     update();
 }

 QSize CircleWidget::minimumSizeHint() const
 {
     return QSize(50, 50);
 }

 QSize CircleWidget::sizeHint() const
 {
     return QSize(180, 180);
 }

 void CircleWidget::nextAnimationFrame()
 {
     ++frameNo;
     update();
 }

 void CircleWidget::setColor(QColor value) {
    color = value;
 }

 void CircleWidget::paintEvent(QPaintEvent *)
 {
     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing, antialiased);
     painter.translate(width() / 2, height() / 2);

     for (int diameter = 0; diameter < 256; diameter += 9) {
         int delta = abs((frameNo % 128) - diameter / 2);
         int alpha = 255 - (delta * delta) / 4 - diameter;
         if (alpha > 0) {
             painter.setBrush(QBrush(color));

             if (floatBased) {
                 painter.drawEllipse(QRectF(-diameter / 2.0, -diameter / 2.0,
                                            diameter, diameter));
             } else {
                 painter.drawEllipse(QRect(-diameter / 2, -diameter / 2,
                                           diameter, diameter));
             }
         }
     }
 }
