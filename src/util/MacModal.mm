#import <string>

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#import "MacModal.h"

@implementation MacModal

void mac_show_error_modal(std::string message, std::string sub_message) {
    NSString *ns_message     = [NSString stringWithCString:message.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *ns_sub_message = [NSString stringWithCString:sub_message.c_str() encoding:[NSString defaultCStringEncoding]];

    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle:@"OK"];
    [alert setMessageText:ns_message];
    [alert setInformativeText:ns_sub_message];
    [alert setAlertStyle:NSAlertStyleCritical];
    [alert runModal];
}

@end
