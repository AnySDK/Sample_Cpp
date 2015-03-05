//
//  ViewController.m
//  sample
//
//  Created by cocos2dx on 14-10-29.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#import "ViewController.h"
#import "AgentManager.h"
#import "PartViews.h"
#import "BButton.h"

#import "Toast.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    //add six systems buttons.
    [self addBaseButtons];
    
    _parts = [PartViews getInstance:self];
    [_parts initAgent];
}

static NSString* base_menu[] = {@"User System", @"IAP System", @"Share System", @"Ads System", @"Social System", @"Push System", @"Analytics System"};

static int g_testCount = sizeof(base_menu) / sizeof(base_menu[0]);

static PartViews* _parts = nil;
static UIView* base_part = nil;

static UIButton* baseBtns[BASE_SYSTEM_COUNT];

static CGSize button_size;

- (void)addBaseButtons
{
    CGRect rx = [[UIScreen mainScreen] bounds];
    
    CGSize _viewSize = [self.view frame].size;
    if (_viewSize.width > _viewSize.height) {
        [PartViews setBaseFullscreenY:0];
    }
    
    float origin_x = 0.0f;
    float origin_y = [PartViews getBaseFullscreenY];
    float default_w = rx.size.width;
    float default_h = 40.0f;
    float space = 0.5f;
    if (default_h > rx.size.height/10) {
        default_h = rx.size.height/10;
    }
    button_size = CGSizeMake(default_w, default_h);
    
    base_part = [[UIView alloc] init];
    [[self view] addSubview:base_part];
    
    for (int i=0; i<g_testCount; i++) {
        id btn = [self addOneButton:(i+1) title:base_menu[i] sel:@selector(onClick:) rect:CGRectMake(origin_x, origin_y + (space+default_h)*i, default_w, default_h)];
        baseBtns[i] = btn;
    }
}

+(CGSize)getButtonSize
{
    return button_size;
}

-(void)showToast:(NSString*)content
{
    [self.view makeToast:content];
}

static UIView* _curDialog = nil;

- (void)addDebugView:(NSString *)title ctx:(NSString *)content
{
    [self hideCurDialog];
    _curDialog = [self getDialogView:title content:content];
    
    [self.view addSubview:_curDialog];
}
-(UIView*)getDialogView:(NSString*)title content:(NSString*)content
{
    CGRect rect = [self.view bounds];
    CGSize size = CGSizeMake(200, 150);
    float v_x = (rect.size.width - size.width)/2;
    float v_y = (rect.size.height - size.height)/2;
    
    UIView* view = [[UIView alloc] initWithFrame:(CGRectMake(v_x, v_y, size.width, size.height))];
    view.backgroundColor = [UIColor darkGrayColor];
    
    UIButton* btnHead = [[UIButton alloc] initWithFrame:(CGRectMake(0, 0, 200, 40))];
    [view addSubview:btnHead];
    btnHead.backgroundColor = [UIColor lightGrayColor];
    [btnHead setTitle:title forState:UIControlStateNormal];
    
    UILabel* lbContent = [[UILabel alloc] initWithFrame:CGRectMake(10, 50, 180, 40)];
    [lbContent setText:content];
    [lbContent setTextColor:[UIColor whiteColor]];
    [view addSubview:lbContent];
    
    UIButton* btnOk = [[UIButton alloc] initWithFrame:(CGRectMake(70, 110, 60, 40))];
    [btnOk setTitle:@"OK" forState:UIControlStateNormal];
    [btnOk setTitleColor:[UIColor brownColor] forState:UIControlStateSelected];
    btnOk.backgroundColor = [UIColor lightTextColor];
    [view addSubview:btnOk];
    [btnOk addTarget:self action:@selector(hideCurDialog) forControlEvents:(UIControlEventTouchUpInside)];
    
    return view;
}
-(void)hideCurDialog
{
    if (nil != _curDialog) {
        [_curDialog removeFromSuperview];
        _curDialog = nil;
    }
}

- (id)addOneButton:(int)idx title:(NSString*)title sel:(SEL)sel rect:(CGRect)rect
{
    BButton* btn = [[BButton alloc] initWithFrame:rect type:BButtonTypeFacebook];
//    UIButton* btn = [[UIButton alloc] initWithFrame:rect];
    [btn setTitle:title forState:(UIControlStateNormal)];
    [btn setTag:idx];
    [btn addTarget:self action:sel forControlEvents:UIControlEventTouchDown];
//    btn.backgroundColor = [UIColor grayColor];
    [[self view] addSubview:btn];
    return btn;
}

-(void)onClick:(id)obj
{
    int idx = [obj tag];
    [self hideBaseBtns];
    [_parts switchView:idx];
}

-(void)hideBaseBtns
{
    for (int i=0; i<BASE_SYSTEM_COUNT; i++) {
        [baseBtns[i] setHidden:true];
    }
}

-(void)showBaseBtns
{
    for (int i=0; i<BASE_SYSTEM_COUNT; i++) {
        [baseBtns[i] setHidden:false];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
