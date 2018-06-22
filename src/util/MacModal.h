#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include "MacModalInterface.hpp"

@interface MacModal : NSObject

- (void)show_error_modal:(void*)message sub_message:(void*)sub_message;

@end
