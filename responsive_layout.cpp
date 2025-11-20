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
    const int crumbH  = (mode == Compact) ? ((H/20 > 28) ? H/20 : 28) : (H/18);
    const int searchH = (mode == Compact) ? ((H/12 > 40) ? H/12 : 40) : (H/12);
    const int filterH = (mode == Compact) ? ((H/14 > 32) ? H/14 : 32) : (H/14);
    const int summaryH = (mode == Compact) ? ((H/16 > 30) ? H/16 : 30) : (H/16);

    // devide the region to topBar, breadcrumbs, searchBar, filterBar, content
    const QRect topBar   (safe.x(), safe.y(), safe.width(), topH);
    const QRect crumbBar (safe.x(), topBar.bottom() + gap/2, safe.width(), crumbH);
    const QRect searchBar(safe.x(), crumbBar.bottom() + gap, safe.width(), searchH);
    const QRect filterBar(safe.x(), searchBar.bottom() + gap, safe.width(), filterH);
    const QRect summaryBar(safe.x(), filterBar.bottom() + gap, safe.width(), summaryH);
    const QRect rcBreadcrumb = crumbBar.adjusted(gap/2, 0, -gap/2, 0);
    const QRect rcSummary = summaryBar.adjusted(gap/2, 0, -gap/2, 0);
    QRect content(safe.x(), summaryBar.bottom() + gap, safe.width(),
                  safe.bottom() - (summaryBar.bottom() + gap));

    // place the left part: kHomeLink | kNavTabs | (Landscape) kPromoBanner
    int leftX  = topBar.x();
    const int leftY  = topBar.y();
    const int leftH  = topBar.height();

    const int homeW  = (safe.width()/10 > 80) ? (safe.width()/10) : 80;
    const int navW   = (safe.width()/4  > 140)? (safe.width()/4 ) : 140;
    const int promoW = (safe.width()/6  > 120)? (safe.width()/6 ) : 120;
    const int profileW = (safe.width()/18 > 70) ? (safe.width()/18) : 70;
    const int wishlistW = (safe.width()/18 > 70) ? (safe.width()/18) : 70;
    const int noticeW   = (safe.width()/20 > 60) ? (safe.width()/20) : 60;

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

    QRect rcNotice(rightX - noticeW, rightY, noticeW, rightH);
    rightX -= noticeW + gap;

    QRect rcWishlist(rightX - wishlistW, rightY, wishlistW, rightH);
    rightX -= wishlistW + gap;

    QRect rcProfile(rightX - profileW, rightY, profileW, rightH);
    rightX -= profileW + gap;

    QRect rcSign  (rightX - signW,   rightY, signW,   rightH);
    rightX -= signW   + gap;

    QRect rcHelp  (rightX - helpW,   rightY, helpW,   rightH);

    // place the search bar：kSearchText | kSearchOptions | kSearchButton
    QRect rcSText, rcSOpt, rcSBtn, rcSort, rcView;
    {
        int x = searchBar.x(), y = searchBar.y(), w = searchBar.width(), h = searchBar.height();
        if (mode == Landscape) {
            const int btnW  = (w/8  > 90) ? (w/8) : 90;
            const int optW  = (w/7  > 110)? (w/7) : 110;
            const int sortW = (w/8  > 100)? (w/8) : 100;
            const int viewW = (w/10 > 80) ? (w/10) : 80;
            const int txtW = w - btnW - optW - sortW - viewW - 4*gap;
            if (txtW > 0) {
                rcSText = QRect(x, y, txtW, h);
                rcSOpt  = QRect(x + txtW + gap, y, optW, h);
                rcSort  = QRect(rcSOpt.right() + gap, y, sortW, h);
                rcView  = QRect(rcSort.right() + gap, y, viewW, h);
                rcSBtn  = QRect(rcView.right() + gap, y, btnW, h);
            }
        } else if (mode == Portrait) {
            const int btnW = (w/6  > 90) ? (w/6) : 90;
            const int txtW = w - btnW - gap;
            rcSText = QRect(x, y, txtW, h);
            rcSBtn  = QRect(x + txtW + gap, y, btnW, h);
        } else { // Compact
            const int btnW = (w/5  > 88) ? (w/5) : 88;
            const int txtW = w - btnW - gap;
            rcSText = QRect(x, y, txtW, h);
            rcSBtn  = QRect(x + txtW + gap, y, btnW, h);
        }
    }

    // layout for filters and search refinements
    QRect rcCategory, rcPrice, rcRating;
    QRect rcOptRow = filterBar;
    QRect rcFilterRow = filterBar;
    rcOptRow.setHeight(filterBar.height()/2);
    rcFilterRow.setY(rcOptRow.bottom());
    rcFilterRow.setHeight(filterBar.height() - rcOptRow.height());

    if (mode != Landscape) {
        const int optW = (rcOptRow.width()/3 > 100) ? (rcOptRow.width()/3) : 100;
        const int sortW = (rcOptRow.width()/4 > 96) ? (rcOptRow.width()/4) : 96;
        const int viewW = (rcOptRow.width()/5 > 80) ? (rcOptRow.width()/5) : 80;
        int x = rcOptRow.x();
        rcSOpt = QRect(x, rcOptRow.y(), optW, rcOptRow.height());
        x += optW + gap;
        rcSort = QRect(x, rcOptRow.y(), sortW, rcOptRow.height());
        x += sortW + gap;
        rcView = QRect(x, rcOptRow.y(), viewW, rcOptRow.height());
    }

    {
        const int chipW = (rcFilterRow.width()/4 > 110) ? (rcFilterRow.width()/4) : 110;
        int x = rcFilterRow.x();
        rcCategory = QRect(x, rcFilterRow.y(), chipW, rcFilterRow.height());
        x += chipW + gap;
        rcPrice = QRect(x, rcFilterRow.y(), chipW, rcFilterRow.height());
        x += chipW + gap;
        rcRating = QRect(x, rcFilterRow.y(), chipW, rcFilterRow.height());
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
            else if (name == kProfile) {
                if (mode != Compact) label->setGeometry(rcProfile);
                else                  label->setGeometry(-1,-1,0,0);
            }
            else if (name == kWishlist) {
                if (mode != Compact) label->setGeometry(rcWishlist);
                else                  label->setGeometry(-1,-1,0,0);
            }
            else if (name == kNotification) {
                if (mode != Compact) label->setGeometry(rcNotice);
                else                  label->setGeometry(-1,-1,0,0);
            }
            else if (name == kShoppingBasket) {
                label->setGeometry(rcBasket);
            }

            // context
            else if (name == kBreadcrumbs) {
                label->setGeometry(rcBreadcrumb);
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
            else if (name == kSortSelector) {
                if (rcSort.width() > 0) label->setGeometry(rcSort);
                else                    label->setGeometry(-1,-1,0,0);
            }
            else if (name == kViewToggle) {
                if (rcView.width() > 0) label->setGeometry(rcView);
                else                    label->setGeometry(-1,-1,0,0);
            }

            // filters
            else if (name == kCategoryFilter) {
                if (rcCategory.width() > 0) label->setGeometry(rcCategory);
                else                        label->setGeometry(-1,-1,0,0);
            }
            else if (name == kPriceFilter) {
                if (rcPrice.width() > 0) label->setGeometry(rcPrice);
                else                      label->setGeometry(-1,-1,0,0);
            }
            else if (name == kRatingFilter) {
                if (rcRating.width() > 0) label->setGeometry(rcRating);
                else                       label->setGeometry(-1,-1,0,0);
            }

            // summary bar
            else if (name == kResultSummary) {
                label->setGeometry(rcSummary);
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
