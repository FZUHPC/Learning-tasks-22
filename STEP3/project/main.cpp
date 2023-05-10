#include"bmp.h"

int main()
{
	//判断
	bool ret;
	//进行操作的图像
	const char * toReadfilename = "bmppicture/photo1.bmp";
	const char * Cropfilename = "bmppicture/crop.bmp";
	const char * Zoomfilename = "bmppicture/zoom.bmp";
	const char * Grayfilename = "bmppicture/gray8bit.bmp";
	const char * toMedianFilterfilename = "bmppicture/SaltandPepperNoiseBmp.bmp";
	const char * MedianFilterfilename = "bmppicture/medianfilter.bmp";

	int choice;
	cout << "Enter your choice: (1 : Crop, 2 : Zoom, 3 : Gray , 4 : Median Filter)" << endl;
	cin >> choice;
	switch(choice)
	{
	case 1:
		ret = CropBmpFile(toReadfilename, Cropfilename);
		cout << "Crop ";
		ErrorPrint(ret); 
		break;
	case 2:
		ret = ZoomBmpFile(toReadfilename, Zoomfilename);
		cout << "Zoom ";
		ErrorPrint(ret);
		break;
	case 3:
		ret = GrayBmpFile(toReadfilename, Grayfilename);
		cout << "Gray ";
		ErrorPrint(ret);
		break;
	case 4:
		ret = MedianFilterBmpFile(toMedianFilterfilename,MedianFilterfilename);
		cout << "Median Filter ";
		ErrorPrint(ret);
		break;
	default:
		cout << "Did anything." << endl;
		break;
	}
	
	return 0;
}