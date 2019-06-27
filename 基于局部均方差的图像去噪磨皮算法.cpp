#include<stdio.h>


//内核公式来源：https://blog.csdn.net/lz0499/article/details/77148182

//imagedata[256][256] 是一个数组，每个元素都是一个含RGB三通道的结构体元素（全局变量）

//deNoiseNum 为σ，Size为滤波器的长（即Size*Size为滤波器总像素点数）

//strInfo.biHeight和strInfo.biWidth 是图片长&宽

//通常：参数deNoiseNum=350，Size=9（若图片噪点数贼多且噪点不明显，比如手机夜景拍照，deNoiseNum=35)


void deNoise(float deNoiseNum, int Size)
{
	//去噪（基于 局部均方差的图像去噪声算法）

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

			//平均值
			meanR = sumR / （Size * Size）;
			meanG = sumG / Size / Size;
			meanB = sumB / Size / Size;

			//方差
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