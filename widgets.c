#include "widgets.h"

DEF_WIDGET_EXTENDED(Column, TAKESCHILDREN)
DEF_WIDGET_EXTENDED(Button, DEFAULTFONT)
DEF_WIDGET_EXTENDED(Text, DEFAULTFONT)
DEF_WIDGET_EXTENDED(BuildCounter, DEFAULTFONT)

#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b

NOP_METHOD(init, Column)
NOP_METHOD(getChildren, Column)
NOP_METHOD(destroy, Column)

void handleEventColumn(RenderContext* ctx, ColumnConfig* cfg) {
    // todo: this is REALLY shaky what happened to extension composition
    EVENTPASSTHROUGH_handleEvent(Column);
}

void drawColumn(RenderContext* ctx, ColumnConfig* cfg) {
    int currentY = ctx->pos.y;
    int maxY = currentY + ctx->constrainSize.y;
    int maxXSize = 0;
    FOREACH(RenderObject*, *RC_getChildren(ctx), child) {
        if (currentY >= maxY) break;
        RO_setBounds(*child, V2(ctx->pos.x, currentY), V2(ctx->constrainSize.x, maxY - currentY));
        RO_draw(*child);
        currentY += (*child)->ctx.actualSize.y;
        maxXSize = max(maxXSize, (*child)->ctx.actualSize.x);
    }
}

NOP_METHOD(getChildren, Button)
NOP_METHOD(destroy, Button)

void initButton(RenderContext* ctx, ButtonConfig* cfg) {
    cfg->_hover = false;
    cfg->_press = false;
}

void handleEventButton(RenderContext* ctx, ButtonConfig* cfg) {
    Vec2 eventPos = GetEvent()->ui.pos;
    bool eventOccuredInsideButton = V2ContainedByBox(eventPos, ctx->pos, ctx->actualSize);
    switch (GetEvent()->ui.type) {
        case EventType_MouseDown: {
            if (eventOccuredInsideButton) {
                cfg->_press = true;
                RC_markNeedsRedraw(ctx);
            }
            break;
        }
        case EventType_MouseMotion: {
            if (cfg->_hover != eventOccuredInsideButton) {
                cfg->_hover = eventOccuredInsideButton;
                RC_markNeedsRedraw(ctx);
            }
            break;
        }
        case EventType_MouseUp: {
            if (cfg->_press) {
                if (eventOccuredInsideButton) {
                    cfg->onPress();
                }
                cfg->_press = false;
                RC_markNeedsRedraw(ctx);
            }
            break;
        }
    }
}

void drawButton(RenderContext* ctx, ButtonConfig* cfg) {
    Vec2 textSize = GetTextSize(DEFAULTFONT_GET(Button), cfg->text);
    ctx->actualSize = V2(textSize.x + 20, textSize.y + 20);
    if (cfg->_hover || cfg->_press) {
        SetDrawColour(COL(0, 255, 0));
        FillRect(ctx->pos, ctx->actualSize);
        SetDrawColour(COL(0, 0, 0));
        DrawText(DEFAULTFONT_GET(Button), cfg->text, V2(ctx->pos.x + 10, ctx->pos.y + 10));
    } else {
        SetDrawColour(COL(0, 255, 0));
        DrawRect(ctx->pos, ctx->actualSize);
        DrawText(DEFAULTFONT_GET(Button), cfg->text, V2(ctx->pos.x + 10, ctx->pos.y + 10));
    }
}

NOP_METHOD(init, Text)
NOP_METHOD(getChildren, Text)
NOP_METHOD(handleEvent, Text)
NOP_METHOD(destroy, Text)

void drawText(RenderContext* ctx, TextConfig* cfg) {
    ctx->actualSize = GetTextSize(DEFAULTFONT_GET(Text), cfg->text);
    SetDrawColour(COL(0, 255, 0));
    Font* font = DEFAULTFONT_GET(Text);
    DrawText(font, cfg->text, ctx->pos);
}

NOP_METHOD(getChildren, BuildCounter)
NOP_METHOD(handleEvent, BuildCounter)
NOP_METHOD(destroy, BuildCounter)

void initBuildCounter(RenderContext* ctx, BuildCounterConfig* cfg) {
    cfg->_builds = 0;
}

void drawBuildCounter(RenderContext* ctx, BuildCounterConfig* cfg) {
    char text[30];
    cfg->_builds++;
    if (cfg->_builds >= 1000) cfg->_builds = 0;
    sprintf(text, "BuildCounter: drawn %i times", cfg->_builds);
    ctx->actualSize = GetTextSize(DEFAULTFONT_GET(BuildCounter), text);
    SetDrawColour(COL(0, 255, 0));
    DrawText(DEFAULTFONT_GET(BuildCounter), text, ctx->pos);
}