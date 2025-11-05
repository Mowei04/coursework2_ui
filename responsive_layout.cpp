//
// Created by twak on 07/10/2019.
//

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>

//using namespace std;

// you should probably make extensive changes to this function
void ResponsiveLayout::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {

    QLayout::setGeometry(r);

    const int W = r.width();
    const int H = r.height();

    // set the responsive margin and gap
    const int margin = (W/64 > 8) ? (W/64) : 8;
    const int gap    = (W/96 > 6) ? (W/96) : 6;
    const QRect safe = r.adjusted(margin, margin, -margin, -margin);

    // three modes
    enum Mode { Compact, Portrait, Landscape };
    Mode mode;
    if (W < 380 || H < 380) mode = Compact;
    else if (W < H)         mode = Portrait;
    else                    mode = Landscape;

    // calculate the responsive top line and search line
    const int topH    = (mode == Compact) ? ((H/10 > 44) ? H/10 : 44) : (H/10);
    const int searchH = (mode == Compact) ? ((H/12 > 40) ? H/12 : 40) : (H/12);

    // devide the region to topBar,searchBar,content
    const QRect topBar   (safe.x(), safe.y(), safe.width(), topH);
    const QRect searchBar(safe.x(), topBar.bottom() + gap, safe.width(), searchH);
    QRect content(safe.x(), searchBar.bottom() + gap, safe.width(),
                  safe.bottom() - (searchBar.bottom() + gap));

    // place the left part: kHomeLink | kNavTabs | (Landscape) kPromoBanner
    int leftX  = topBar.x();
    const int leftY  = topBar.y();
    const int leftH  = topBar.height();

    const int homeW  = (safe.width()/10 > 80) ? (safe.width()/10) : 80;
    const int navW   = (safe.width()/4  > 140)? (safe.width()/4 ) : 140;
    const int promoW = (safe.width()/6  > 120)? (safe.width()/6 ) : 120;

    QRect rcHome (leftX, leftY, homeW, leftH);
    leftX += homeW + gap;

    QRect rcNav  (leftX, leftY, navW,  leftH);
    leftX += navW  + gap;

    QRect rcPromo(leftX, leftY, promoW, leftH);

    // place the left part: kHelp | kSignIn | kShoppingBasket
    int rightX = topBar.right();
    const int rightY = topBar.y();
    const int rightH = topBar.height();
    const int helpW   = (safe.width()/16 > 60) ? (safe.width()/16) : 60;
    const int signW   = (safe.width()/12 > 80) ? (safe.width()/12) : 80;
    const int basketW = (safe.width()/14 > 60) ? (safe.width()/14) : 60;

    QRect rcBasket(rightX - basketW, rightY, basketW, rightH);
    rightX -= basketW + gap;

    QRect rcSign  (rightX - signW,   rightY, signW,   rightH);
    rightX -= signW   + gap;

    QRect rcHelp  (rightX - helpW,   rightY, helpW,   rightH);

    // place the search bar：kSearchText | kSearchOptions | kSearchButton
    QRect rcSText, rcSOpt, rcSBtn;
    {
        int x = searchBar.x(), y = searchBar.y(), w = searchBar.width(), h = searchBar.height();
        if (mode == Landscape) {
            const int btnW = (w/8  > 90) ? (w/8) : 90;
            const int optW = (w/6  > 120)? (w/6) : 120;
            const int txtW = w - btnW - optW - 2*gap;
            if (txtW > 0) {
                rcSText = QRect(x, y, txtW, h);
                rcSOpt  = QRect(x + txtW + gap, y, optW, h);
                rcSBtn  = QRect(x + txtW + gap + optW + gap, y, btnW, h);
            }
        } else if (mode == Portrait) {
            const int btnW = (w/6  > 90) ? (w/6) : 90;
            const int txtW = w - btnW - gap;
            rcSText = QRect(x, y, txtW, h);
            rcSBtn  = QRect(x + txtW + gap, y, btnW, h);

            //the option move to next line and place the content part
            const int optH = (h/2 > 24) ? (h/2) : 24;
            rcSOpt = QRect(safe.x(), searchBar.bottom() + gap/2, safe.width(), optH);
            content.setTop(rcSOpt.bottom() + gap);
        } else { // Compact
            const int btnW = (w/5  > 88) ? (w/5) : 88;
            const int txtW = w - btnW - gap;
            rcSText = QRect(x, y, txtW, h);
            rcSBtn  = QRect(x + txtW + gap, y, btnW, h);
        }
    }

    // calculate the results locations
    int cols;
    if (mode == Landscape)      cols = (safe.width()/220 < 3) ? 3 : ((safe.width()/220 > 6) ? 6 : safe.width()/220);
    else if (mode == Portrait)  cols = (safe.width()/220 < 2) ? 2 : ((safe.width()/220 > 3) ? 3 : safe.width()/220);
    else                        cols = (safe.width()/240 < 1) ? 1 : ((safe.width()/240 > 2) ? 2 : safe.width()/240);

    const int gridMargin = gap;
    const int innerW = content.width() - 2*gridMargin;
    const int cell   = (cols > 0) ? (innerW - (cols - 1)*gap) / cols : innerW;
    const int x0     = content.x() + gridMargin;
    const int y0     = content.y() + gridMargin;

    //place the
    int resultIndex = 0;

    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);
        try {
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());

            if (label == NULL) {
                std::cout << "warning, unknown widget class in layout" << std::endl;
                continue;
            }

            const QString name = label->text();

            // place topBar
            if (name == kHomeLink) {
                label->setGeometry(rcHome);
            }
            else if (name == kNavTabs) {
                if (mode != Compact) label->setGeometry(rcNav);
                else                 label->setGeometry(-1,-1,0,0);
            }
            else if (name == kPromoBanner) {
                if (mode == Landscape) label->setGeometry(rcPromo);
                else                    label->setGeometry(-1,-1,0,0);
            }
            else if (name == kHelp) {
                if (mode != Compact) label->setGeometry(rcHelp);
                else                  label->setGeometry(-1,-1,0,0);
            }
            else if (name == kSignIn) {
                label->setGeometry(rcSign);
            }
            else if (name == kShoppingBasket) {
                label->setGeometry(rcBasket);
            }

            // palce searchBar
            else if (name == kSearchText) {
                if (rcSText.width() > 0) label->setGeometry(rcSText);
                else                     label->setGeometry(-1,-1,0,0);
            }
            else if (name == kSearchOptions) {
                if (rcSOpt.width() > 0) label->setGeometry(rcSOpt);
                else                    label->setGeometry(-1,-1,0,0);
            }
            else if (name == kSearchButton) {
                if (rcSBtn.width() > 0) label->setGeometry(rcSBtn);
                else                    label->setGeometry(-1,-1,0,0);
            }

            // place the resuolt bar
            else if (name == kSearchResult) {
                if (cell > 0 && cols > 0) {
                    int row = resultIndex / cols;
                    int col = resultIndex % cols;
                    int x = x0 + col * (cell + gap);
                    int y = y0 + row * (cell + gap);
                    label->setGeometry(x, y, cell, cell);
                    resultIndex++;
                } else {
                    label->setGeometry(-1,-1,0,0);
                }
            }

            // put the buttun to the right end of the page
            else if (name == kSearchForward || name == kSearchBackward) {
                const int btnH = ((searchH - 8) > 28) ? (searchH - 8) : 28;
                const int btnW = (safe.width()/12 > 64) ? (safe.width()/12) : 64;
                int bx = content.right() - btnW;
                int by = content.bottom() - btnH;
                if (name == kSearchBackward) bx -= (btnW + gap);
                label->setGeometry(bx, by, btnW, btnH);
            }

            // hide other part
            else {
                label->setGeometry(-1,-1,0,0);
            }
        }
        catch (std::bad_cast) {
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
