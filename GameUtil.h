#pragma once
#include <DxLib.h>
#include <string>

enum DrawType {
    LEFT,
    CENTER,
    RIGHT
};

namespace TextUtil {
	inline void DrawFix2DText(DrawType type, int x, int y, int size, std::string text, unsigned int textColor, unsigned int edgeColor) {
        SetFontSize(size);
        int strWidth = GetDrawStringWidth(text.c_str(), text.size());

        switch (type)
        {
        case LEFT:
            break;
        case CENTER:
            x -= strWidth / 2;
            y -= size / 2;
            break;
        case RIGHT:
            x -= strWidth;
            break;
        }

        DrawString(x, y, text.c_str(), textColor, edgeColor);
    }

}