// lcd.c
#include "lcd.h"
#include "lcd_init.h"
#include "lcdfont.h"


// 区域填充函数
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint32_t color) {
    LCD_Address_Set(xsta, ysta, xend-1, yend-1);
    for(uint16_t i = ysta; i < yend; i++) {
        for(uint16_t j = xsta; j < xend; j++) {
            LCD_WR_DATA(color);
        }
    }
}

// 画点函数
void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t color) {
    LCD_Address_Set(x, y, x, y);
    LCD_WR_DATA(color);
}

// 画线函数 (Bresenham算法)
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color) {
    int16_t dx = abs(x2 - x1);
    int16_t dy = abs(y2 - y1);
    int16_t sx = (x1 < x2) ? 1 : -1;
    int16_t sy = (y1 < y2) ? 1 : -1;
    int16_t err = dx - dy;
    
    while(1) {
        LCD_DrawPoint(x1, y1, color);
        if(x1 == x2 && y1 == y2) break;
        
        int16_t e2 = 2 * err;
        if(e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if(e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// 画矩形函数
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color) {
    LCD_DrawLine(x1, y1, x2, y1, color);
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x1, y2, x2, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
}

// 画圆函数 (中点圆算法)
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint32_t color) {
    int16_t x = 0;
    int16_t y = r;
    int16_t d = 1 - r;
    
    while(x <= y) {
        LCD_DrawPoint(x0 + x, y0 + y, color);
        LCD_DrawPoint(x0 - x, y0 + y, color);
        LCD_DrawPoint(x0 + x, y0 - y, color);
        LCD_DrawPoint(x0 - x, y0 - y, color);
        LCD_DrawPoint(x0 + y, y0 + x, color);
        LCD_DrawPoint(x0 - y, y0 + x, color);
        LCD_DrawPoint(x0 + y, y0 - x, color);
        LCD_DrawPoint(x0 - y, y0 - x, color);
        
        if(d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}


// 显示单个字符
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint32_t fc, uint32_t bc, uint8_t sizey, uint8_t mode) {
    uint8_t temp;
    uint8_t sizex = sizey / 2;
    uint16_t TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
    uint16_t x0 = x;
    
    num = num - ' ';
    LCD_Address_Set(x, y, x + sizex - 1, y + sizey - 1);
    
    for(uint16_t i = 0; i < TypefaceNum; i++) {
        if(sizey == 12) {
            temp = ascii_1206[num][i];
        } else if(sizey == 16) {
            temp = ascii_1608[num][i];
        } else if(sizey == 24) {
            temp = ascii_2412[num][i];
        } else if(sizey == 32) {
            temp = ascii_3216[num][i];
        } else {
            return;
        }
        
        for(uint8_t t = 0; t < 8; t++) {
            if(!mode) {
                if(temp & (0x01 << t)) {
                    LCD_WR_DATA(fc);
                } else {
                    LCD_WR_DATA(bc);
                }
            } else {
                if(temp & (0x01 << t)) {
                    LCD_DrawPoint(x, y, fc);
                }
                x++;
                if((x - x0) == sizex) {
                    x = x0;
                    y++;
                    break;
                }
            }
        }
    }
}

// 显示字符串
void LCD_ShowString(uint16_t x, uint16_t y, const uint8_t *p, uint32_t fc, uint32_t bc, uint8_t sizey, uint8_t mode) {
    while(*p != '\0') {
        LCD_ShowChar(x, y, *p, fc, bc, sizey, mode);
        x += sizey / 2;
        p++;
    }
}

// 幂函数
uint32_t mypow(uint8_t m, uint8_t n) {
    uint32_t result = 1;
    while(n--) {
        result *= m;
    }
    return result;
}

// 显示整数
void LCD_ShowIntNum(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint32_t fc, uint32_t bc, uint8_t sizey) {
    uint8_t sizex = sizey / 2;
    uint8_t enshow = 0;
    
    for(uint8_t t = 0; t < len; t++) {
        uint8_t temp = (num / mypow(10, len - t - 1)) % 10;
        
        if(enshow == 0 && t < (len - 1)) {
            if(temp == 0) {
                LCD_ShowChar(x + t * sizex, y, ' ', fc, bc, sizey, 0);
                continue;
            } else {
                enshow = 1;
            }
        }
        LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
    }
}

// 显示浮点数
void LCD_ShowFloatNum1(uint16_t x, uint16_t y, float num, uint8_t len, uint32_t fc, uint32_t bc, uint8_t sizey) {
    uint8_t sizex = sizey / 2;
    uint16_t num1 = num * 100;
    
    for(uint8_t t = 0; t < len; t++) {
        uint8_t temp = (num1 / mypow(10, len - t - 1)) % 10;
        
        if(t == (len - 2)) {
            LCD_ShowChar(x + (len - 2) * sizex, y, '.', fc, bc, sizey, 0);
            t++;
            len++;
        }
        LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
    }
}

// 显示图片
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[]) {
    uint32_t k = 0;
    LCD_Address_Set(x, y, x + length - 1, y + width - 1);
    
    for(uint16_t i = 0; i < length; i++) {
        for(uint16_t j = 0; j < width; j++) {
            LCD_WR_DATA((pic[k*3] << 16) | (pic[k*3+1] << 8) | pic[k*3+2]);
            k++;
        }
    }
}
