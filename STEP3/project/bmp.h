#include <iostream>
#include <cstring>
#include<inttypes.h>
using namespace std;
 
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef uint8_t BYTE;

#pragma pack (1)
typedef  struct tagBITMAPFILEHEADER 
{
	WORD           bfType;//位图文件类型，必须是0x4D42，即字符串“BM”，也就是说所有.bmp文件的头两个字节都是“BM”
	DWORD        bfSize;//位图文件大小，包括这14个字节
	WORD           bfReserved1;//保留字，设为0
	WORD           bfReserved2;//保留字，设为0
	DWORD        bfOffBits;//从文件头到实际的位图数据的偏移字节数，单位：字节
} BITMAPFILEHEADER;
#pragma pack (1)
typedef struct tagBITMAPINFOHEADER
{
	DWORD        biSize;//本结构所占用字节数，大小为40字节
	LONG            biWidth;//位图宽度，单位：字节
	LONG            biHeight;//位图高度，单位：字节
	WORD           biPlanes;//目标设备级别，必须为1
	WORD           biBitCount;//表示颜色时每个像素要用到的位数，常用的值为1(黑白二色图), 4(16色图), 8(256色), 24(真彩色图)
	DWORD        biCompression;// 位图是否压缩，其类型是 0(BI_RGB不压缩),  1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)
	DWORD        biSizeImage;//实际的位图数据占用的字节数
	LONG            biXPelsPerMeter;//位图水平分辨率，每米像素数
	LONG            biYPelsPerMeter;//位图垂直分辨率，每米像素数
	DWORD        biClrUsed;//指定本图象实际用到的颜色数，如果该值为零，则用到的颜色数为2的biBitCount次幂个
	DWORD        biClrImportant;//指定本图象中重要的颜色数，如果该值为零，则认为所有的颜色都是重要的
} BITMAPINFOHEADER;
#pragma pack (1)
typedef struct tagRGBQUAD 
{
	BYTE    rgbBlue; //该颜色的蓝色分量(值范围为0-255)  
	BYTE    rgbGreen; //该颜色的绿色分量(值范围为0-255) 
	BYTE    rgbRed; //该颜色的红色分量(值范围为0-255) 
	BYTE    rgbReserved; //保留值，设为0
} RGBQUAD;

class PictureData
{
public:
    unsigned char * pData;//读入图像数据的指针
	unsigned int width;//图像的宽
	unsigned int height;//图像的高
	unsigned short bitCount;//图像类型，每像素位数
	unsigned long len;//PixelLen
	RGBQUAD * pRGBQUAD;//颜色表指针
};

#define iFilterW 3
#define iFilterH 3

void ErrorPrint(int ret);
 
bool ReadBmpFile(const char * filename, struct PictureData *p1) ;
 
bool WriteBmpFile(const char * filename, struct PictureData *p1);

bool CropBmpFile(const char * toReadfilename, const char * toCropfilename);

bool ZoomBmpFile(const char * toReadfilename, const char * toZoomfilename);

bool GrayBmpFile(const char * toReadfilename, const char * toGrayfilename);

unsigned char GetMedianNum(int * bArray, int iFilterLen);
 
bool MedianFilterBmpFile(const char * toMedianFilterfilename, const char * MedianFilterfilename);
