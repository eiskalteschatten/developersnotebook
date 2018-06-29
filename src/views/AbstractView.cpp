#include <ctime>
#include <sstream>
#include <iomanip>

#include "AbstractView.hpp"
#include "../constants.hpp"

AbstractView::AbstractView() {}

AbstractView::AbstractView(GtkWidget *window) {
    main_window = window;
}

AbstractView::~AbstractView() {
    g_free(main_window);
    g_free(main_widget);
}

gint AbstractView::sort_by_string(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data) {
    gint ret = 0;
    gchar *string1;
    gchar *string2;
    gint sortcol = GPOINTER_TO_INT(user_data);

    gtk_tree_model_get(model, a, sortcol, &string1, -1);
    gtk_tree_model_get(model, b, sortcol, &string2, -1);

    if (
        (string1 == NULL || string2 == NULL) &&
        !(string1 == NULL && string2 == NULL)
    ) {
        ret = (string1 == NULL) ? -1 : 1;
    }
    else if (!(string1 == NULL && string2 == NULL)) {
        ret = g_utf8_collate(string1, string2);
    }

    g_free(string1);
    g_free(string2);

    return ret;
}

gint AbstractView::sort_by_boolean(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data) {
    gboolean bool1;
    gboolean bool2;
    gint sortcol = GPOINTER_TO_INT(user_data);

    gtk_tree_model_get(model, a, sortcol, &bool1, -1);
    gtk_tree_model_get(model, b, sortcol, &bool2, -1);

    if (!bool1 && bool2) {
        return -1;
    }
    else if (bool1 && !bool2) {
        return 1;
    }

    return 0;
}

gint AbstractView::sort_by_date(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data) {
    gchar *string_char1;
    gchar *string_char2;
    gint sortcol = GPOINTER_TO_INT(user_data);

    gtk_tree_model_get(model, a, sortcol, &string_char1, -1);
    gtk_tree_model_get(model, b, sortcol, &string_char2, -1);

    std::string string1 = std::string(string_char1);
    std::string string2 = std::string(string_char2);

    g_free(string_char1);
    g_free(string_char2);

    std::tm tm1 = get_date_from_string(&string1);
    std::tm tm2 = get_date_from_string(&string2);

    return difftime(mktime(&tm1), mktime(&tm2)) < 0 ? -1 : 1;
}

std::string AbstractView::format_date(const guint *year, const guint *month, const guint *day) {
    std::tm date_tm = {};

    date_tm.tm_year = *year - 1900;
    date_tm.tm_mon  = *month;
    date_tm.tm_mday = *day;

    std::time_t time_temp   = std::mktime(&date_tm);
    const std::tm *time_out = std::localtime(&time_temp);

    return format_date(time_out);
}

std::string AbstractView::format_date(const std::tm *date_tm) {
    std::stringstream ss;
    ss << std::put_time(date_tm, Constants::default_date_format.c_str());
    return ss.str();
}

std::string AbstractView::format_date_time(const std::tm *date_tm) {
    std::stringstream ss;
    ss << std::put_time(date_tm, Constants::default_date_time_format.c_str());
    return ss.str();
}

std::tm AbstractView::get_date_from_string(std::string *date_str) {
    std::tm date_tm = {};
    std::stringstream ss(*date_str);
    ss >> std::get_time(&date_tm, Constants::default_date_format.c_str());
    return date_tm;
}

void AbstractView::reset_calender(GtkWidget *calendar) {
    auto now               = std::time(nullptr);
    struct std::tm *now_tm = std::localtime(&now);
    guint year             = now_tm->tm_year + 1900;

    gtk_calendar_select_month(GTK_CALENDAR(calendar), now_tm->tm_mon, year);
    gtk_calendar_select_day(GTK_CALENDAR(calendar), now_tm->tm_mday);

    gtk_calendar_select_day(GTK_CALENDAR(calendar), 0);
}
