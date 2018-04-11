#include "AbstractView.hpp"

AbstractView::~AbstractView() {
    delete main_widget;
}
