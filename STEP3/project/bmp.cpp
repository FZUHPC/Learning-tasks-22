#include"bmp.h"

void ErrorPrint(int ret)
{
	if (!ret)
	{
		cout << "failed!" << endl;
		
	}
	else
	{
		cout << "succeed!" << endl;
	}
}
 
bool ReadBmpFile(const char * filename, struct PictureData *p1) 
{
	FILE * pf;
	pf = fopen(filename, "rb");
	if (NULL == pf)
	{
		cout << "ReadBmpFile - open file failed!" << endl;
		fclose(pf);
		return false;
	}
	
	BITMAPFILEHEADER bitMapFileHeader;
	BITMAPINFOHEADER bitMapInfoHeader;
	fread(&bitMapFileHeader, sizeof(BITMAPFILEHEADER), 1, pf);
	if (0x4D42 != bitMapFileHeader.bfType)
	{
		cout << "ReadBmpFile - it's not a bmp file!" << endl;
		return false;
	}
	cout << "ReadBmpFile - bitMapFileHeader:" << endl;
	cout << "bitMapFileHeader.bfType: " << bitMapFileHeader.bfType << endl;
	cout << "bitMapFileHeader.bfSize: " << bitMapFileHeader.bfSize << endl;
	cout << "bitMapFileHeader.bfOffBits: " << bitMapFileHeader.bfOffBits << endl;
	
	fread(&bitMapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pf);
	//判断位深
	if(bitMapInfoHeader.biBitCount != 8 && bitMapInfoHeader.biBitCount != 24 && bitMapInfoHeader.biBitCount !=32)
	{
		cout << "ReadBmpFile - Format Error %d Bit! Only Supports 8-Bit, 24-Bit and 32-Bit!" << endl;
		return false;
	}
	//判断尺寸
	if(bitMapInfoHeader.biWidth == 0 || bitMapInfoHeader.biHeight == 0)
	{
		cout << "Size Error! Width is zero or height is zero!" << endl;
		return false;
	}
	cout << "\nReadBmpFile - bitMapInfoHeader:" << endl;
	cout << "bitMapInfoHeader.biSize:" << bitMapInfoHeader.biSize << endl;
	cout << "bitMapInfoHeader.biWidth: " << bitMapInfoHeader.biWidth << endl;
	cout << "bitMapInfoHeader.biHeight: " << bitMapInfoHeader.biHeight << endl;
	cout << "bitMapInfoHeader.biCompression: " << bitMapInfoHeader.biCompression << endl;
	cout << "bitMapInfoHeader.biBitCount: " << bitMapInfoHeader.biBitCount << endl;
	cout << "bitMapInfoHeader.biSizeImage: " << bitMapInfoHeader.biSizeImage << endl;
	
	p1->width = bitMapInfoHeader.biWidth;
	p1->height = bitMapInfoHeader.biHeight;
	p1->bitCount = bitMapInfoHeader.biBitCount;
	
	if (8 == bitMapInfoHeader.biBitCount)
	{
		p1->pRGBQUAD = new RGBQUAD[256];
		fread(p1->pRGBQUAD, sizeof(RGBQUAD), 256, pf);
	}
	
	//数据每行字节数为4的倍数
	unsigned int lineBytes = (bitMapInfoHeader.biWidth * bitMapInfoHeader.biBitCount / 8 + 3) / 4 * 4;//步幅是从一行像素的开头到下一行的开头所需的字节数。
	p1->len=bitMapInfoHeader.biHeight * lineBytes;//总共需要的字节数 
	p1->pData = new unsigned char[p1->len];
	fread(p1->pData, sizeof(unsigned char), p1->len, pf);
	
	fclose(pf);
	return true;
}
 
bool WriteBmpFile(const char * filename, struct PictureData *p1)
{
	FILE * pf;
	pf = fopen(filename, "wb");
	if (NULL == pf)
	{
		cout << "WriteBmpFile - open file failed!" << endl;
		fclose(pf);
		return false;
	}
 
	int colorTablesize = 0;
	if (p1->bitCount == 8)
	{
		colorTablesize = 1024;
	}
 
	//待存储图像数据每行字节数为4的倍数
	int lineBytes = (p1->width * p1->bitCount / 8 + 3) / 4 * 4;
 
	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER bitMapFileHeader;
	bitMapFileHeader.bfType = 0x4D42;//bmp类型 
	bitMapFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineBytes * p1->height;
	bitMapFileHeader.bfReserved1 = 0;
	bitMapFileHeader.bfReserved2 = 0;
	bitMapFileHeader.bfOffBits = 54 + colorTablesize;
 
	//申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER bitMapInfoHeader;
	bitMapInfoHeader.biBitCount = p1->bitCount;
	bitMapInfoHeader.biClrImportant = 0;
	bitMapInfoHeader.biClrUsed = 0;
	bitMapInfoHeader.biCompression = 0;
	bitMapInfoHeader.biHeight = p1->height;
	bitMapInfoHeader.biPlanes = 1;
	bitMapInfoHeader.biSize = 40;
	bitMapInfoHeader.biSizeImage = lineBytes * p1->height;
	bitMapInfoHeader.biWidth = p1->width;
	bitMapInfoHeader.biXPelsPerMeter = 0;
	bitMapInfoHeader.biYPelsPerMeter = 0;
 
	//写文件头进文件
	fwrite(&bitMapFileHeader, sizeof(BITMAPFILEHEADER), 1, pf);
	//写位图信息头进内存
	fwrite(&bitMapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pf);
	
	//如果灰度图像，有颜色表，写入文件  
	if (p1->bitCount == 8)
	{
		fwrite(p1->pRGBQUAD, sizeof(RGBQUAD), 256, pf);
	}
 	cout << "WriteBmpFile - bitMapFileHeader: " << endl;
	cout << "bitMapFileHeader.bfType: " << bitMapFileHeader.bfType << endl;
	cout << "bitMapFileHeader.bfSize: " << bitMapFileHeader.bfSize << endl;
	cout << "bitMapFileHeader.bfOffBits: " << bitMapFileHeader.bfOffBits << endl;
	cout << "\nWriteBmpFile - bitMapInfoHeader:" << endl;
	cout << "bitMapInfoHeader.biSize:" << bitMapInfoHeader.biSize << endl;
	cout << "bitMapInfoHeader.biWidth: " << bitMapInfoHeader.biWidth << endl;
	cout << "bitMapInfoHeader.biHeight: " << bitMapInfoHeader.biHeight << endl;
	cout << "bitMapInfoHeader.biCompression: " << bitMapInfoHeader.biCompression << endl;
	cout << "bitMapInfoHeader.biBitCount: " << bitMapInfoHeader.biBitCount << endl;
	cout << "bitMapInfoHeader.biSizeImage: " << bitMapInfoHeader.biSizeImage << endl;
 
	
	fwrite(p1->pData, sizeof(unsigned char), p1->height * lineBytes, pf);
	fclose(pf);
	return true;
}

bool CropBmpFile(const char * toReadfilename, const char * toCropfilename)
{
    struct PictureData *pCrop = new struct PictureData;
	pCrop->pRGBQUAD = NULL;
	pCrop->pData = NULL;
    bool ret = ReadBmpFile(toReadfilename, pCrop);
	cout << "CropBmpFile - Read bmp file ";
	ErrorPrint(ret); 
    cout << endl;
	if(!ret)
	{
		return false;
	}

    unsigned int OffsetWidth, OffsetHeight, CropWidth, CropHeight;
	cout << "CropBmpFile - Enter OffsetWidth, OffsetHeight, CropWidth, CropHeight: " << endl; 
	cin >> OffsetWidth >> OffsetHeight >> CropWidth >> CropHeight; 
	
    if (OffsetWidth + CropWidth > pCrop->width || OffsetHeight + CropHeight > pCrop->height || OffsetWidth < 0 || OffsetHeight < 0 || CropWidth <= 0 || CropHeight <= 0) 
	{
        cout << "CropBmpFile - Crop Size Error!" << endl;
        return false;
    }

    unsigned int depthBytes = pCrop->bitCount / 8;//一字节八位， 每像素位数/8=每像素字节 
    unsigned int lineBytes = ((pCrop->width * depthBytes + 3) / 4) * 4;//步幅是从一行像素的开头到下一行的开头所需的字节数。
    
    unsigned int dstLineBytes = ((CropWidth * depthBytes + 3) / 4) * 4;//步幅是从一行像素的开头到下一行的开头所需的字节数。
    unsigned long dstPixelLen = dstLineBytes * CropHeight;//总共需要的字节数 
    unsigned char *CropData = new unsigned char[dstPixelLen];

    for (unsigned int i = 0; i < CropHeight; i++) {
        memcpy(CropData + i * dstLineBytes, pCrop->pData + (i + pCrop->height - CropHeight - OffsetHeight) * lineBytes + OffsetWidth * depthBytes, dstLineBytes);
    }
    
    pCrop->pData = CropData;
    pCrop->len = dstPixelLen;
    pCrop->height = CropHeight;
    pCrop->width = CropWidth;
    
	ret = WriteBmpFile(toCropfilename, pCrop);
	cout << "CropBmpFile - Write bmp file " ;
	ErrorPrint(ret); 
	if(!ret)
	{
		return false;
	}
	
	delete[] pCrop->pRGBQUAD;
	pCrop->pRGBQUAD = NULL;
	delete[] pCrop->pData;
	pCrop->pData = NULL;
	delete pCrop;

    return true;
}

bool ZoomBmpFile(const char * toReadfilename, const char * toZoomfilename)
{
    //读取
    struct PictureData *pZoom = new struct PictureData;
	pZoom->pRGBQUAD = NULL;
	pZoom->pData = NULL;
    bool ret = ReadBmpFile(toReadfilename, pZoom);
	cout << "ZoomBmpFile - Read bmp file ";
	ErrorPrint(ret); 
    cout << endl;
	if(!ret)
	{
		return false;
	}

    //输入缩放因子
    double factorX;
    double factorY;
    cout << "ZoomBmpFile - Enter zoom factorX, factorY: " <<endl;
    cin >> factorX >> factorY;

    //判断缩放因子
    if (factorX <= 0 || factorY <= 0) 
    {
        cout << "ZoomBmpFile - Factor Error! Cannot be negative!" << endl;
        return false;
    }

    double factorReciprocalX = 1 / factorX;
    double factorReciprocalY = 1 / factorY;
    unsigned int dstWidth = (unsigned int)(pZoom->width * factorX);
    unsigned int dstHeight = (unsigned int)(pZoom->height * factorY);

    unsigned int depthBytes = pZoom->bitCount / 8;
    unsigned int dstLineBytes = ((dstWidth * depthBytes + 3) / 4) * 4;
    unsigned char *dstBytes = new unsigned char[dstLineBytes * dstHeight];
    unsigned int lineBytes = ((pZoom->width * depthBytes + 3) / 4) * 4;

    for (unsigned int h = 0; h < dstHeight; h++) 
    {
        for (unsigned int w = 0; w < dstWidth; w++) 
        {
            //原图像的真实位置
            double srcRealX = (w + 0.5) * factorReciprocalX - 0.5;
            double srcRealY = (h + 0.5) * factorReciprocalY - 0.5;

            //原图像对应的像素点位置
            int srcX = (int)srcRealX;
            int srcY = (int)srcRealY;

            //原图像位置偏移量
            double offsetX = srcRealX - srcX;
            double offsetY = srcRealY - srcY;

            //原图像位置的临近4个点
            int leftUp = srcY * lineBytes + srcX * depthBytes;
            int rightUp = srcY * lineBytes + (srcX + 1) * depthBytes;
            int leftDown = (srcY + 1) * lineBytes + srcX * depthBytes;
            int rightDown = (srcY + 1) * lineBytes + (srcX + 1) * depthBytes;

            if (srcY + 1 == dstHeight - 1) 
            {
                leftDown = leftUp;
                rightDown = rightUp;
            }
            if (srcX + 1 == dstWidth - 1)
            {
                rightUp = leftUp;
                rightDown = leftDown;
            }

            //目的图像像素位置索引
            int index = h * dstLineBytes + w * depthBytes;
            for (unsigned int i = 0; i < depthBytes; i++) 
            {
                double part1 = pZoom->pData[leftUp + i] * (1 - offsetX) * (1 - offsetY);
                double part2 = pZoom->pData[rightUp + i] * offsetX * (1 - offsetY);
                double part3 = pZoom->pData[leftDown + i] * offsetY * (1 - offsetX);
                double part4 = pZoom->pData[rightDown + i] * offsetY * offsetX;

                dstBytes[index + i] = (unsigned char)(part1 + part2 + part3 + part4);
            }
        }
    }

    pZoom->pData = dstBytes;
    pZoom->len = dstLineBytes * dstHeight;
    pZoom->width = dstWidth;
    pZoom->height = dstHeight;

    ret = WriteBmpFile(toZoomfilename, pZoom);
	cout << "ZoomBmpFile - Write bmp file " ;
	ErrorPrint(ret); 
	if(!ret)
	{
		return false;
	}

    delete[] pZoom->pRGBQUAD;
	pZoom->pRGBQUAD = NULL;
	delete[] pZoom->pData;
	pZoom->pData = NULL;
	delete pZoom;
    return true;
}

bool GrayBmpFile(const char * toReadfilename, const char * toGrayfilename)
{
 
	/*char readPath[] = "D:\\C++_file\\image_deal_C++\\IMAGE_JIEQU\\1.bmp";
	readBmp(readPath);*/
    struct PictureData *pGray = new struct PictureData;
	pGray->pRGBQUAD = NULL;
	pGray->pData = NULL;
    bool ret = ReadBmpFile(toReadfilename, pGray);
	cout << "GrayBmpFile - Read bmp file ";
	ErrorPrint(ret); 
    cout << endl;
	if(!ret)
	{
		return false;
	}

    if(24 != pGray->bitCount)
    {
        cout << "GrayBmpFile - The file is't a RGB bmp file!" << endl;
        return false;
    }
 
	unsigned char *pGrayData;
	//因为24为真彩色位图数据的一个像素用3各字节表示，灰度图像为1个字节  
    pGray->bitCount = 8;
	//一个扫描行所占的字节数必须是4的倍数(即以long为单位),不足的以0填充  
	//所以如果当前pGray->width如果不是4的倍数时，要在后面补0直到为4的倍数
	int lineBytes = (pGray->width * pGray->bitCount / 8 + 3) / 4 * 4;
	int oldLineBytes = (pGray->width * 24 / 8 + 3) / 4 * 4;
	pGrayData = new unsigned char[lineBytes * pGray->height];
	
	//定义灰度图像的颜色表	
	pGray->pRGBQUAD = new RGBQUAD[256];
	for (int i = 0; i < 256; i++)
	{
		(*(pGray->pRGBQUAD + i)).rgbBlue = i;
		(*(pGray->pRGBQUAD + i)).rgbGreen = i;
		(*(pGray->pRGBQUAD + i)).rgbRed = i;
		(*(pGray->pRGBQUAD + i)).rgbReserved = 0;
	}
	//将RGB转换为灰度值 
	int red, green, blue;
	BYTE gray;
	//char gray_1;
 
	for (int i = 0; i < pGray->height; i++)
	{
		//位图数据(pGray->pData)中存储的实际像素数为pGray->width个,而一个扫描行要lineByte个字节，  
		//多余出来的是上面补的0,所以要转换的要是实际的像素数,  
		//因为转换前后pGray->width是相同的，而lineByte是不同的，也就是后面补的0不同  
		for (int j = 0; j < pGray->width; j++)
		{
			red = *(pGray->pData + i*oldLineBytes + 3 * j + 2);
			green = *(pGray->pData + i*oldLineBytes + 3 * j + 1);
			blue = *(pGray->pData + i*oldLineBytes + 3 * j );
			//实际应用时，希望避免低速的浮点运算，所以需要整数算法。
			gray = (BYTE)((77 * red + 151 * green + 28 * blue) >> 8);
			//gray_1 = red*0.299 + green*0.587 + blue*0.114;
			*(pGrayData + i*lineBytes + j) = gray;
		}
	}
    pGray->pData = pGrayData;

    ret = WriteBmpFile(toGrayfilename, pGray);
	cout << "GrayBmpFile - Write bmp file " ;
	ErrorPrint(ret); 
	if(!ret)
	{
		return false;
	}
	
	delete[] pGray->pRGBQUAD;
	pGray->pRGBQUAD = NULL;
	delete[] pGray->pData;
	pGray->pData = NULL;
	delete pGray;

    return true;
}

unsigned char GetMedianNum(int * bArray, int iFilterLen)
{
	int i, j;// 循环变量  
	unsigned char bTemp;
 
	// 用冒泡法对数组进行排序  
	for (j = 0; j < iFilterLen - 1; j++)
	{
		for (i = 0; i < iFilterLen - j - 1; i++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// 互换  
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
 
	// 计算中值  
	if ((iFilterLen & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素  
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值  
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}
 
	return bTemp;
}
 
bool MedianFilterBmpFile(const char * toMedianFilterfilename, const char * MedianFilterfilename)
{
	
    struct PictureData *pFilter = new struct PictureData;
	pFilter->pRGBQUAD = NULL;
	pFilter->pData = NULL;
    bool ret = ReadBmpFile(toMedianFilterfilename, pFilter);
	cout << "MedianFilterBmpFile - Read bmp file ";
	ErrorPrint(ret); 
    cout << endl;
	if(!ret)
	{
		return false;
	}
    
	unsigned char *FilterData;
	unsigned char *oldData;
	oldData = pFilter->pData;
	int  aValue[iFilterH*iFilterW];          // 指向滤波器数组的指针  
 
	int lineBytes = (pFilter->width * pFilter->bitCount / 8 + 3) / 4 * 4;
	FilterData = new unsigned char[lineBytes * pFilter->height];
	int iFilterHM= (iFilterH - 1)/ 2;
	int iFilterWM = (iFilterW - 1) / 2;
 
 
	for (int i = iFilterHM; i < pFilter->height - iFilterHM; i++)
		for (int j = iFilterWM; j < pFilter->width - iFilterWM; j++)
			for (int k = 0; k < 3; k++)
			{
				
				for (int m  = 0; m< iFilterH; m++)
					for (int n = 0; n < iFilterW; n++)
						{
							aValue[m * iFilterW + n] = *(oldData + lineBytes* (i+m-1) + (j + n-1) * 3 + k);	
						}
				*(FilterData + pFilter->width * 3 * i + j * 3 + k) = GetMedianNum(aValue, iFilterH * iFilterW); 
				
			}
 
	for (int i = 0; i < pFilter->height; i++)
		for (int j = 0; j < pFilter->width; j++)
				for (int k = 0; k < 3; k++)
				{
 
					
					if ((i<iFilterHM) && (j<iFilterWM))
								*(FilterData + lineBytes * i + j * 3 + k) = *(FilterData + lineBytes* (i + iFilterHM) + (j + iFilterWM) * 3 + k);
					else if ((i<iFilterHM) && (j>=iFilterWM)&&(j<(pFilter->width - iFilterWM)))
						*(FilterData + lineBytes * i + j * 3 + k) = *(FilterData + lineBytes* (i + iFilterHM) + j  * 3 + k);
					else if ((i<iFilterHM) && ( j >= (pFilter->width - iFilterWM)))
						*(FilterData + lineBytes * i + j * 3 + k) = *(FilterData + lineBytes* (i + iFilterHM) + (j - iFilterWM) * 3 + k);
					else if ((i>=iFilterHM) && i <(pFilter->height - iFilterHM) && (j< iFilterWM))
						*(FilterData + lineBytes * i + j * 3 + k) = *(FilterData + lineBytes* i + (j + iFilterWM) * 3 + k);
					else if ((i>=iFilterHM) && i < (pFilter->height - iFilterHM) && (j >= (pFilter->width - iFilterWM)))
						*(FilterData + lineBytes * i + j * 3 + k) = *(FilterData + lineBytes* i + (j - iFilterWM) * 3 + k);
					else if ((i >= (pFilter->height - iFilterHM)) && (j< iFilterWM))
						*(FilterData + lineBytes * i + j * 3 + k) = *(FilterData + lineBytes* (i - iFilterHM) + (j + iFilterWM) * 3 + k);
					else if ((i >= (pFilter->height - iFilterHM)) && (j>= iFilterWM)&&(j<(pFilter->width - iFilterWM)))
								*(FilterData + lineBytes * i + j * 3 + k) = *(FilterData + lineBytes* (i - iFilterHM) + j * 3 + k);
					else if ((i >= (pFilter->height - iFilterHM)) && ( j >= (pFilter->width - iFilterWM)))
						*(FilterData + lineBytes * i + j * 3 + k) = *(FilterData + lineBytes* (i - iFilterHM) + (j - iFilterWM) * 3 + k);
				
					
				}
    pFilter->pData = FilterData;
 
	
	ret = WriteBmpFile(MedianFilterfilename, pFilter);
	cout << "MedianFilterBmpFile - Write bmp file " ;
	ErrorPrint(ret); 
	if(!ret)
	{
		return false;
	}
	
	delete[] pFilter->pRGBQUAD;
	pFilter->pRGBQUAD = NULL;
	delete[] pFilter->pData;
	pFilter->pData = NULL;
	delete pFilter;

    return true;
}
