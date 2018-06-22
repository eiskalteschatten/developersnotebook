#ifndef MacModalInterface_hpp
#define MacModalInterface_hpp

void mac_show_error_modal(std::string message, std::string sub_message);
int mac_show_confirm_modal(std::string message, std::string sub_message, std::string accept_button, std::string reject_button);

#endif
