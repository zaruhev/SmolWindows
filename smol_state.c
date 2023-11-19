#include "smol.h"

bool SmolContextShouldClose(WndCtx *ctx) {
    return !GetMessage(&ctx->mState__EventMsg, NULL, 0, 0);
}

#define RectResolutionEquals(rect1, rect2) (rect1.bottom - rect1.top == rect2.bottom - rect2.top\
                                && rect1.right - rect1.left == rect2.right - rect2.left)
#define RectResolutionHorizontal(rect) (rect.right - rect.left)
#define RectResolutionVertical(rect) (rect.bottom - rect.top)

/// Dev note: Determines whether to call the OnClientSizeUpdated event callback.
static inline void Smol__CheckOnClientSizeUpdated(WndCtx* ctx) {
    RECT rect;
    GetClientRect(ctx->handle, &rect);
    if (!RectResolutionEquals(ctx->mState__ClientSize, rect)) {
        ctx->mClientSizeUpdatedCallback(ctx,
            RectResolutionHorizontal(rect),
            RectResolutionVertical(rect));
        ctx->mState__ClientSize = rect;
    }
}

void SmolHandleEvents(WndCtx *ctx) {
    TranslateMessage(&ctx->mState__EventMsg);
    DispatchMessage(&ctx->mState__EventMsg);

    // TODO: We do not want to run every single callback every single frame. Find a way to snapshot the state and compare.
    if (ctx->mClientSizeUpdatedCallback) Smol__CheckOnClientSizeUpdated(ctx);
}