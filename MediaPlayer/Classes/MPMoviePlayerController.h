//
//  MPMoviewPlayerController.h
//  MediaPlayer
//
//  Created by Michael Dales on 08/07/2011.
//  Copyright 2011 Digital Flapjack Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MPMediaPlayback.h"

#import <QTKit/QTKit.h>

enum {
    MPMovieLoadStateUnknown        = 0,
    MPMovieLoadStatePlayable       = 1 << 0,
    MPMovieLoadStatePlaythroughOK  = 1 << 1,
    MPMovieLoadStateStalled        = 1 << 2,
};
typedef NSInteger MPMovieLoadState;

enum {
    MPMovieControlStyleNone,
    MPMovieControlStyleEmbedded,
    MPMovieControlStyleFullscreen,
    MPMovieControlStyleDefault = MPMovieControlStyleFullscreen
};
typedef NSInteger MPMovieControlStyle;

enum {
    MPMovieFinishReasonPlaybackEnded,
    MPMovieFinishReasonPlaybackError,
    MPMovieFinishReasonUserExited
};
typedef NSInteger MPMovieFinishReason;

enum {
    MPMovieSourceTypeUnknown,
    MPMovieSourceTypeFile,
    MPMovieSourceTypeStreaming
};
typedef NSInteger MPMovieSourceType;

enum {
    MPMovieRepeatModeNone,
    MPMovieRepeatModeOne
};
typedef NSInteger MPMovieRepeatMode;

enum {
    MPMoviePlaybackStateStopped,
    MPMoviePlaybackStatePlaying,
    MPMoviePlaybackStatePaused,
    MPMoviePlaybackStateInterrupted,
    MPMoviePlaybackStateSeekingForward,
    MPMoviePlaybackStateSeekingBackward
};
typedef NSInteger MPMoviePlaybackState;


typedef enum {
    MPMovieScalingModeNone,
    MPMovieScalingModeAspectFit,
    MPMovieScalingModeAspectFill,
    MPMovieScalingModeFill
} MPMovieScalingMode;

extern NSString *const MPMoviePlayerPlaybackDidFinishReasonUserInfoKey;

// notifications
extern NSString *const MPMoviePlayerPlaybackStateDidChangeNotification;
extern NSString *const MPMoviePlayerPlaybackDidFinishNotification;
extern NSString *const MPMoviePlayerLoadStateDidChangeNotification;
extern NSString *const MPMovieDurationAvailableNotification;

// Posted when the movie player enters or exits fullscreen mode.
extern NSString *const MPMoviePlayerWillEnterFullscreenNotification;
extern NSString *const MPMoviePlayerDidEnterFullscreenNotification;
extern NSString *const MPMoviePlayerWillExitFullscreenNotification;
extern NSString *const MPMoviePlayerDidExitFullscreenNotification;
extern NSString *const MPMoviePlayerFullscreenAnimationDurationUserInfoKey; // NSNumber of double (NSTimeInterval)
extern NSString *const MPMoviePlayerFullscreenAnimationCurveUserInfoKey;     // NSNumber of NSUInteger (UIViewAnimationCurve)

@class UIInternalMovieView;

@interface MPMoviePlayerController : NSObject <MPMediaPlayback> 
{
@private
    UIInternalMovieView *movieView;
    
    QTMovie *movie;
}
@property (nonatomic, readonly) UIView *view;
@property (nonatomic, readonly) MPMovieLoadState loadState;
@property (nonatomic, copy) NSURL *contentURL;
@property (nonatomic) MPMovieControlStyle controlStyle;
@property (nonatomic) MPMovieSourceType movieSourceType;

// A view for customization which is always displayed behind movie content.
@property(nonatomic, readonly) UIView *backgroundView;

@property (nonatomic, readonly) MPMoviePlaybackState playbackState;
@property (nonatomic) MPMovieRepeatMode repeatMode;

// Indicates if a movie should automatically start playback when it is likely to finish uninterrupted based on e.g. network conditions. Defaults to YES.
@property(nonatomic) BOOL shouldAutoplay;

@property (nonatomic, readonly) NSTimeInterval duration;
@property (nonatomic) MPMovieScalingMode scalingMode;


// Determines if the movie is presented in the entire screen (obscuring all other application content). Default is NO.
// Setting this property to YES before the movie player's view is visible will have no effect.
@property(nonatomic, getter=isFullscreen) BOOL fullscreen;
- (void)setFullscreen:(BOOL)fullscreen animated:(BOOL)animated;

- (id)initWithContentURL: (NSURL*)url;


@end

// -----------------------------------------------------------------------------
// Thumbnails

enum {
    MPMovieTimeOptionNearestKeyFrame,
    MPMovieTimeOptionExact
};
typedef NSInteger MPMovieTimeOption;

@interface MPMoviePlayerController (MPMoviePlayerThumbnailGeneration)

// Returns a thumbnail at the given time.
// Deprecated.  Use -requestThumbnailImagesAtTimes:timeOption: / MPMoviePlayerThumbnailImageRequestDidFinishNotification instead.
- (UIImage *)thumbnailImageAtTime:(NSTimeInterval)playbackTime timeOption:(MPMovieTimeOption)option; // NS_DEPRECATED_IOS(3_2, 7_0);

// Asynchronously request thumbnails for one or more times, provided as an array of NSNumbers (double).
// Posts MPMoviePlayerThumbnailImageRequestDidFinishNotification on completion.
- (void)requestThumbnailImagesAtTimes:(NSArray *)playbackTimes timeOption:(MPMovieTimeOption)option NS_AVAILABLE_IOS(3_2);

// Cancels all pending asynchronous thumbnail requests.
- (void)cancelAllThumbnailImageRequests NS_AVAILABLE_IOS(3_2);

@end
