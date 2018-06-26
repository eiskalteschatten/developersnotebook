#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#import "MacWindowManager.h"

@implementation MacWindowManager

void mac_close_active_window() {
    NSWindow *window = [[NSApplication sharedApplication] keyWindow];
    [window close];
}

@end
