//
//  ViewController.h
//  sample
//
//  Created by cocos2dx on 14-10-29.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

-(void)onClick:(id)obj;
-(void)showBaseBtns;
+(CGSize)getButtonSize;
-(void)addDebugView:(NSString*)title ctx:(NSString*)content;
-(void)showToast:(NSString*)content;
@end

