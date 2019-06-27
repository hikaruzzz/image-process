#include<stdio.h>


//�ں˹�ʽ��Դ��https://blog.csdn.net/lz0499/article/details/77148182

//imagedata[256][256] ��һ�����飬ÿ��Ԫ�ض���һ����RGB��ͨ���Ľṹ��Ԫ�أ�ȫ�ֱ�����

//deNoiseNum Ϊ�ң�SizeΪ�˲����ĳ�����Size*SizeΪ�˲��������ص�����

//strInfo.biHeight��strInfo.biWidth ��ͼƬ��&��

//ͨ��������deNoiseNum=350��Size=9����ͼƬ�������������㲻���ԣ������ֻ�ҹ�����գ�deNoiseNum=35)


void deNoise(float deNoiseNum, int Size)
{
	//ȥ�루���� �ֲ��������ͼ��ȥ�����㷨��

	for (int i = Size / 2; i < strInfo.biHeight - Size / 2; i++)
	{
		for (int j = Size / 2; j < strInfo.biWidth - Size / 2; j++)
		{
			int index = 1;
			float sumR2 = 0, sumG2 = 0, sumB2 = 0;
			float sumR = 0, sumG = 0, sumB = 0;
			float meanR = 0, varR = 0;
			float meanG = 0, varG = 0;
			float meanB = 0, varB = 0;
			float kr, kg, kb;

			for (int m = -Size / 2; m <= Size / 2; m++)
			{
				for (int n = -Size / 2; n <= Size / 2; n++)
				{
					sumR += int(imagedata[i + m][j + n].red);
					sumG += imagedata[i + m][j + n].green;
					sumB += imagedata[i + m][j + n].blue;
					sumR2 += imagedata[i + m][j + n].red*imagedata[i + m][j + n].red;
					sumG2 += imagedata[i + m][j + n].green*imagedata[i + m][j + n].green;
					sumB2 += imagedata[i + m][j + n].blue*imagedata[i + m][j + n].blue;
				}
			}

			//ƽ��ֵ
			meanR = sumR / ��Size * Size��;
			meanG = sumG / Size / Size;
			meanB = sumB / Size / Size;

			//����
			varR = (sumR2 - (sumR*sumR) / Size / Size) / Size / Size;
			varG = (sumG2 - (sumG*sumG) / Size / Size) / Size / Size;
			varB = (sumB2 - (sumB*sumB) / Size / Size) / Size / Size;
			kr = varR / (varR + deNoiseNum);
			kg = varG / (varG + deNoiseNum);
			kb = varB / (varB + deNoiseNum);

			imagedata[i][j].red = (1 - kr)*meanR + kr * imagedata[i][j].red;
			imagedata[i][j].green = (1 - kg)*meanG + kg * imagedata[i][j].green;
			imagedata[i][j].blue = (1 - kb)*meanB + kb * imagedata[i][j].blue;
		}
	}
}