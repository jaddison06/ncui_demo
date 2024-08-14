#define DEFAULT_FONT "./FiraCode-Regular.ttf", 15

#include "widgets.h"

// todo:
//  * weird flicker
//  * buttons don't always hover/unhover
//  * clearing widget space before redraw does NOT work
//  * composing widgets (eg button <-- text)
//  * syntax for laying out widget tree is still not great

DECL_VALUELISTENABLE(int)
DEF_VALUELISTENABLE(int)
DECL_VALUELISTENER(int)
DEF_VALUELISTENER(int)

RenderObject* _buildCounter;
void buildBuildCounter() {
    RO_markNeedsRedraw(_buildCounter);
}

static int_listenable* _listenable;

char* _text = 0;
RenderObject* buildText() {
    if (_text == 0) _text = malloc(4);
    sprintf(_text, "%i", _listenable->value);
    RenderObject* out = Text((TextExtendedConfig){.cfg = (TextConfig){.text = _text}});
    return out;
}

void incrementListenable() {
    if (_listenable->value >= 999) _listenable->value = -1;
    update_intlistenable(_listenable, _listenable->value + 1);
}

RenderObject* build() {
    RenderObject* buildCounter = BuildCounter((BuildCounterExtendedConfig){});
    _buildCounter = buildCounter;
    
    return Column((ColumnExtendedConfig){
        .children = ROList(5,
            Text((TextExtendedConfig){.cfg=(TextConfig){
                .text = "This is a Text widget"
            }}),
            int_listener((int_listenerExtendedConfig){.buildCB = buildText, .cfg = (int_listenerConfig){.listenable = _listenable}}),
            Button((ButtonExtendedConfig){.cfg=(ButtonConfig){.onPress=incrementListenable, .text="Press to increment above counter!"}}),
            buildCounter,
            Button((ButtonExtendedConfig){.cfg=(ButtonConfig){.onPress=buildBuildCounter, .text="Press to mark build counter widget as dirty"}})
        )
    });
}

void dummyTextInputHandler(char* text) {}

int main() {
    if (InitPlatform("NCUI Demo", false) == 0) {
        printf("%s\n", SDL_GetError());
        return 1;
    }
    _listenable = new_int_listenable(0);
    RenderObject* root = build();
    RunUI(root, dummyTextInputHandler);
    RO_destroy(root);
    return 0;
}