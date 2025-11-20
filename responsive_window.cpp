//
// Created by twak on 14/10/2019.
//

#include "responsive_window.h"
#include "responsive_layout.h"
#include "responsive_label.h"
#include "screenshot.h"
#include <iostream>
#include <QApplication>
#include <QLabel>

ResponsiveWindow::ResponsiveWindow() {

    setWindowTitle("2811: Coursework 1");
    setMinimumSize(320, 320);
    setMaximumSize(1280, 720);

    createWidgets();
}

void ResponsiveWindow::createWidgets() {

    ResponsiveLayout *rl = new ResponsiveLayout();

    // top nevigation
    rl->addWidget(new ResponsiveLabel(kHomeLink));
    rl->addWidget(new ResponsiveLabel(kNavTabs));
    rl->addWidget(new ResponsiveLabel(kSignIn));
    rl->addWidget(new ResponsiveLabel(kProfile));
    rl->addWidget(new ResponsiveLabel(kShoppingBasket));
    rl->addWidget(new ResponsiveLabel(kWishlist));
    rl->addWidget(new ResponsiveLabel(kNotification));
    rl->addWidget(new ResponsiveLabel(kPromoBanner));
    rl->addWidget(new ResponsiveLabel(kHelp));

    // breadcrumbs for quick context
    rl->addWidget(new ResponsiveLabel(kBreadcrumbs));

    // searchBar
    rl->addWidget(new ResponsiveLabel(kSearchText));
    rl->addWidget(new ResponsiveLabel(kSearchButton));
    rl->addWidget(new ResponsiveLabel(kSearchOptions));
    rl->addWidget(new ResponsiveLabel(kSortSelector));
    rl->addWidget(new ResponsiveLabel(kViewToggle));

    // filter ribbon
    rl->addWidget(new ResponsiveLabel(kCategoryFilter));
    rl->addWidget(new ResponsiveLabel(kPriceFilter));
    rl->addWidget(new ResponsiveLabel(kRatingFilter));

    // result overview
    rl->addWidget(new ResponsiveLabel(kResultSummary));

    // results
    for (int i = 0; i < 17; i++){
        rl->addWidget(new ResponsiveLabel(kSearchResult));
    }

    // buttun
    rl->addWidget(new ResponsiveLabel(kSearchForward));
    rl->addWidget(new ResponsiveLabel(kSearchBackward));

    setLayout(rl);
}
