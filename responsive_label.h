//
// Created by twak on 14/10/2019.
//

#ifndef RESPONSIVELABEL_H
#define RESPONSIVELABEL_H


#include <QLabel>
#include <QString>
#include <map>

//using namespace std;

// Please add to, but DO NOT modify the existing constants in this file.
// label names that are displayed
const QString
        kHomeLink       = "home",
        kShoppingBasket = "basket",
        kSignIn         = "sign-in",
        kNavTabs        = "navigation tabs",
        kAdvert         = "advert",
        kSearchButton   = "search",
        kSearchResult   = "result",
        kSearchText     = "search query",
        kSearchForward  = ">",
        kSearchBackward = "<",
        kSearchOptions  = "search options",
        kPromoBanner = "promotion banner",
        kHelp = "help",
        kProfile = "profile",
        kWishlist = "wishlist",
        kNotification = "notification",
        kBreadcrumbs = "breadcrumbs",
        kCategoryFilter = "category",
        kPriceFilter = "price",
        kRatingFilter = "rating",
        kSortSelector = "sort",
        kViewToggle = "view",
        kResultSummary = "results";

// every label name has a colour
const std::map<QString, QString> kColours = {
        std::make_pair(kHomeLink,       "#ffaaff"),
        std::make_pair(kShoppingBasket, "#ffaaaa"),
        std::make_pair(kSignIn,         "#aaffaa"),
        std::make_pair(kNavTabs,        "#ffa9d3"),
        std::make_pair(kAdvert,         "#ffaa66"),
        std::make_pair(kSearchButton,   "#aaffff"),
        std::make_pair(kSearchResult,   "#99ddff"),
        std::make_pair(kSearchText,     "#aaaaff"),
        std::make_pair(kSearchForward,  "#5caeff"),
        std::make_pair(kSearchBackward, "#5caeff"),
        std::make_pair(kSearchOptions,  "#9dceff"),
        std::make_pair(kPromoBanner, "#D6EAF8"),
        std::make_pair(kHelp,  "#E8DAEF"),
        std::make_pair(kProfile, "#F5EEF8"),
        std::make_pair(kWishlist, "#FDEBD0"),
        std::make_pair(kNotification, "#F9E79F"),
        std::make_pair(kBreadcrumbs, "#EBDEF0"),
        std::make_pair(kCategoryFilter, "#D1F2EB"),
        std::make_pair(kPriceFilter, "#FDEDEC"),
        std::make_pair(kRatingFilter, "#FCF3CF"),
        std::make_pair(kSortSelector, "#D6EAF8"),
        std::make_pair(kViewToggle, "#E8F8F5"),
        std::make_pair(kResultSummary, "#F6F2FF")
    };

class ResponsiveLabel : public QLabel {
public:
    ResponsiveLabel(QString name) ;
    ResponsiveLabel(QString name, QString colour) ;
};


#endif // RESPONSIVELABEL_H
