#include "lcd.h"
#include "lcd_init.h"
#include "lcdfont.h"

#include "main.h"  // 包含HAL库头文件

// 填充矩形区域
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color) {
    uint16_t i, j; 
    LCD_Address_Set(xsta, ysta, xend-1, yend-1);
    for(i = ysta; i < yend; i++) {													   	 
        for(j = xsta; j < xend; j++) {
            LCD_WR_DATA(color);
        }
    } 					  	    
}

// 在指定位置画点
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color) {
    LCD_Address_Set(x, y, x, y);
    LCD_WR_DATA(color);
} 

// 画线
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint16_t t; 
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if(delta_x > 0) incx = 1;
    else if (delta_x == 0) incx = 0;
    else {incx = -1; delta_x = -delta_x;}
    if(delta_y > 0) incy = 1;
    else if (delta_y == 0) incy = 0;
    else {incy = -1; delta_y = -delta_y;}
    if(delta_x > delta_y) distance = delta_x;
    else distance = delta_y;
    for(t = 0; t < distance + 1; t++) {
        LCD_DrawPoint(uRow, uCol, color);
        xerr += delta_x;
        yerr += delta_y;
        if(xerr > distance) {
            xerr -= distance;
            uRow += incx;
        }
        if(yerr > distance) {
            yerr -= distance;
            uCol += incy;
        }
    }
}

// 画矩形
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    LCD_DrawLine(x1, y1, x2, y1, color);
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x1, y2, x2, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
}

// 画圆
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color) {
    int a, b;
    a = 0; b = r;	  
    while(a <= b) {
        LCD_DrawPoint(x0 - b, y0 - a, color);
        LCD_DrawPoint(x0 + b, y0 - a, color);
        LCD_DrawPoint(x0 - a, y0 + b, color);
        LCD_DrawPoint(x0 - a, y0 - b, color);
        LCD_DrawPoint(x0 + b, y0 + a, color);
        LCD_DrawPoint(x0 + a, y0 - b, color);
        LCD_DrawPoint(x0 + a, y0 + b, color);
        LCD_DrawPoint(x0 - b, y0 + a, color);
        a++;
        if((a * a + b * b) > (r * r)) {
            b--;
        }
    }
}

// 显示汉字串
void LCD_ShowChinese(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode) {
    while(*s != 0) {
        if(sizey == 12) LCD_ShowChinese12x12(x, y, s, fc, bc, sizey, mode);
        else if(sizey == 16) LCD_ShowChinese16x16(x, y, s, fc, bc, sizey, mode);
        else if(sizey == 24) LCD_ShowChinese24x24(x, y, s, fc, bc, sizey, mode);
        else if(sizey == 32) LCD_ShowChinese32x32(x, y, s, fc, bc, sizey, mode);
        else return;
        s += 2;
        x += sizey;
    }
}

// 显示12x12汉字
void LCD_ShowChinese12x12(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode) {
    uint8_t i, j, m = 0;
    uint16_t k;
    uint16_t HZnum;
    uint16_t TypefaceNum;
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont12) / sizeof(typFNT_GB12);
    for(k = 0; k < HZnum; k++) {
        if((tfont12[k].Index[0] == *s) && (tfont12[k].Index[1] == *(s + 1))) { 	
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for(i = 0; i < TypefaceNum; i++) {
                for(j = 0; j < 8; j++) {	
                    if(!mode) {
                        if(tfont12[k].Msk[i] & (0x01 << j)) LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if(m % sizey == 0) {
                            m = 0;
                            break;
                        }
                    } else {
                        if(tfont12[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc);
                        x++;
                        if((x - x0) == sizey) {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }				  	
        continue;
    }
} 

// 显示16x16汉字
void LCD_ShowChinese16x16(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode) {
    uint8_t i, j, m = 0;
    uint16_t k;
    uint16_t HZnum;
    uint16_t TypefaceNum;
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont16) / sizeof(typFNT_GB16);
    for(k = 0; k < HZnum; k++) {
        if ((tfont16[k].Index[0] == *s) && (tfont16[k].Index[1] == *(s + 1))) { 	
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for(i = 0; i < TypefaceNum; i++) {
                for(j = 0; j < 8; j++) {	
                    if(!mode) {
                        if(tfont16[k].Msk[i] & (0x01 << j)) LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if(m % sizey == 0) {
                            m = 0;
                            break;
                        }
                    } else {
                        if(tfont16[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc);
                        x++;
                        if((x - x0) == sizey) {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }				  	
        continue;
    }
} 

// 显示24x24汉字
void LCD_ShowChinese24x24(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode) {
    uint8_t i, j, m = 0;
    uint16_t k;
    uint16_t HZnum;
    uint16_t TypefaceNum;
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont24) / sizeof(typFNT_GB24);
    for(k = 0; k < HZnum; k++) {
        if ((tfont24[k].Index[0] == *s) && (tfont24[k].Index[1] == *(s + 1))) { 	
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for(i = 0; i < TypefaceNum; i++) {
                for(j = 0; j < 8; j++) {	
                    if(!mode) {
                        if(tfont24[k].Msk[i] & (0x01 << j)) LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if(m % sizey == 0) {
                            m = 0;
                            break;
                        }
                    } else {
                        if(tfont24[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc);
                        x++;
                        if((x - x0) == sizey) {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }				  	
        continue;
    }
} 

// 显示32x32汉字
void LCD_ShowChinese32x32(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode) {
    uint8_t i, j, m = 0;
    uint16_t k;
    uint16_t HZnum;
    uint16_t TypefaceNum;
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont32) / sizeof(typFNT_GB32);
    for(k = 0; k < HZnum; k++) {
        if ((tfont32[k].Index[0] == *s) && (tfont32[k].Index[1] == *(s + 1))) { 	
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for(i = 0; i < TypefaceNum; i++) {
                for(j = 0; j < 8; j++) {	
                    if(!mode) {
                        if(tfont32[k].Msk[i] & (0x01 << j)) LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if(m % sizey == 0) {
                            m = 0;
                            break;
                        }
                    } else {
                        if(tfont32[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc);
                        x++;
                        if((x - x0) == sizey) {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }				  	
        continue;
    }
}

// 显示单个字符
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode) {
    uint8_t temp, sizex, t, m = 0;
    uint16_t i, TypefaceNum;
    uint16_t x0 = x;
    sizex = sizey / 2;
    TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
    num = num - ' ';
    LCD_Address_Set(x, y, x + sizex - 1, y + sizey - 1);
    for(i = 0; i < TypefaceNum; i++) { 
        if(sizey == 12) temp = ascii_1206[num][i];
        else if(sizey == 16) temp = ascii_1608[num][i];
        else if(sizey == 24) temp = ascii_2412[num][i];
        else if(sizey == 32) temp = ascii_3216[num][i];
        else return;
        for(t = 0; t < 8; t++) {
            if(!mode) {
                if(temp & (0x01 << t)) LCD_WR_DATA(fc);
                else LCD_WR_DATA(bc);
                m++;
                if(m % sizex == 0) {
                    m = 0;
                    break;
                }
            } else {
                if(temp & (0x01 << t)) LCD_DrawPoint(x, y, fc);
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
void LCD_ShowString(uint16_t x, uint16_t y, const char *p, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode) {         
    while(*p != '\0') {       
        LCD_ShowChar(x, y, *p, fc, bc, sizey, mode);
        x += sizey / 2;
        p++;
    }  
}

// 幂运算
uint32_t mypow(uint8_t m, uint8_t n) {
    uint32_t result = 1;	 
    while(n--) result *= m;
    return result;
}

// 显示整数变量
void LCD_ShowIntNum(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey) {         	
    uint8_t t, temp;
    uint8_t enshow = 0;
    uint8_t sizex = sizey / 2;
    for(t = 0; t < len; t++) {
        temp = (num / mypow(10, len - t - 1)) % 10;
        if(enshow == 0 && t < (len - 1)) {
            if(temp == 0) {
                LCD_ShowChar(x + t * sizex, y, ' ', fc, bc, sizey, 0);
                continue;
            } else enshow = 1; 
        }
        LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
    }
} 

// 显示两位小数变量
void LCD_ShowFloatNum1(uint16_t x, uint16_t y, float num, uint8_t len, uint16_t fc, uint16_t bc, uint8_t sizey) {         	
    uint8_t t, temp;
    uint16_t num1;
    uint8_t sizex = sizey / 2;
    num1 = num * 100;
    for(t = 0; t < len; t++) {
        temp = (num1 / mypow(10, len - t - 1)) % 10;
        if(t == (len - 2)) {
            LCD_ShowChar(x + (len - 2) * sizex, y, '.', fc, bc, sizey, 0);
            t++;
            len += 1;
        }
        LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
    }
}

// 显示图片
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[]) {
    uint16_t i, j;
    uint32_t k = 0;
    LCD_Address_Set(x, y, x + length - 1, y + width - 1);
    for(i = 0; i < length; i++) {
        for(j = 0; j < width; j++) {
            LCD_WR_DATA8(pic[k * 2]);
            LCD_WR_DATA8(pic[k * 2 + 1]);
            k++;
        }
    }			
}
