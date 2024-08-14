#pragma once

#define DEFAULT_FONT "./FiraCode-Regular.ttf", 15

#include "widget.h"

DECL_WIDGET_EXTENDED(Column, , TAKESCHILDREN)
DECL_WIDGET_EXTENDED(Button, char* text; void (*onPress)(); bool _press; bool _hover;, DEFAULTFONT)
DECL_WIDGET_EXTENDED(Text, char* text;, DEFAULTFONT)
DECL_WIDGET_EXTENDED(BuildCounter, int _builds;, DEFAULTFONT)