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
    rl->addWidget(new ResponsiveLabel(kShoppingBasket));
    rl->addWidget(new ResponsiveLabel(kPromoBanner));
    rl->addWidget(new ResponsiveLabel(kHelp));

    // searchBar
    rl->addWidget(new ResponsiveLabel(kSearchText));
    rl->addWidget(new ResponsiveLabel(kSearchButton));
    rl->addWidget(new ResponsiveLabel(kSearchOptions));

    // results
    for (int i = 0; i < 17; i++){
        rl->addWidget(new ResponsiveLabel(kSearchResult));
    }

    // buttun
    rl->addWidget(new ResponsiveLabel(kSearchForward));
    rl->addWidget(new ResponsiveLabel(kSearchBackward));

    setLayout(rl);
}
