#import "MacModal.h"

@implementation MacModal

void mac_show_error_modal(void *message, void *sub_message) {
    [self doSomethingWith:message sub_message:sub_message];
}

- (void)show_error_modal:(void*)message sub_message:(void*)sub_message {

}

@end
